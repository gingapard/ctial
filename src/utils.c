#include<stdio.h>
#include<stdlib.h>
#include"utils.h"

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
		case TargetConflict: 
			printf("Conflicting Target[%d]\n", pos);
			break;
		case TargetMissingEx:
			printf("Expected argument after '-t'\n");
			break;
	}
}

void check_conflict(enum ErrorArg err, int set, int pos) {
	if (set != 0) {
		pr_err_arg(err, pos);
		exit(1);
	}
}
