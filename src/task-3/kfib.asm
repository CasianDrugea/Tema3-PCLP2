section .text
global kfib


kfib:
    ; Create a new stack frame
    enter 0, 0

    ; Save callee-saved registers that will be used
    push ebx
    push esi
    push edi

    ; Load arguments into registers
    mov esi, [ebp + 8]  ; esi = n
    mov ebx, [ebp + 12] ; ebx = K

    ; Base Case 1: n < K
    cmp esi, ebx        ; Compare n with K
    jge CheckEqualsCase_N ; If n >= K, skip handling for n < K
    jmp case_n_less_than_K ; Explicit jump to handle n < K

CheckEqualsCase_N:
    ; Base Case 2: n = K
    cmp esi, ebx        ; Compare n with K
    jne RecursiveCase_N   ; If n != K (and we know n >= K from above, so n > K), jump to recursive case
    jmp case_n_equals_K   ; Explicit jump to handle n = K

RecursiveCase_N:
    ; Recursive Case: n > K (this block is reached if n > K)
    ; Calculate KFib(n-1,K) + KFib(n-2,K) + ... + KFib(n-K,K)
    
    mov edi, 0          ; edi will store the sum, initialize sum = 0
    mov ecx, 1          ; ecx will be the loop counter 'i', from 1 to K

recursive_sum_loop:
    cmp ecx, ebx        ; Compare i with K
    jle LoopBody_N      ; If i <= K, continue with the loop body
    jmp end_recursive_sum_loop ; Loop is finished, jump to end

LoopBody_N:

    push edi            ; Save current sum (edi) onto the stack
    push ecx            ; Save current loop counter 'i' (ecx) onto the stack

    ; Prepare arguments for the recursive call kfib(n-i, K)
    ; Argument K for the recursive call is in ebx
    push ebx            ; Push K onto the stack for the recursive call
    
    ; Calculate n-i for the recursive call
    mov eax, esi        ; eax = current n (from esi)
    sub eax, ecx        ; eax = n - i (using current 'i' from ecx)
    push eax            ; Push n-i onto the stack for the recursive call
    
    call kfib           ; Recursively call kfib(n-i, K). Result will be in eax.
    add esp, 8          ; Clean up the 2 arguments (n-i, K) pushed for the call (2 * 4 bytes)

    ; After the recursive call returns, eax contains its result.
    pop ecx             ; Restore loop counter 'i' from the stack
    pop edi             ; Restore sum from the stack
    
    add edi, eax        ; Add the result of the recursive call to the sum (sum += result)

    add ecx, 1           ; Increment loop counter i (i++)
    jmp recursive_sum_loop ; Continue to the next iteration

end_recursive_sum_loop:
    mov eax, edi        ; The final sum (in edi) is the result for n > K
    jmp exit     ; Jump to the common exit point

case_n_less_than_K:
    mov eax, 0       ; Result is 0 if n < K
    jmp exit     ; Jump to the common exit point

case_n_equals_K:
    mov eax, 1          ; Result is 1 if n = K
    ; Fall through to exit

exit:
    pop edi
    pop esi
    pop ebx

    ; Destroy the stack frame and return
    leave
    ret
