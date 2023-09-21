#include<stdio.h>
#include<stdlib.h>
#include"error.h"

void pr_usage() {
	printf("usage: todo\n");
}

void pr_help() {
	printf("todo\n");
}

void pr_err_arg(enum ErrorArg err, int pos) {
	switch (err) {
		case ActionConflict:
			printf("Conflicting Action[%d]\n", pos);
			break;
		case ActionMissing:
			printf("Need action specified. Try '-h' for help.\n");
			break;
		case TargetConflict: 
			printf("Conflicting Target[%d]\n", pos);
			break;
		case TargetMissing:
			printf("Target needed to proceed with action\n");
			break;
		case TargetMissingEx:
			printf("Expected argument after '-t'\n");
			break;
		case ArgConflict:
			printf("Conflicting '-arg'[%d]\n", pos);
			break;
		case ArgMissingEx:
			printf("-md needed to proceed with action\n");
			break;
		case ArgMissing:
			printf("Expected token after '-md'\n");
	}
}

void check_conflict(enum ErrorArg err, int set, int pos) {
	if (set != 0) {
		pr_err_arg(err, pos);
		exit(1);
	}
}
