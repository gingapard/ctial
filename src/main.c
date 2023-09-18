#include<stdio.h>
#include<string.h>

void pr_usage() {
	printf("usage: todo\n");
}

enum Error {
	ActionConflict,
	ActionMissing,
	TargetConflict,
	TargetMissingEx,
	TargetMissing,
	ArgConflict,
	ArgMissingEx,
	ArgMissing,
};

void pr_err(enum Error err, int pos) {
	switch (err) {
		case ActionConflict:
			printf("Conflicting Action: index %d\n", pos);
			break;
		case TargetConflict: 
			printf("Conflicting Target: index %d\n", pos);
			break;
		case TargetMissingEx:
			printf("Expected argument after '-t'\n");
			break;
	}
}

typedef struct {
	int action;
	char target[64];
	char arg[64];
} Input;

int main(int argc, char** argv) {
	if (argc < 2) {
		pr_usage();
		return 1;
	}

	Input input;
	int act_set = 0;
	int tar_set = 0;
	int arg_set = 0;

	// parsing input
	for (int i = 1; i < argc; ++i) {
		// get action
		// insert
		if (strcmp(argv[i], "-i") == 0) {
			if (act_set != 0) {
				pr_err(ActionConflict, i);
				printf("Abort.\n");
				return 1;
			}
			input.action = 0;
			++act_set;
		}
		// delete
		else if (strcmp(argv[i], "-d") == 0) {
			if (act_set != 0) {
				pr_err(ActionConflict, i);
				printf("Abort.\n");
				return 1;
			}
			input.action = 1;
			++act_set;
		}
		// modify
		else if (strcmp(argv[i], "-m") == 0) {
			if (act_set != 0) {
				pr_err(ActionConflict, i);
				printf("Abort.\n");
				return 1;
			}
			input.action = 2;
			++act_set;
		}

		// get target
		else if (strcmp(argv[i], "-t") == 0) {
			if (tar_set != 0) {
				pr_err(TargetConflict, i);
				printf("Abort.\n");
				return 1;
			}

			++tar_set;
			
			if (i == argc - 1) {
				pr_err(TargetMissingEx, i);
				printf("Abort.\n");
				return 1;
			}

			if (argv[i + 1][0] == '-') {
				pr_err(TargetMissingEx, i);
				printf("Abort,\n");
				return 1;
			}
		
			strcpy(input.target, argv[i + 1]);
		}
		else if (strcmp(argv[i], "-arg") == 0) {
			if (arg_set != 0) {
				pr_err(ArgConflict, i);
				printf("Abort.\n");
				return 1;
			}

			++arg_set;

			if (i == argc - 1) {
				pr_err(ArgMissingEx, i);
				printf("Abort.\n");
				return 1;
			}

			if (argv[i + 1][0] == '-') {
				pr_err(ArgMissingEx, i);
				printf("Abort,\n");
				return 1;
			}

			strcpy(input.arg, argv[i + 1]);
		}
	}

	printf("Action: %d, target: %s, argument: %s\n", input.action, input.target, input.arg);

	return 0;
}
