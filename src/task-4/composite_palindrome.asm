section .text
global check_palindrome
global composite_palindrome

check_palindrome:
    ; create a new stack frame
    enter 0, 0
    xor eax, eax
    leave
    ret

composite_palindrome:
    ; create a new stack frame
    enter 0, 0
    xor eax, eax
    leave
    ret

