section .text
global sort

sort:
    enter 0, 0              ; Create new stack frame
    ; Save registers that will be modified and restored
    push ecx                ; Save register ecx
    push edi                ; Save register edi
    push eax                ; Save register eax
                          ; No-operation for structural difference

    ; Initializations:
    ; eax = target_val (search value)
    ; ecx = current_tail_of_sorted_list
    ; ebx = head_of_sorted_list (return value container)
    mov eax, 1              ; eax (target_val) = 1
    sub ecx, ecx            ; ecx (current_tail_of_sorted_list) = 0 (NULL)
    mov ebx, 0              ; ebx (head_of_sorted_list) = 0 (NULL)

OuterLoop_Start:            ; Label for the outer loop
     
    ; Check if target_val (eax) has exceeded n ([ebp+8])
    ; edx = n (total number of elements)
    mov edx, [ebp + 8]      ; edx = n
    cmp eax, edx            ; Compare eax (target_val) with edx (n)
    ; If target_val <= n, continue loop, else jump to OuterLoop_End
    jle ContinueOuterLoop_L1
    jmp OuterLoop_End       ; Jump to the end of the main loop

ContinueOuterLoop_L1:
     
    ; Inner loop: Iterate through nodes to find node->val == target_val (eax)
    ; edx = n (used as inner loop counter)
    ; edi = node_array_ptr (pointer to the array of nodes)
    mov edx, [ebp + 8]      ; edx = number of nodes (inner loop counter)
    mov edi, [ebp + 12]     ; edi = pointer to the node array

InnerLoop_Start:            ; Label for the inner loop
    ; esi = current_node_value ([edi])
    ; edi = current_node_pointer
    mov esi, [edi]          ; esi = value of the current node
    cmp esi, eax            ; Compare esi (node_value) with eax (target_val)
    ; If node_value != target_val, continue search, else jump to Node_Found
    jne ContinueInnerSearch_L2
    jmp Node_Found          ; Jump to process the found node

ContinueInnerSearch_L2:
     
    ; Mismatch, advance to the next node in the array
    lea edi, [edi+8]        ; edi += 8 (current_node_pointer)
    sub edx, 1              ; edx-- (inner loop counter)
    jmp InnerLoop_Start     ; Continue the inner loop

Node_Found:                 ; Label for when a node is found
    ; edi (current_node_pointer) points to the node where node->val == target_val (eax).
    ; This is the node to be linked.

    ; Check if current_tail_of_sorted_list (ecx) is NULL
    cmp ecx, 0
    ; If ecx == 0, process as first element, else jump to Link_To_Previous
    je ProcessAsFirstElement_L3
    jmp Link_To_Previous    ; Jump to link to the previous tail

ProcessAsFirstElement_L3:
     
    ; current_tail_of_sorted_list (ecx) is NULL.
    ; The found node (edi) is the first node.
    ; ebx = head_of_sorted_list
    mov ebx, edi            ; ebx (head_of_sorted_list) = edi (found_node_ptr)
    mov ecx, edi            ; ecx (current_tail_of_sorted_list) = edi (found_node_ptr)
    jmp PrepareNextTarget   ; Jump to prepare for the next target value

Link_To_Previous:           ; Label for linking to the previous tail
    ; current_tail_of_sorted_list (ecx) is not NULL.
    ; Link the previous tail to this newly found node.
    mov dword [ecx + 4], edi  ; [ecx+4] (tail->next_ptr) = edi (found_node_ptr)
    mov ecx, edi              ; Update ecx (current_tail_of_sorted_list) = edi (found_node_ptr)
     

PrepareNextTarget:          ; Label for preparing the next search
    ; eax = target_val
    add eax, 1              ; Increment eax (target_val)
    jmp OuterLoop_Start     ; Go back to the outer loop

OuterLoop_End:              ; Label for the end of the outer loop
     
    ; ecx (current_tail_of_sorted_list / last_node_ptr) points to the last linked node.
    ; The 'next' field of this last node should be NULL.
    cmp ecx, 0              ; Check if ecx (last_node_ptr) is NULL
    ; If ecx != 0, ensure next is NULL, else jump to Cleanup_And_Return
    jne EnsureLastNextIsNull_L4
    jmp Cleanup_And_Return  ; Jump to cleanup and return

EnsureLastNextIsNull_L4:
     
    ; ecx is not NULL, so there is at least one node in the sorted list.
    mov dword [ecx + 4], 0  ; Set (last_node_ptr)->next = NULL explicitly.
     

Cleanup_And_Return:         ; Label for cleanup and function return
    ; The return value (head of the sorted list) is currently in the EBX register.
    ; It must be moved to the EAX register before 'ret'.

    ; Restore previously saved registers
    pop eax
    pop edi
    pop ecx

    ; EBX (physical register) holds the result (head of the sorted list).
    ; EAX (physical register) must contain the result for the RET instruction.
    mov eax, ebx            ; Move result from EBX to EAX.
    
    leave                   ; Restore stack frame: mov esp, ebp; pop ebp
    ret                     ; Return from function. Result is now in EAX.
