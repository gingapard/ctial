#include<stdio.h>
#include<termios.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include<sys/stat.h>
#include<crypt.h>
#include"actions.h"
#include"utils.h"
#include"error.h"

#define MAX_LENGTH 64

char* get_home() {
    char* tmp = getenv("HOME");
    char* homeDIR = (char*)malloc(sizeof(tmp));
    strcpy(homeDIR, tmp);
    if (homeDIR == NULL) {
        fprintf(stderr, "HOME environment variable not set.\n");
        exit(1);
    }

    return homeDIR;
}

char* get_password() {
    struct termios t, backup;
    tcgetattr(STDIN_FILENO, &t);
    backup = t;
    cfmakeraw(&t);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);

    char ch = 0;
    int position = 0;
    char password[MAX_LENGTH + 1] = {0};

    while (position < MAX_LENGTH) {
        ch = getchar();
        if (ch < 0x20)
          break;

        password[position++] = ch;
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &backup);
    char* result = (char*)malloc(strlen(password));
    strcpy(result, password);
    if (strlen(password) == 0) result[0] = '\0';

    return result;
}

int dir_exists(const char* path) {
    struct stat info;
    if (stat(path, &info) != 0) return 0;
    return 1;
}

void verify_file_struct() {
    char fullPath[PATH_MAX];
    const char* homeDIR = getenv("HOME");
    // formating path
    snprintf(fullPath, sizeof(fullPath), "%s/%s", homeDIR, ".ctial");
    
    // creating .ctial dir
    puts("Verifying file structure...");
    // checkign if .ctial exists
    if (!dir_exists(fullPath)) {
        puts("Creating dir: .ctial");
        if (mkdir(fullPath, 0777) == 0) printf("Done.\n", fullPath);
        else puts("Error Creating Dir");
    } 
    
    snprintf(fullPath, sizeof(fullPath), "%s/%s/%s", homeDIR, ".ctial", "master");
    // checking if master exists
    if (dir_exists(fullPath)) {
        printf("You already have a master password.\n");
        printf("Proceeding will make all previously saved secrets unaccessable!\n");
        printf("To change master password, use '-passwd' ");

        char buffer[16];
        printf("\nProceed: Y/n: ");
        fflush(stdout);
        fgets(buffer, sizeof(buffer), stdin);

        if (strcmp("Y", buffer) == 0 && strcmp("y", buffer) == 0 && strcmp("\n", buffer) == 0) {
            puts("Abort.");
            exit(1);
        }
        // creating master file
        FILE* fp = fopen(fullPath, "w");
        fclose(fp);
    }
    puts("Done.");
}

void setup() {
    const char* homeDIR = get_home();;
    verify_file_struct();
    int passeq = 0;
    char fullPath[PATH_MAX];
    snprintf(fullPath, sizeof(fullPath), "%s/%s/%s", homeDIR, ".ctial", "master");

    char hash_pass1[MAX_LENGTH + 1];
    char hash_pass2[MAX_LENGTH + 1];

    // getting password
    do {
        printf("Master: ");
        char* pass_str = get_password();
        // checking if input is empty
        if (strlen(pass_str) == 0) {
            pr_err_pass(Empty);
            continue;
        }

        // hasing password
        strcpy(hash_pass1, crypt(pass_str, "master"));
        printf("\n");

        printf("Retype Master: ");
        char* pass_str_2 = get_password();
        // checking if input is empty
        if (strlen(pass_str_2) == 0) {
            pr_err_pass(Empty);
            continue;
        }

        // hasing password
        strcpy(hash_pass2, crypt(pass_str_2, "master"));
        printf("\n");
        
        if (strcmp(hash_pass1, hash_pass2) == 0) {
            FILE* fp = fopen(fullPath, "w");
            fwrite(hash_pass1, 1, strlen(hash_pass1), fp);
            fclose(fp);
            puts("Success.");
            passeq = 1;
        }
        else {
            puts("Sorry, did not match.");
        }


    } while (passeq == 0);
}
