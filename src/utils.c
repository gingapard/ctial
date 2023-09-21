#include<stdio.h>
#include<termios.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include<sys/stat.h>
#include"utils.h"

#define MAX_LENGTH 64

char* get_password() {
    struct termios t, backup;
    tcgetattr(STDIN_FILENO, &t);
    backup=t;
    cfmakeraw(&t);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);

    char c = 0;
    int position = 0;
    char password[MAX_LENGTH + 1] = {0};

    while (position < MAX_LENGTH) {
        c = getchar();
        if (c < 0x20)
          break;

        password[position++] = c;
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &backup);
    char* result = (char*)malloc(strlen(password));
    strcpy(result, password);
    return result;
}

int dir_exists(const char *path) {
    struct stat info;
    if (stat(path, &info) != 0) return 0;
    return 1;
}

void verify_file_struct() {
    const char* homeDIR = getenv("HOME");
    if (homeDIR == NULL) {
        fprintf(stderr, "HOME environment variable not set.\n");
        EXIT_FAILURE;
    }

    char fullPath[PATH_MAX];
    snprintf(fullPath, sizeof(fullPath), "%s/%s", homeDIR, ".ctial");
    
    // creating .ctial dir
    printf("Creating file structure.\n");
    if (!dir_exists(fullPath)) {
        if (mkdir(fullPath, 0777) == 0) {
            printf("Created %s\n", fullPath);
        }
        else {
            printf("Error Creating Dir\n");
        }
    } 
}

void setup() {
    verify_file_struct();
}
