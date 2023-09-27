#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<crypt.h>
#include"error.h"
#include"utils.h"
#include"actions.h"

void insert(Input input) {
	const char* homeDIR = getenv("HOME");
	int passeq = 0;
	int passeq_master = 0;
	char path[640];
	snprintf(path, sizeof(path), "%s/%s/%s", homeDIR, ".ctial", input.target);
	FILE* fp = fopen(path, "w");	

	char master_path[640];
	snprintf(master_path, sizeof(master_path), "%s/%s/%s", homeDIR, ".ctial", "master");

	do {
		printf("Password to store: ");
		char* pass_str = get_password();	
		printf("\n");
		if (strlen(pass_str) == 0) {
			pr_err_pass(Empty);
			continue;
		}
		
		do {
			printf("Master: ");
			char* master_str = get_password();
			printf("\n");

			FILE* master_fp = fopen(master_path, "r");
			char master_tmp[320];
			fgets(master_tmp, 320, master_fp);

			if (strcmp(crypt(master_str, "master"), master_tmp) == 0) {
				// todo encrypt password with key	
				passeq_master = 1;
				fclose(master_fp);
			}
			else {
				pr_err_pass(Wrong);
				fclose(master_fp);
				continue;
			}
		} while (passeq_master == 0);
		passeq = 1;
	} while (passeq == 0);

	fclose(fp);
}
