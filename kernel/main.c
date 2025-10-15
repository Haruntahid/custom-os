#include "io.h"
#include "shell.h"
#include "interrupts.h"

void kernel_main() {
    clear_screen();
    print("Welcome to CustomOS!\n");
    print("Type 'help' to see available commands.\n\n");

    init_pic();
    init_idt();
    asm volatile("sti"); // Enable interrupts

    while (1); // keep kernel running
}
