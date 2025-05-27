section .data
    delimiters_str: db " ,.", 10, 0

section .text
    global get_words
    global sort

    extern qsort
    extern strlen
    extern strcmp

compare_words:
    enter 0,0           ; Setup frame
    push ebx            ; Save ebx
    push esi            ; Save esi
    push edi            ; Save edi

    ; Get char** args
    mov esi, [ebp + 8]  ; esi = char** a
    mov edi, [ebp + 12] ; edi = char** b

    ; Dereference to get char*
    mov esi, [esi]      ; esi = char* a
    mov edi, [edi]      ; edi = char* b

    ; Check str_a (esi) for NULL
    cmp esi, 0
    jne CompStrANotNull    ; Str_a not NULL?
    ; Str_a is NULL
    cmp edi, 0
    jne CompStrANullStrBNotNull ; Str_b not NULL?
    ; Both NULL
    xor eax, eax        ; Result 0 (equal)
    jmp CompCleanup     ; To cleanup

CompStrANullStrBNotNull:
    ; Str_a NULL, Str_b not NULL
    mov eax, 1          ; Result 1 (a > b for sort)
    jmp CompCleanup     ; To cleanup

CompStrANotNull:
    ; Str_a not NULL
    cmp edi, 0
    jne CompBothNotNull ; Str_b not NULL?
    ; Str_a not NULL, Str_b NULL
    mov eax, -1         ; Result -1 (a < b for sort)
    jmp CompCleanup     ; To cleanup

CompBothNotNull:
    ; Both strings not NULL, compare lengths
    push esi            ; Arg: str_a for strlen
    call strlen
    add esp, 4          ; Pop arg
    mov ebx, eax        ; ebx = len(str_a)

    push edi            ; Arg: str_b for strlen
    call strlen
    add esp, 4          ; Pop arg
                        ; eax = len(str_b)

    cmp ebx, eax        ; Compare len(str_a) with len(str_b)
    jl CompLenAShorter  ; len_a < len_b?
    jg CompLenALonger   ; len_a > len_b?

    ; Lengths equal, strcmp
    push edi            ; Arg2: str_b for strcmp
    push esi            ; Arg1: str_a for strcmp
    call strcmp
    add esp, 8          ; Pop 2 args
                        ; eax has strcmp result
    jmp CompCleanup     ; To cleanup

CompLenAShorter:
    mov eax, -1         ; len_a < len_b, result -1
    jmp CompCleanup     ; To cleanup

CompLenALonger:
    mov eax, 1          ; len_a > len_b, result 1
    jmp CompCleanup     ; To cleanup

CompCleanup:
    pop edi             ; Restore edi
    pop esi             ; Restore esi
    pop ebx             ; Restore ebx
    leave               ; Restore frame
    ret                 ; Return (result in eax)


sort:
    enter 0,0           ; Setup frame

    ; Call qsort(base, num, size, comparator)
    push compare_words  ; Arg4: comparator
    push dword [ebp + 16]; Arg3: element_size
    push dword [ebp + 12]; Arg2: num_elements
    push dword [ebp + 8] ; Arg1: array_base
    call qsort
    add esp, 16         ; Pop 4 args

    leave               ; Restore frame
    ret                 ; Return

is_delimiter_internal:
    push ebp
    mov ebp, esp        ; Setup frame
    push edi            ; Save edi (iterator)

    mov edi, delimiters_str ; edi = ptr to delimiters

DelimiterScanLoop:
    mov dl, [edi]       ; dl = current delimiter char
    cmp dl, 0           ; End of delimiters_str?
    jne DelimiterCharIsNotZero ; Not EOS?
    ; End of delimiters, char not found
    mov eax, 0          ; Not found (false)
    jmp DelimiterScanEnd    ; To end

DelimiterCharIsNotZero:
    cmp al, dl          ; Input char (al) == current delimiter (dl)?
    jne InputCharIsNotThisDelimiter ; Not this one?
    ; Match found
    mov eax, 1          ; Found (true)
    jmp DelimiterScanEnd    ; To end

InputCharIsNotThisDelimiter:
    inc edi             ; Next delimiter char
    jmp DelimiterScanLoop   ; Loop

DelimiterScanEnd:
    pop edi             ; Restore edi
    mov esp, ebp        ; Restore esp
    pop ebp             ; Restore ebp
    ret                 ; Return (result in eax)


get_words:
    enter 0, 0          ; Setup frame
    pushad              ; Save all GP registers

    ; Load parameters
    mov esi, [ebp + 8]  ; esi = input_str
    mov ebx, [ebp + 12] ; ebx = words_array
    mov edx, [ebp + 16] ; edx = max_words

    xor ecx, ecx        ; ecx = word_count = 0

MainWordExtractionLoop:
    ; Check word count against max
    cmp ecx, edx        ; word_count >= max_words?
    jge WordsFinished   ; Yes, finish

SkipDelimitersLoop:
    mov al, [esi]       ; al = current char from input_str
    cmp al, 0           ; End of input_str?
    jne CharNotZeroInSkipLoop ; Not EOS?
    ; EOS found while skipping
    jmp WordsFinishedEarly   ; To early finish

CharNotZeroInSkipLoop:
    call is_delimiter_internal ; Is char in al a delimiter? (eax=0/1)
    cmp eax, 1          ; Is delimiter?
    jne FoundStartOfWord ; No, found word start
    ; Yes, is a delimiter
    inc esi             ; Next char in input_str
    jmp SkipDelimitersLoop ; Loop skip

FoundStartOfWord:
    ; esi points to word start. Store it.
    push esi            ; Save word_start_ptr
    mov eax, ecx        ; eax = word_count
    shl eax, 2          ; eax = offset (word_count * 4)
    add eax, ebx        ; eax = &words_array[word_count]
    pop dword [eax]     ; words_array[word_count] = word_start_ptr

    mov edi, esi        ; edi (scan_ptr) = word_start

ScanForWordEndLoop:
    mov al, [edi]       ; al = char from scan_ptr
    cmp al, 0           ; End of string?
    jne CharNotZeroInScanLoop ; Not EOS?
    ; EOS found while scanning word
    jmp EOSFoundDuringWordScan

CharNotZeroInScanLoop:
    call is_delimiter_internal ; Is char in al a delimiter? (eax=0/1)
    cmp eax, 1          ; Is delimiter?
    jne CharIsNotDelimiterInScan ; Not delimiter?
    ; Delimiter found, marks end of word
    jmp DelimiterFoundToEndCurrentWord

CharIsNotDelimiterInScan:
    inc edi             ; Next char (scan_ptr)
    jmp ScanForWordEndLoop ; Loop scan

DelimiterFoundToEndCurrentWord:
    mov byte [edi], 0   ; Null-terminate word
    mov esi, edi        ; input_str_ptr to current pos
    inc esi             ; Advance input_str_ptr past new null
    inc ecx             ; word_count++
    jmp MainWordExtractionLoop ; Next word

EOSFoundDuringWordScan:
    ; EOS is end of word. Already null-terminated.
    mov esi, edi        ; input_str_ptr to EOS
    inc ecx             ; word_count++
    jmp MainWordExtractionLoop ; Next word (likely to finish)

WordsFinishedEarly:     ; Label for early finish

WordsFinished:          ; Label for normal finish
    popad               ; Restore all GP registers
    leave               ; Restore frame
    ret                 ; Return
