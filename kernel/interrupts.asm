; keyboard_interrupt.asm
section .text
global keyboard_isr

keyboard_isr:
    pusha                   ; Save all registers

    ; Read scancode from port 0x60
    in al, 0x60

    ; TODO: pass scancode to C handler

    ; Send End of Interrupt (EOI) to PIC
    mov al, 0x20
    out 0x20, al

    popa                    ; Restore registers
    iretd                   ; Return from interrupt
