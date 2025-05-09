section .text
global kfib

kfib:
    ; create a new stack frame
    enter 0, 0
    xor eax, eax
    leave
    ret

