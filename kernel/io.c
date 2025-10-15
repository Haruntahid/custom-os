#include "io.h"

#define VIDEO_MEMORY (char*)0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

int cursor = 0;

void print(const char* str) {
    volatile char* video = VIDEO_MEMORY;
    while (*str) {
        if (*str == '\n') {
            cursor += (80 - (cursor % 80));
        } else {
            video[cursor * 2] = *str;
            video[cursor * 2 + 1] = 0x07;
            cursor++;
        }
        str++;
    }
}

void clear_screen() {
    volatile char* video = VIDEO_MEMORY;
    for (int i = 0; i < MAX_ROWS * MAX_COLS; i++) {
        video[i * 2] = ' ';
        video[i * 2 + 1] = 0x07;
    }
    cursor = 0;
}

void read_input(char* buf) {
    int i = 0;
    char c;
    while (1) {
        c = get_char();  // placeholder for keyboard input
        if (c == '\n' || c == '\r') {
            buf[i] = 0;
            print("\n");
            return;
        } else if (c == 0x08 && i > 0) {  // backspace
            i--;
            print("\b \b");
        } else {
            buf[i++] = c;
            char temp[2] = {c, 0};
            print(temp);
        }
    }
}

void keyboard_callback(uint32_t scancode) {
    char c = (char)(scancode + 0x20); // crude example, real mapping is better
    print_char(c);
}

char get_char(void) {
    // Temporary stub until you implement real keyboard input
    return 'a';  // Always returns 'a' for now
}
