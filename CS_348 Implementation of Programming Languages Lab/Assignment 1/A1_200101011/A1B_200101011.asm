global  main                        ;must be declared for linker
extern  printf                      ;import printf and scanf
extern  scanf

;data section starts
section .data
    msg1:       dq  "Enter N: ", 0
    msg2:       dq  "Enter Matrix:", 0
    scan_n:     dq  "%d%*c", 0
    msg3:       dq  "Transpose Matrix:", 0
    print_n:    dq  "%5d ", 0
    new_line:   dq  10, 0

;bss section starts
section .bss
    size:   resq    1               ;to store size of matrix
    buff:   resq    4096            ;to store matrix

;text section starts
section .text
main:                               ;tells linker the entry point
    push    rbp                     ;keeps the stack aligned
    mov     rbp,    rsp             ;rbp now points to top of stack

    ;prompt use to enter size of matrix
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
    
    ;prompt user to enter matrix
    xor     rax,    rax
    lea     rdi,    [msg2]          ;printf("Enter Matrix:\n");
    call    printf
    xor     rax,    rax
    lea     rdi,    [new_line]
    call    printf

    ;take user input of matrix and store it in memory
    xor     r13,    r13             ;i = 0
    xor     r15,    r15             ;temp = 0
outer_scan:
    xor     r14,    r14             ;j = 0
inner_scan:
    ;scan an element
    xor     rax,    rax
    lea     rdi,    [scan_n]        ;scanf("%d%*c",&buff[i][j])
    lea     rsi,    [buff + r15*8]
    call    scanf
    inc     r15                     ;temp++ ;next memory location
    inc     r14                     ;j++
    cmp     r14,    r12             ;if j < size, loop
    jl      inner_scan
    inc     r13                     ;i++
    cmp     r13,    r12             ;if i < size, loop
    jl      outer_scan

    ;find tranpose of the matrix
    xor     r13,    r13             ;i = 0
outer_loop:
    mov     r14,    r13
    inc     r14                     ;j=i+1
inner_loop:
    ;swap mat[i][j] and mat[j][i]
    mov     r10,    r13             ;r10 <= [i][j] = i*size + j
    imul    r10,    r12
    add     r10,    r14
    mov     r11,    r14             ;r11 <= [j][i] = j*size + i
    imul    r11,    r12
    add     r11,    r13
    ;swap now
    mov     r8,     [buff+r10*8]    ;temp1 = mat[i][j]
    mov     r9,     [buff+r11*8]    ;temp2 = mat[j][i]
    mov     [buff+r11*8],   r8      ;mat[j][i] = temp1
    mov     [buff+r10*8],   r9      ;mat[i][j] = temp2
    inc     r14                     ;j++
    cmp     r14,    r12             ;if j < size, loop
    jl      inner_loop
    inc     r13                     ;i++
    cmp     r13,    r12             ;if i < size, loop
    jl      outer_loop

    ;print matrix transpose
    xor     rax,    rax
    lea     rdi,    [msg3]          ;printf("Transpose Matrix:\n");
    call    printf
    xor     rax,    rax
    lea     rdi,    [new_line]
    call    printf

    ;print resultant matrix
    xor     r13,    r13             ;i = 0
    xor     r15,    r15             ;temp = 0
outer_print:
    xor     r14,    r14             ;j = 0
inner_print:
    ;print an element
    xor     rax,    rax
    lea     rdi,    [print_n]       ;printf("%5d ",buff[i][j]);
    mov     rsi,    [buff + r15*8]
    call    printf
    inc     r15                     ;temp++ ;next memory location
    inc     r14                     ;j++
    cmp     r14,    r12             ;if j < size, loop
    jl      inner_print
    ;print new line
    xor     rax,    rax
    lea     rdi,    [new_line]      ;printf("\n");
    call    printf
    inc     r13                     ;i++
    cmp     r13,    r12             ;if i < size, loop
    jl      outer_print

    ;exit program
exit:
    mov     rsp,    rbp             ;restore stack pointer
    pop     rbp                     ;restore rbp
    ret                             ;return