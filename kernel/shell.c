#include "shell.h"
#include "io.h"
#include "fs.h"
#include "string.h"

char current_dir[256] = "/";

void shell_loop() {
    char input[128];

    while (1) {
        print(current_dir);
        print(" $ ");
        read_input(input);

        if (strcmp(input, "help") == 0) {
            print("Commands: help, ls, pwd, cd, clear\n");
        } else if (strcmp(input, "ls") == 0) {
            list_files(current_dir);
        } else if (strcmp(input, "pwd") == 0) {
            print(current_dir);
            print("\n");
        } else if (strncmp(input, "cd ", 3) == 0) {
            change_dir(input + 3, current_dir);
        } else if (strcmp(input, "clear") == 0) {
            clear_screen();
        } else {
            print("Command not found.\n");
        }
    }
}
