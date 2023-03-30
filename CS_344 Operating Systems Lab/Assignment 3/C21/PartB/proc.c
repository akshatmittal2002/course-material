#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "fs.h"
#include "file.h"
#include "stat.h"
#include "fcntl.h"
#include <stdbool.h>

struct {
  struct spinlock lock;
  struct proc proc[NPROC];
} ptable;

static struct proc *initproc;

int nextpid = 1;
extern void forkret(void);
extern void trapret(void);

static void wakeup1(void *chan);

// This function create a kernel process and add it to the processes queue.
void
create_kernel_process(const char *name, void (*entrypoint)()){
  char *sp;
  struct proc *p;

  acquire(&ptable.lock);

  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    if(p->state == UNUSED)
      goto found;

  release(&ptable.lock);
  return;

found:
  p->state = EMBRYO;
  p->pid = nextpid++;

  release(&ptable.lock);

  // Allocate kernel stack.
  p->kstack = kalloc();
  if (p->kstack == 0)
  {
    p->state = UNUSED;
    return;
  }
  sp = p->kstack + KSTACKSIZE;

  // Leave room for trap frame.
  sp -= sizeof *p->tf;
  p->tf = (struct trapframe*) sp;

  // Set up new context to start executing at forkret,
  // which returns to trapret.
  sp -= 4;
  *(uint*)sp = (uint)exit; // end the kernel process upon return from entrypoint()

  sp -= sizeof *p->context;
  p->context = (struct context*)sp;
  memset(p->context, 0, sizeof *p->context);
  (p->context)->eip = (uint)entrypoint;

  if((p->pgdir = setupkvm()) == 0)
    panic("kernel process: out of memory?");

  p->sz = PGSIZE;
  p->parent = initproc;
  p->cwd = idup(initproc->cwd);

  safestrcpy(p->name, name, sizeof(p->name));

  acquire(&ptable.lock);
  p->state = RUNNABLE;
  release(&ptable.lock);
  return;
}

// Circular Queue ADT
struct swapqueue{
  int front, rear;              // To indidicate start and end
  int size;                     // Size of queue
  char* reqchan;                // Channel on which requesting processes for swapping-out/in a page waits
  char* qchan;                  // Channel on which swapout/swapin function waits if no process to serve
  struct spinlock lock;         // Lock to protect shared access
  struct proc* queue[NPROC+1];  // Queue storing PCB of the processes queued for swapping-out/in requests
};

// Enqueue function for the queue
void
enqueue(struct swapqueue* sq, struct proc* np){
  if(sq->size == NPROC)
    return;
  sq->rear = (sq->rear + 1) % NPROC;
  sq->queue[sq->rear] = np;
  sq->size++;  
}

// Dequeue function for the queue
struct proc*
dequeue(struct swapqueue* sq){
  if (sq->size == 0)
    return 0;
  struct proc* res = sq->queue[sq->front]; 
  sq->front = (sq->front + 1) % NPROC; 
  sq->size--;
  if(sq->size == 0){
    sq->front = 0;
    sq->rear = NPROC - 1;
  }
  return res; 
}

// To store victim frames
struct victim{
  pte_t* pte;
  struct proc* pr;
  uint va; 
};

// Limit on number of files
extern int flimit;
int flimit;

// Separate queues for swap-out and swap-in
extern struct swapqueue swap_out_queue, swap_in_queue;
struct swapqueue swap_out_queue, swap_in_queue;

// Count for number of swap out and swap in
int swapoutcount, swapincount;

// Inbuilt function to allocate fd; present in sysfile.c
int
fdalloc(struct file *f){
  int fd;
  struct proc *curproc = myproc();

  for(fd = 0; fd < NOFILE; fd++){
    if(curproc->ofile[fd] == 0){
      curproc->ofile[fd] = f;
      return fd;
    }
  }
  return -1;
}

// Inbuilt function to create a file with given name; present in sysfile.c
struct inode*
create(char *path, short type, short major, short minor)  
{
  struct inode *ip, *dp;
  char name[DIRSIZ];

  if((dp = nameiparent(path, name)) == 0)
    return 0;
  ilock(dp);

  if((ip = dirlookup(dp, name, 0)) != 0){
    iunlockput(dp);
    ilock(ip);
    if(type == T_FILE && ip->type == T_FILE)
      return ip;
    iunlockput(ip);
    return 0;
  }

  if((ip = ialloc(dp->dev, type)) == 0)
    panic("create: ialloc");

  ilock(ip);
  ip->major = major;
  ip->minor = minor;
  ip->nlink = 1;
  iupdate(ip);

  if(type == T_DIR){  // Create . and .. entries.
    dp->nlink++;  // for ".."
    iupdate(dp);
    // No ip->nlink++ for ".": avoid cyclic ref count.
    if(dirlink(ip, ".", ip->inum) < 0 || dirlink(ip, "..", dp->inum) < 0)
      panic("create dots");
  }

  if(dirlink(dp, name, ip->inum) < 0)
    panic("create: dirlink");

  iunlockput(dp);

  return ip;
}

// Inbuilt function to open a file; present in sysfile.c
int
open_file(char *path, int omode) {  
  int fd;
  struct file *f;
  struct inode *ip;

  begin_op();

  if(omode & O_CREATE){
    ip = create(path, T_FILE, 0, 0);
    if(ip == 0){
      end_op();
      return -1;
    }
  } else {
    if((ip = namei(path)) == 0){
      end_op();
      return -1;
    }
    ilock(ip);
    if(ip->type == T_DIR && omode != O_RDONLY){
      iunlockput(ip);
      end_op();
      return -1;
    }
  }

  if((f = filealloc()) == 0 || (fd = fdalloc(f)) < 0){
    if(f)
      fileclose(f);
    iunlockput(ip);
    end_op();
    return -1;
  }
  iunlock(ip);
  end_op();

  f->type = FD_INODE;
  f->ip = ip;
  f->off = 0;
  f->readable = !(omode & O_WRONLY);
  f->writable = (omode & O_WRONLY) || (omode & O_RDWR);
  strncpy(f->name, path, 14);
  return fd;
}


// Create name string from PID and VA[32:13]; will return PID_VA[32:13] as the name
void
get_name(int pid, uint addr, char *name) {
  int i = 0;
  while (pid){
    name[i++] = '0' + (pid%10);
    pid = pid/10;
  }
  int mid = i;
  
  name[i++] = '_';
  
  if(addr==0){
    name[i++]='0';
  }
  while (addr){
    name[i++] = '0' + (addr%10);
    addr = addr/10;
  }
  
  name[i++] = '.';
  name[i++] = 's';
  name[i++] = 'w';
  name[i++] = 'p';
  name[i] = 0;

  char temp;
  for(int j=0; j<mid/2; j++){
    temp = name[j];
    name[j] = name[mid-j-1];
    name[mid-j-1] = temp;
  }

  for(int j=mid+1, k=i-5; j<k; j++, k--){
    temp = name[j];
    name[j] = name[k];
    name[k] = temp;
  }
}

// Writes a page into the swapout file
int
write_page(int pid, uint addr, char *buf){
  
  flimit++;

  char name[14];
  get_name(pid, addr, name);
  
  int fd = open_file(name, O_CREATE|O_WRONLY);  // Open + create file 
  struct file *f;
  if(fd < 0 || fd >= NOFILE || (f = myproc()->ofile[fd]) == 0)
    return -1;
  
  // cprintf("Creating page file: %s\n", name);
  char my_pid[3], my_va[3];
  int va = (int) addr;

  my_pid[2] = 0;
  my_pid[1] = '0' + pid % 10;
  my_pid[0] = (pid / 10 ? '0' + pid / 10 : ' ');

  my_va[2] = 0;
  my_va[1] = '0' + va%10;
  my_va[0] = (va / 10 ? '0' + va / 10 : ' ');

  if (my_va[0] == ' ')
    cprintf("|    Page File Creation     |  %s | %s |      Contents of page %s saved in %s        |\n", my_pid, my_va, my_va, name);
  else
    cprintf("|    Page File Creation     |  %s | %s |      Contents of page %s saved in %s       |\n", my_pid, my_va, my_va, name);

  int noc = filewrite(f, buf, 4096); // Write the page in the file
  if (noc < 0)
    cprintf("Unable to write. Exiting (paging.c::write_page)!!");
  
  swapoutcount++;
  return noc;
}

// Deletes swapout file with the given filename; present in sysfile.c
int
delete_page(char* path){
  struct inode *ip, *dp;
  struct dirent de;
  char name[DIRSIZ];
  uint off;

  begin_op();
  dp = nameiparent(path, name);

  ilock(dp);

  if(namecmp(name, ".") == 0 || namecmp(name, "..") == 0)
    goto bad;

  if((ip = dirlookup(dp, name, &off)) == 0)
    goto bad;
  
  ilock(ip);

  if(ip->nlink < 1)
    panic("unlink: nlink < 1");

  memset(&de, 0, sizeof(de));
  
  if(writei(dp, (char*)&de, off, sizeof(de)) != sizeof(de))
    panic("unlink: writei");
  
  if(ip->type == T_DIR){
    dp->nlink--;
    iupdate(dp);
  }
  
  iunlockput(dp);

  ip->nlink--;
  iupdate(ip);
  iunlockput(ip);
  end_op();
  return 0;

bad:
  iunlockput(dp);
  end_op();
  return -1;
}

// Reads the swapout file into the buffer 
int
read_page(int pid, uint addr, char *buf){
  
  char name[14];
  get_name(pid, addr, name);
  
  int fd = open_file(name, O_RDONLY);   // Open swapout page file
  struct file *f;
  if(fd < 0 || fd >= NOFILE || (f=myproc()->ofile[fd]) == 0)
    return -1;
  
  int noc = fileread(f, buf, 4096);     // Read the page into the buffer
  if(noc < 0)
    cprintf("Unable to write. Exiting (paging.c::read_page)!!");
  
  swapincount++;
  
  delete_page(name);
  myproc()->ofile[fd] = 0;
  fileclose(f);

  return noc;
}

// Chooses a victim frame using LRU and evicts it 
int
select_victim_evict(int pid){
  struct proc* p;
  struct victim victims[4] = {{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
  pde_t *pte;

  for(p=ptable.proc; p<&ptable.proc[NPROC]; p++){
      if (p->state == UNUSED || p->state == EMBRYO || p->state == RUNNING || p->pid < 5 || p->pid == pid)
        continue;
      
      for(uint i=PGSIZE; i<p->sz; i+=PGSIZE){
        pte = (pte_t*)getpte(p->pgdir, (void *) i);
        if(!((*pte) & PTE_U) || !((*pte) & PTE_P))
          continue;
        
        // 96 = 1100000 in binary
        int idx = (((*pte)&(uint)96)>>5);
        if(idx>0 && idx<3)
          idx = 3-idx;
        
        victims[idx].pte = pte;
        victims[idx].va = i;
        victims[idx].pr = p;
      }
  }

  for(int i=0; i<4; i++){
    if(victims[i].pte == 0)
      continue;
    
    pte = victims[i].pte;
    int origstate = victims[i].pr->state;
    char* origchan = victims[i].pr->chan;
    victims[i].pr->state = SLEEPING;
    victims[i].pr->chan = 0;
    uint reqpte = *pte;
    *pte = ((*pte) & (~PTE_P)) | ((uint)1<<7);
    
    if(victims[i].pr->state != ZOMBIE){
      release(&swap_out_queue.lock);
      release(&ptable.lock);

      write_page(victims[i].pr->pid, (victims[i].va)>>12, (void *)P2V(PTE_ADDR(reqpte)));   
      
      acquire(&swap_out_queue.lock);
      acquire(&ptable.lock);
    }

    kfree((char *)P2V(PTE_ADDR(reqpte)));
    lcr3(V2P(victims[i].pr->pgdir)); 
    victims[i].pr->state = origstate;
    victims[i].pr->chan = origchan;
    return 1;
  }
  return 0;
}

// Entry point of the swapout process
void swapout_proc(){
  sleep(swap_out_queue.qchan, &ptable.lock);
  while(1){
    // cprintf("\n\nEntering swapout\n");
    cprintf("|      Swapout Resumes      |  -  | -  |   Swapout queue is non-empty => start execution   |\n");
    acquire(&swap_out_queue.lock);
    
    while(swap_out_queue.size){
      // Edge case handling
      while (flimit >= NOFILE){
        cprintf("flimit\n");
        wakeup1(swap_out_queue.reqchan);
        release(&swap_out_queue.lock);
        release(&ptable.lock);
        yield();
        acquire(&swap_out_queue.lock);
        acquire(&ptable.lock);
      }

      // Dequeue process from queue
      struct proc *p = dequeue(&swap_out_queue);

      // Edge case handling
      if(!select_victim_evict(p->pid)){
        wakeup1(swap_out_queue.reqchan);
        release(&swap_out_queue.lock);
        release(&ptable.lock);
        yield();
        acquire(&swap_out_queue.lock);
        acquire(&ptable.lock);
      }

      // When frame found set satified to true
      p->satisfied = 1;
    }

    wakeup1(swap_out_queue.reqchan);
    release(&swap_out_queue.lock);
    sleep(swap_out_queue.qchan, &ptable.lock);
  }
}

// Entry point of the swapin process
void swapin_proc(){
  sleep(swap_in_queue.qchan, &ptable.lock);
  while(1){
    // cprintf("\n\nEntering swapin\n");
    cprintf("|      Swapin Resumes       |  -  | -  |   Swapin queue is non-empty => start execution    |\n");
    acquire(&swap_in_queue.lock);
    
    while(swap_in_queue.size){
      struct proc *p = dequeue(&swap_in_queue);
      flimit--;
      release(&swap_in_queue.lock);
      release(&ptable.lock);
      
      char* mem = kalloc();
      read_page(p->pid,((p->trapva)>>12),mem);
      
      acquire(&swap_in_queue.lock);
      acquire(&ptable.lock);

      swapInMap(p->pgdir, (void *)PGROUNDDOWN(p->trapva),
                  PGSIZE, V2P(mem));
      wakeup1(p->chan);
    }
    // cprintf("\n\n");
    release(&swap_in_queue.lock);
    sleep(swap_in_queue.qchan, &ptable.lock);
  }

}


// Submits a request for a free page to the swapout process
void req_swapout(){
  struct proc* p = myproc();
  // cprintf("Submitted request to swap-out %d\n",p->pid);
  char my_pid[3];
  my_pid[2] = 0;
  my_pid[1] = '0' + p->pid%10;
  my_pid[0] = (p->pid/10 ? '0' + p->pid/10 : ' ');

  cprintf("| Submit Request to SwapOut |  %s | -  |         Process %s is queued to swapout           |\n", my_pid, my_pid);

  acquire(&ptable.lock);

  acquire(&swap_out_queue.lock);
  p->satisfied = 0;
  enqueue(&swap_out_queue, p); // Enqueues the process in the Swapout queue
  wakeup1(swap_out_queue.qchan); // Wakes up the Swapout process
  release(&swap_out_queue.lock);
  while(p->satisfied == 0) // Sleep process till not satisfied 
    sleep(swap_out_queue.reqchan, &ptable.lock);
  
  release(&ptable.lock);
  return;
}

// Submits a request to the swapin process
void req_swapin(){
  struct proc* p = myproc();
  // cprintf("submittes request to swap-in %d\n",p->pid);
  char my_pid[3];
  my_pid[2] = 0;
  my_pid[1] = '0' + p->pid%10;
  my_pid[0] = (p->pid/10 ? '0' + p->pid/10 : ' ');
  cprintf("| Submit Request to SwapIn  |  %s | -  |         Process %s is queued to swapin            |\n", my_pid, my_pid);

  acquire(&ptable.lock);

  acquire(&swap_in_queue.lock);
  enqueue(&swap_in_queue, p); // Enqueues the process in the Swapin queue
  wakeup1(swap_in_queue.qchan); // Wake up the Swapin process
  release(&swap_in_queue.lock);
  sleep((char*)p->pid, &ptable.lock); // Suspend the process

  release(&ptable.lock);
  return;
}

// On exit delete the swapout page-files created 
void delete_page_files()
{
  struct proc *p;

  acquire(&ptable.lock);
  
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->state == UNUSED)
      continue;
    
    if(p->pid==2 || p->pid==3){
      for(int fd=0; fd<NOFILE; fd++){
        if(p->ofile[fd]){
          struct file* f = p->ofile[fd];

          if(f->ref < 1){
            p->ofile[fd] = 0;
            continue;
          }

          release(&ptable.lock);
          
          if(f->ref == 1){
            int i = 0, k = 0;
            for(i=0; i<14; i++)
              if(f->name[i] == '_')
                break;
            
            for(k=0; k<14; k++)
              if(f->name[k] == '.')
                break;
            
            char my_pid[3], my_va[3];
            my_pid[0] = ((i==2) ? f->name[i-2] : ' ');
            my_pid[1] = f->name[i-1];
            my_pid[2] = 0;
            i++;
            my_va[0] = ((k-i==2) ? f->name[k-2] : ' ');
            my_va[1] = f->name[k-1];
            my_va[2] = 0;

            if(my_va[0] == ' ')
              cprintf("|    Page File Deletion     |  %s | %s |           Page file %s is deleted           |\n", my_pid, my_va, f->name);
            else
              cprintf("|    Page File Deletion     |  %s | %s |           Page file %s is deleted          |\n", my_pid, my_va, f->name);
          }
          delete_page(p->ofile[fd]->name);
          fileclose(f);
          flimit--;
          p->ofile[fd] = 0;

          acquire(&ptable.lock);
        }
      }
    }
  }
  
  cprintf("--------------------------------------------------------------------------------------------\n\n");
  cprintf("Total no. of Swap in: %d\n", swapincount);
  cprintf("Total no. of Swap out: %d\n", swapoutcount);
  swapincount = 0;
  swapoutcount = 0;

  release(&ptable.lock);
}

void
pinit(void)
{
  initlock(&ptable.lock, "ptable");
  // Initialize swap-out/in queues lock
  initlock(&swap_out_queue.lock, "swap_out_queue");
  initlock(&swap_in_queue.lock, "swap_in_queue");
}

// Must be called with interrupts disabled
int
cpuid() {
  return mycpu()-cpus;
}

// Must be called with interrupts disabled to avoid the caller being
// rescheduled between reading lapicid and running through the loop.
struct cpu*
mycpu(void)
{
  int apicid, i;
  
  if(readeflags()&FL_IF)
    panic("mycpu called with interrupts enabled\n");
  
  apicid = lapicid();
  // APIC IDs are not guaranteed to be contiguous. Maybe we should have
  // a reverse map, or reserve a register to store &cpus[i].
  for (i = 0; i < ncpu; ++i) {
    if (cpus[i].apicid == apicid)
      return &cpus[i];
  }
  panic("unknown apicid\n");
}

// Disable interrupts so that we are not rescheduled
// while reading proc from the cpu structure
struct proc*
myproc(void) {
  struct cpu *c;
  struct proc *p;
  pushcli();
  c = mycpu();
  p = c->proc;
  popcli();
  return p;
}

//PAGEBREAK: 32
// Look in the process table for an UNUSED proc.
// If found, change state to EMBRYO and initialize
// state required to run in the kernel.
// Otherwise return 0.
static struct proc*
allocproc(void)
{
  struct proc *p;
  char *sp;

  acquire(&ptable.lock);

  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    if(p->state == UNUSED)
      goto found;

  release(&ptable.lock);
  return 0;

found:
  p->state = EMBRYO;
  p->pid = nextpid++;

  release(&ptable.lock);

  // Allocate kernel stack.
  if((p->kstack = kalloc()) == 0){
    p->state = UNUSED;
    return 0;
  }
  sp = p->kstack + KSTACKSIZE;

  // Leave room for trap frame.
  sp -= sizeof *p->tf;
  p->tf = (struct trapframe*)sp;

  // Set up new context to start executing at forkret,
  // which returns to trapret.
  sp -= 4;
  *(uint*)sp = (uint)trapret;

  sp -= sizeof *p->context;
  p->context = (struct context*)sp;
  memset(p->context, 0, sizeof *p->context);
  p->context->eip = (uint)forkret;

  return p;
}

//PAGEBREAK: 32
// Set up first user process.
void
userinit(void)
{
  struct proc *p;
  extern char _binary_initcode_start[], _binary_initcode_size[];

  p = allocproc();
  
  initproc = p;
  if((p->pgdir = setupkvm()) == 0)
    panic("userinit: out of memory?");
  inituvm(p->pgdir, _binary_initcode_start, (int)_binary_initcode_size);
  p->sz = PGSIZE;
  memset(p->tf, 0, sizeof(*p->tf));
  p->tf->cs = (SEG_UCODE << 3) | DPL_USER;
  p->tf->ds = (SEG_UDATA << 3) | DPL_USER;
  p->tf->es = p->tf->ds;
  p->tf->ss = p->tf->ds;
  p->tf->eflags = FL_IF;
  p->tf->esp = PGSIZE;
  p->tf->eip = 0;  // beginning of initcode.S

  safestrcpy(p->name, "initcode", sizeof(p->name));
  p->cwd = namei("/");

  // this assignment to p->state lets other cores
  // run this process. the acquire forces the above
  // writes to be visible, and the lock is also needed
  // because the assignment might not be atomic.
  acquire(&ptable.lock);

  p->state = RUNNABLE;

  release(&ptable.lock);

  // Initialize swap-out queue
  acquire(&swap_out_queue.lock);
  swap_out_queue.front = 0;
  swap_out_queue.rear = NPROC - 1;
  swap_out_queue.size = 0;
  swap_out_queue.qchan = swap_out_queue.reqchan = (void*)0xA8080;
  release(&swap_out_queue.lock);

  // Initialize swap-in queue
  acquire(&swap_in_queue.lock);
  swap_in_queue.front = 0;
  swap_in_queue.rear = NPROC - 1;
  swap_in_queue.size = 0;
  swap_in_queue.qchan = swap_in_queue.reqchan = (void*)0xB8081;
  release(&swap_in_queue.lock);

  // Initialize limit on file
  flimit = 2;
}

// Grow current process's memory by n bytes.
// Return 0 on success, -1 on failure.
int
growproc(int n)
{
  uint sz;
  struct proc *curproc = myproc();

  sz = curproc->sz;
  if(n > 0){
    if((sz = allocuvm(curproc->pgdir, sz, sz + n)) == 0)
      return -1;
  } else if(n < 0){
    if((sz = deallocuvm(curproc->pgdir, sz, sz + n)) == 0)
      return -1;
  }
  curproc->sz = sz;
  switchuvm(curproc);
  return 0;
}

// Create a new process copying p as the parent.
// Sets up stack to return as if from system call.
// Caller must set state of returned proc to RUNNABLE.
int
fork(void)
{
  int i, pid;
  struct proc *np;
  struct proc *curproc = myproc();

  // Allocate process.
  if((np = allocproc()) == 0){
    return -1;
  }

  // Copy process state from proc.
  if((np->pgdir = copyuvm(curproc->pgdir, curproc->sz)) == 0){
    kfree(np->kstack);
    np->kstack = 0;
    np->state = UNUSED;
    return -1;
  }
  np->sz = curproc->sz;
  np->parent = curproc;
  *np->tf = *curproc->tf;

  // Clear %eax so that fork returns 0 in the child.
  np->tf->eax = 0;

  for(i = 0; i < NOFILE; i++)
    if(curproc->ofile[i])
      np->ofile[i] = filedup(curproc->ofile[i]);
  np->cwd = idup(curproc->cwd);

  safestrcpy(np->name, curproc->name, sizeof(curproc->name));

  pid = np->pid;

  acquire(&ptable.lock);

  np->state = RUNNABLE;

  release(&ptable.lock);

  return pid;
}

// Exit the current process.  Does not return.
// An exited process remains in the zombie state
// until its parent calls wait() to find out it exited.
void
exit(void)
{
  struct proc *curproc = myproc();
  struct proc *p;
  int fd;

  if(curproc == initproc)
    panic("init exiting");

  // Close all open files.
  for(fd = 0; fd < NOFILE; fd++){
    if(curproc->ofile[fd]){
      fileclose(curproc->ofile[fd]);
      curproc->ofile[fd] = 0;
    }
  }

  // If process runs on shell, delete swapped out page files
  if(curproc->parent && curproc->parent->pid == 4)
    delete_page_files();

  begin_op();
  iput(curproc->cwd);
  end_op();
  curproc->cwd = 0;

  acquire(&ptable.lock);

  // Parent might be sleeping in wait().
  wakeup1(curproc->parent);

  // Pass abandoned children to init.
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->parent == curproc){
      p->parent = initproc;
      if(p->state == ZOMBIE)
        wakeup1(initproc);
    }
  }

  // Jump into the scheduler, never to return.
  curproc->state = ZOMBIE;
  sched();
  panic("zombie exit");
}

// Wait for a child process to exit and return its pid.
// Return -1 if this process has no children.
int
wait(void)
{
  struct proc *p;
  int havekids, pid;
  struct proc *curproc = myproc();
  
  acquire(&ptable.lock);
  for(;;){
    // Scan through table looking for exited children.
    havekids = 0;
    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
      if(p->parent != curproc)
        continue;
      havekids = 1;
      if(p->state == ZOMBIE){
        // Found one.
        pid = p->pid;
        kfree(p->kstack);
        p->kstack = 0;
        freevm(p->pgdir);
        p->pid = 0;
        p->parent = 0;
        p->name[0] = 0;
        p->killed = 0;
        p->state = UNUSED;
        release(&ptable.lock);
        return pid;
      }
    }

    // No point waiting if we don't have any children.
    if(!havekids || curproc->killed){
      release(&ptable.lock);
      return -1;
    }

    // Wait for children to exit.  (See wakeup1 call in proc_exit.)
    sleep(curproc, &ptable.lock);  //DOC: wait-sleep
  }
}

//PAGEBREAK: 42
// Per-CPU process scheduler.
// Each CPU calls scheduler() after setting itself up.
// Scheduler never returns.  It loops, doing:
//  - choose a process to run
//  - swtch to start running that process
//  - eventually that process transfers control
//      via swtch back to the scheduler.
void
scheduler(void)
{
  struct proc *p;
  struct cpu *c = mycpu();
  c->proc = 0;
  
  for(;;){
    // Enable interrupts on this processor.
    sti();

    // Loop over process table looking for process to run.
    acquire(&ptable.lock);
    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
      if(p->state != RUNNABLE)
        continue;

      // Switch to chosen process.  It is the process's job
      // to release ptable.lock and then reacquire it
      // before jumping back to us.
      c->proc = p;
      switchuvm(p);
      p->state = RUNNING;

      swtch(&(c->scheduler), p->context);
      switchkvm();

      // Process is done running for now.
      // It should have changed its p->state before coming back.
      c->proc = 0;
    }
    release(&ptable.lock);

  }
}

// Enter scheduler.  Must hold only ptable.lock
// and have changed proc->state. Saves and restores
// intena because intena is a property of this
// kernel thread, not this CPU. It should
// be proc->intena and proc->ncli, but that would
// break in the few places where a lock is held but
// there's no process.
void
sched(void)
{
  int intena;
  struct proc *p = myproc();

  if(!holding(&ptable.lock))
    panic("sched ptable.lock");
  if(mycpu()->ncli != 1)
    panic("sched locks");
  if(p->state == RUNNING)
    panic("sched running");
  if(readeflags()&FL_IF)
    panic("sched interruptible");
  intena = mycpu()->intena;
  swtch(&p->context, mycpu()->scheduler);
  mycpu()->intena = intena;
}

// Give up the CPU for one scheduling round.
void
yield(void)
{
  acquire(&ptable.lock);  //DOC: yieldlock
  myproc()->state = RUNNABLE;
  sched();
  release(&ptable.lock);
}

// A fork child's very first scheduling by scheduler()
// will swtch here.  "Return" to user space.
void
forkret(void)
{
  static int first = 1;
  // Still holding ptable.lock from scheduler.
  release(&ptable.lock);

  if (first) {
    // Some initialization functions must be run in the context
    // of a regular process (e.g., they call sleep), and thus cannot
    // be run from main().
    first = 0;
    iinit(ROOTDEV);
    initlog(ROOTDEV);
    // Create two kernel processes for swap-in and swap-out as soon as OS boots
    create_kernel_process("swapinprocess",swapin_proc);
    create_kernel_process("swapoutprocess",swapout_proc);
  }

  // Return to "caller", actually trapret (see allocproc).
}

// Atomically release lock and sleep on chan.
// Reacquires lock when awakened.
void
sleep(void *chan, struct spinlock *lk)
{
  struct proc *p = myproc();
  
  if(p == 0)
    panic("sleep");

  if(lk == 0)
    panic("sleep without lk");

  // Must acquire ptable.lock in order to
  // change p->state and then call sched.
  // Once we hold ptable.lock, we can be
  // guaranteed that we won't miss any wakeup
  // (wakeup runs with ptable.lock locked),
  // so it's okay to release lk.
  if(lk != &ptable.lock){  //DOC: sleeplock0
    acquire(&ptable.lock);  //DOC: sleeplock1
    release(lk);
  }
  // Go to sleep.
  p->chan = chan;
  p->state = SLEEPING;

  sched();

  // Tidy up.
  p->chan = 0;

  // Reacquire original lock.
  if(lk != &ptable.lock){  //DOC: sleeplock2
    release(&ptable.lock);
    acquire(lk);
  }
}

//PAGEBREAK!
// Wake up all processes sleeping on chan.
// The ptable lock must be held.
static void
wakeup1(void *chan)
{
  struct proc *p;

  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    if(p->state == SLEEPING && p->chan == chan)
      p->state = RUNNABLE;
}

// Wake up all processes sleeping on chan.
void
wakeup(void *chan)
{
  acquire(&ptable.lock);
  wakeup1(chan);
  release(&ptable.lock);
}

// Kill the process with the given pid.
// Process won't exit until it returns
// to user space (see trap in trap.c).
int
kill(int pid)
{
  struct proc *p;

  acquire(&ptable.lock);
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->pid == pid){
      p->killed = 1;
      // Wake process from sleep if necessary.
      if(p->state == SLEEPING)
        p->state = RUNNABLE;
      release(&ptable.lock);
      return 0;
    }
  }
  release(&ptable.lock);
  return -1;
}

//PAGEBREAK: 36
// Print a process listing to console.  For debugging.
// Runs when user types ^P on console.
// No lock to avoid wedging a stuck machine further.
void
procdump(void)
{
  static char *states[] = {
  [UNUSED]    "unused",
  [EMBRYO]    "embryo",
  [SLEEPING]  "sleep ",
  [RUNNABLE]  "runble",
  [RUNNING]   "run   ",
  [ZOMBIE]    "zombie"
  };
  int i;
  struct proc *p;
  char *state;
  uint pc[10];

  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->state == UNUSED)
      continue;
    if(p->state >= 0 && p->state < NELEM(states) && states[p->state])
      state = states[p->state];
    else
      state = "???";
    cprintf("%d %s %s", p->pid, state, p->name);
    if(p->state == SLEEPING){
      getcallerpcs((uint*)p->context->ebp+2, pc);
      for(i=0; i<10 && pc[i] != 0; i++)
        cprintf(" %p", pc[i]);
    }
    cprintf("\n");
  }
}
