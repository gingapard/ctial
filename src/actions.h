#ifndef ACTIONS_H
#define ACTIONS_H


enum Action {
	Insert,
	Delete,
	Modify,
	List,
};

typedef struct {
	enum Action action;
	char target[64];
	char arg[64];
} Input;

void insert(Input input);


#endif
