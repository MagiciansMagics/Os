disk_read16:
    pusha

    mov si, 0x00                            ; just a number to keep track of how many times i have read it

disk_read_retry:
    mov ah, 0x02                            ; BIOS Disk Read
    mov dl, [drive_number]              ; Boot disk number
    int 0x13

    jc read_disk_again                      ; Retry if carry flag is set

    popa
    ret                                     ; Success, return

read_disk_again:
    inc si                                  ; Increment retry counter
    cmp si, 0x10                            ; Maximum retries reached?
    je disk_read_error_max                  ; Jump if retries exceeded

    jmp disk_read_retry                     ; Retry

disk_read_error_max:                        ; final place aka kaput
    mov bx, disk_read_error_text
    call print16
    jmp halt

disk_read_error_text: db "Could not read the disk!", 10, 13, 0