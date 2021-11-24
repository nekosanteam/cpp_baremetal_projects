    .text
    .global _start

    //
_start:
    // frame pointer のクリア.
    xor     %ebp, %ebp
    // argc
    mov     (%rsp), %edi
    // argv
    lea     8(%rsp), %rsi
    // envp
    lea     16(%rsp, %rdi, 8), %rdx
    xor     %eax, %eax
    call    main

    mov     %eax, %edi
    xor     %eax, %eax
    call    _exit

_exit:
    mov     $60, %eax
    xor     %rdi, %rdi
    syscall
