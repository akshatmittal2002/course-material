#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_draw(void)
{
  char* buf;
  uint size;

  // problem in allocation of integer or buffer
  if(argint(1, (void*) &size) < 0)
    return -1;
  
  if(argptr(0, (void*) &buf, size) < 0)
    return -1;

  // ASCII art
  const char ascii_art[] = "\
          _                   _               _              _       _        _                 _       \n\
        / /\\                /\\_\\            / /\\           / /\\    / /\\     / /\\              /\\ \\     \n\
       / /  \\              / / /  _        / /  \\         / / /   / / /    / /  \\             \\_\\ \\    \n\
      / / /\\ \\            / / /  /\\_\\     / / /\\ \\__     / /_/   / / /    / / /\\ \\            /\\__ \\   \n\
     / / /\\ \\ \\          / / /__/ / /    / / /\\ \\___\\   / /\\ \\__/ / /    / / /\\ \\ \\          / /_ \\ \\  \n\
    / / /  \\ \\ \\        / /\\_____/ /     \\ \\ \\ \\/___/  / /\\ \\___\\/ /    / / /  \\ \\ \\        / / /\\ \\ \\ \n\
   / / /___/ /\\ \\      / /\\_______/       \\ \\ \\       / / /\\/___/ /    / / /___/ /\\ \\      / / /  \\/_/ \n\
  / / /_____/ /\\ \\    / / /\\ \\ \\      _    \\ \\ \\     / / /   / / /    / / /_____/ /\\ \\    / / /        \n\
 / /_________/\\ \\ \\  / / /  \\ \\ \\    /_/\\__/ / /    / / /   / / /    / /_________/\\ \\ \\  / / /         \n\
/ / /_       __\\ \\_\\/ / /    \\ \\ \\   \\ \\/___/ /    / / /   / / /    / / /_       __\\ \\_\\/_/ /          \n\
\\_\\___\\     /____/_/\\/_/      \\_\\_\\   \\_____\\/     \\/_/    \\/_/     \\_\\___\\     /____/_/\\_\\/           \n\
";

  // size of ascii art
  int art_size = sizeof(ascii_art);

  // if size of ascii art is more that available
  if(size < art_size)
    return -1;
  
  // copy art to buffer
  for(int i = 0; i < art_size; i ++)
    buf[i] = ascii_art[i];
  
  // return number of bytes copied, i.e., 1*(size of art)
  return art_size;
}
