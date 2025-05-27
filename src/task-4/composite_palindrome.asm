section .text
    global check_palindrome
    global composite_palindrome

check_palindrome:
    enter 0, 0
    ; Save callee-saved registers
    push esi
    push edi
    push ebx

    ; Load parameters
    mov esi, [ebp + 8]  ; esi = str (left pointer)
    mov ebx, [ebp + 12] ; ebx = len

    ; Handle len = 0
    cmp ebx, 0          ; Check if len is 0 (Replaced test ebx, ebx)
    jnz LenNotZero_PCHK ; If len != 0, continue
    jmp ReturnTrue_PCHK ; If len == 0, is a palindrome

LenNotZero_PCHK:
    ; Initialize edi (right pointer) to str + len - 1
    mov edi, esi        ; edi = str
    add edi, ebx        ; edi = str + len
    dec edi             ; edi = str + len - 1 (points to last char)

CompareLoop_PCHK:
    ; Check if pointers crossed or met
    cmp esi, edi
    jl PointersNotCrossed_PCHK ; If esi < edi, continue comparison
    jmp ReturnTrue_PCHK        ; If esi >= edi, it's a palindrome

PointersNotCrossed_PCHK:
    ; Load chars from both ends
    mov al, [esi]       ; al = char from left
    mov ah, [edi]       ; ah = char from right

    ; Compare characters
    cmp al, ah
    je CharactersMatch_PCHK   ; If chars are equal, continue
    jmp ReturnFalse_PCHK      ; If chars are not equal, not a palindrome

CharactersMatch_PCHK:
    ; Move pointers inwards
    inc esi             ; Move left pointer right
    dec edi             ; Move right pointer left

    jmp CompareLoop_PCHK   ; Repeat comparison

ReturnTrue_PCHK:
    mov eax, 1          ; Return 1 (true)
    jmp ExitCheckPalindrome_PCHK

ReturnFalse_PCHK:
    mov eax, 0       ; Return 0 (false)
    ; Fall through to ExitCheckPalindrome_PCHK

ExitCheckPalindrome_PCHK:
    ; Restore callee-saved registers
    pop ebx
    pop edi
    pop esi

    leave               ; Restore ebp and esp
    ret                 ; Return to caller

composite_palindrome:
    enter 0, 0
    xor eax, eax        ; Always returns 0
    leave
    ret
