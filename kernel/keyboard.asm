; kernel/keyboard.asm
[bits 32]
global keyboard_handler
extern keyboard_callback

keyboard_handler:
    pusha

    in al, 0x60          ; Read scan code from keyboard controller
    push eax
    call keyboard_callback ; Call C function to handle it
    pop eax

    mov al, 0x20
    out 0x20, al         ; Send End of Interrupt to PIC

    popa
    iret
