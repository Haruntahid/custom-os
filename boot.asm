; boot.asm
BITS 16
ORG 0x7C00

start:
    mov si, msg
    call print

hang:
    jmp hang

print:
    mov ah, 0x0E
.loop:
    lodsb
    cmp al, 0
    je .done
    int 0x10
    jmp .loop
.done:
    ret

msg db "Hello, OS from copy.sh!", 0

; Pad to 512 bytes and add boot signature
times 510 - ($ - $$) db 0
dw 0xAA55
