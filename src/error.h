#ifndef ERROR_H 
#define ERROR_H

#include<stdio.h>

enum ErrorArg {
	ActionConflict,
	ActionMissing,
	TargetConflict,
	TargetMissingEx,
	TargetMissing,
	ArgConflict,
	ArgMissingEx,
	ArgMissing,
};

void pr_usage();
void pr_help();
void pr_err_arg(enum ErrorArg err, int pos);
void check_conflict(enum ErrorArg err, int set, int pos);

#endif
