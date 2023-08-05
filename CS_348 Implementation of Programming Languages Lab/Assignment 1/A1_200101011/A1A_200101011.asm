global  main                        ;must be declared for linker
extern  printf                      ;import printf and scanf
extern  scanf

;data section starts
section .data
    msg1:       dq  "Enter N: ", 0
    msg2:       dq  "Enter K: ", 0
    msg3:       dq  "Enter Array: ", 0
    scan_n:     dq  "%d%*c", 0
    msg4:       dq  "Kth largest element: %d", 0
    msg5:       dq  "Indices: ", 0
    print_n:    dq  "%d ", 0
    new_line:   dq  10, 0
    msg6:       dq  "Invalid K, Enter between 1 and N only", 0

;bss section starts
section .bss
    size:   resq    1               ;to store size of array
    k:      resq    1               ;to store k
    arr1:   resq    1023            ;to store array1
    arr2:   resq    1023            ;to store sorted array
    ans_k:  resq    1               ;to store kth largest element
    ans:    resq    1023            ;to store indices of kth largest element
    ans_n:  resq    1               ;to store size of ans array

;text section starts
section .text
main:                               ;tells linker the entry point
    push    rbp                     ;keeps the stack aligned
    mov     rbp,    rsp             ;rbp now points to top of stack

    ;prompt use to enter size of array
    xor     rax,    rax
    lea     rdi,    [msg1]          ;printf("Enter N: ");
    call    printf

    ;scan the input and store it in memory
    xor     rax,    rax
    lea     rdi,    [scan_n]        ;scanf("%d%*c",&size);
    lea     rsi,    [size]
    call    scanf

    ;if size <= 0, exit
    mov     r12,    [size]          ;copy size in a register
    cmp     r12,    0
    jle     exit

    ;prompt use to enter k
    xor     rax,    rax
    lea     rdi,    [msg2]          ;printf("Enter K: ");
    call    printf

    ;scan the input and store it in memory
    xor     rax,    rax
    lea     rdi,    [scan_n]        ;scanf("%d%*c",&k);
    lea     rsi,    [k]
    call    scanf

    ;if k < 1 or k > size, exit
    mov     r13,    [k]             ;;copy k in a register
    cmp     r13,    1
    jl      pre_exit
    cmp     r13,    r12
    jg      pre_exit
    
    ;prompt user to enter array
    xor     rax,    rax
    lea     rdi,    [msg3]          ;printf("Enter Array: ");
    call    printf

    ;take user input of array and store it in memory
    xor     r14,    r14             ;i = 0
outer_scan:
    ;scan an element
    xor     rax,    rax
    lea     rdi,    [scan_n]        ;scanf("%d%*c",&arr1[i]);
    lea     rsi,    [arr1 + r14*8]
    call    scanf
    mov     r8,     [arr1+r14*8]    ;copy in arr2
    mov     [arr2+r14*8],   r8
    inc     r14                     ;i++
    cmp     r14,    r12             ;if i < size, loop
    jl      outer_scan

    ;sort arr2 using bubble sort
    mov     rcx,    [size]          ;rcx <= size
    dec     rcx                     ;size-- ;outer loop will run size-1 times
nextloop:
    mov     rbx,    rcx             ;inner loop will run size-i-1 times
    mov     rsi,    0               ;temp = 0
nextcomp:
    mov     rax,    [arr2 + rsi]    ;if arr[j] < arr[j+1], swap, else noswap
    mov     rdx,    [arr2 + rsi + 8]
    cmp     rax,    rdx
    jge     noswap
    mov     [arr2+rsi],     rdx
    mov     [arr2+rsi + 8], rax
noswap:
    add     rsi,    8               ;temp += 8 ;since each number is 64 bit
    dec     rbx                     ;inner loop
    jnz     nextcomp
    dec     rcx                     ;outer loop
    jnz     nextloop

    ;find kth element of arr2
    mov     rbx,    [k]             ;rbx <= k-1 ;due to 0-based indexing
    dec     rbx
    imul    rbx,    8
    mov     rax,    [arr2+rbx]      ;store arr2[k-1] in ans_k
    mov     [ans_k],    rax

    ;find indices of kth largest element in arr1 and store in ans array
    mov     r12,    [size]          ;r12 <= size
    mov     rax,    [ans_k]         ;rax <= ans_k
    xor     r8,     r8              ;i = 0
    xor     r9,     r9              ;j = 0
traverse:
    ;if arr1[i] == ans_k, store index(i+1) in ans[j], else next iteration
    mov     rbx,    [arr1 + r8*8]
    cmp     rbx,    rax
    jne     no_store
    inc     r8
    mov     [ans + r9*8],   r8      ;store i+1 in ans[j]
    dec     r8
    inc     r9                      ;j++
no_store:
    inc     r8                      ;i++
    cmp     r8,     r12             ;if i < size, loop
    jl      traverse
    mov     [ans_n],    r9          ;store j for size of ans array

    ; print the results
    xor     rax,    rax
    lea     rdi,    [msg4]          ;printf("Kth largest element: %d\n");
    mov     rsi,    [ans_k]
    call    printf
    xor     rax,    rax
    lea     rdi,    [new_line]
    call    printf

    ;print the indices
    xor     rax,    rax
    lea     rdi,    [msg5]          ;printf("Indeices: ");
    call    printf

    ;print the ans array
    xor     r14,    r14             ;i = 0
    mov     r12,    [ans_n]         ;r12 <= ans_size
outer_print:
    ;print an element
    xor     rax,    rax
    lea     rdi,    [print_n]       ;printf("%d ");
    mov     rsi,    [ans+r14*8]
    call    printf
    inc     r14                     ;i++
    cmp     r14,    r12             ;if i < ans_size, loop
    jl      outer_print
    ;print new line
    xor     rax,    rax
    lea     rdi,    [new_line]      ;printf("\n");
    call    printf

    jmp exit
    ;print error message if k < 1 or k > size
pre_exit:
    xor     rax,    rax
    lea     rdi,    [msg6]          ;printf("Invalid K, Enter between 1 and N only\n");
    call    printf
    xor     rax,    rax
    lea     rdi,    [new_line]
    call    printf
    ;exit program
exit:
    mov     rsp,    rbp             ;restore stack pointer
    pop     rbp                     ;restore rbp
    ret                             ;return