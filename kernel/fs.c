#include "fs.h"
#include "io.h"
#include <string.h>

void list_files(const char* dir) {
    if (strcmp(dir, "/") == 0) {
        print("home\nbin\netc\n");
    } else if (strcmp(dir, "/home") == 0) {
        print("user\n");
    } else {
        print("No files found.\n");
    }
}

void change_dir(const char* path, char* current) {
    if (strcmp(path, "/") == 0 || strcmp(path, "/home") == 0 || strcmp(path, "/home/user") == 0) {
        strcpy(current, path);
    } else {
        print("Directory not found.\n");
    }
}
