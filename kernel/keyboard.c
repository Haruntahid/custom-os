#include <stdint.h>
#include "io.h"

extern void keyboard_handler(); // From ASM

#define IDT_SIZE 256

struct IDTEntry {
    uint16_t base_low;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_high;
} __attribute__((packed));

struct IDTEntry idt[IDT_SIZE];

void set_idt_gate(int n, uint32_t handler) {
    idt[n].base_low = handler & 0xFFFF;
    idt[n].sel = 0x08; // Kernel code segment
    idt[n].always0 = 0;
    idt[n].flags = 0x8E; // Present, ring 0, 32-bit interrupt gate
    idt[n].base_high = (handler >> 16) & 0xFFFF;
}

extern void load_idt(uint32_t); // Defined in ASM

void init_idt() {
    set_idt_gate(33, (uint32_t)keyboard_handler); // IRQ1 = 33
    load_idt((uint32_t)&idt);
}

void init_pic() {
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20); // Remap master PIC to 0x20
    outb(0xA1, 0x28); // Remap slave PIC to 0x28
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);  // Enable IRQs
    outb(0xA1, 0x0);
}
