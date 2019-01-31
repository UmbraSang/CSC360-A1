
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#include "DoublyLinkedList.c"

pid_t parentID;
pid_t pid;

char* intakeLine() {
	char* line = NULL;
	size_t buffsize = 0;
	getline(&line, &buffsize, stdin);
	// if(*line == "^D"){
	// 	exit(0);
	// }
	return line;
}

struct List* getTokens(char* input) {
	char* token = strtok(input, " \t\r\n\a");
	struct List* tokarr = makeList();
	while (token!=NULL){
		addLast(makeNode(token), tokarr);
		token = strtok(NULL, " \t\r\n\a");
	}
	return tokarr;
}

char* builtInList[] = {
    "setenv",
    "unsetenv",
    "exit",
	"cd"
};

int numBuiltIn(){
    return sizeof(builtInList)/sizeof(char *);
}

int setEnv(char **args){
	if(args[1]==NULL || args[2]==NULL){
		printf("Too few arguments.\n");
	} else{
		setenv(args[1], args[2], 1);
		printf("Envrioment Variable set.\n");
	}
	return 1;
}

int unsetEnv(char **args){
	if(args[1]==NULL){
		printf("Too few arguments.\n");
	} else {
		unsetenv(args[1]);
		printf("Envrioment Variable removed.\n");
	}
	return 1;
}

int exitShell(char **args){
	printf("Killing shell.\n");
	return 0;
}

int cngDir(char **args){
	if (args[1]==NULL){
		chdir(getenv("HOME"));
		printf("Welcome to HOME directory.\n");
	}else{
		chdir(args[1]);
		printf("Welcome to %s directory.\n", args[1]);
	}
	return 1;
}

void INThandler(int sig){
	//char yn;

	signal(sig, SIG_IGN);
	if(getpid()==parentID){
		kill(pid, SIGKILL);
		// printf("\nReady to quit? [y/n]");
		// yn = getchar();
		// if(yn == 'y' || yn == 'Y'){
		// 	exit(0);
		// } else {
		// 	signal(SIGINT, INThandler);
		// }
	}
}

int launch(char** args){
	int status;
	parentID = getpid();

	pid = fork();
	signal(SIGINT, INThandler);
	if(pid==0){
		//child part
		if(execvp(args[0], args)==-1){
			perror("failed exec() call\n");
		}
		exit(EXIT_FAILURE);
	} else if (pid < 0){
		//error part
		perror("bad fork\n");
	} else{
		//parent part
		do {
      		waitpid(pid, &status, WUNTRACED);
    	} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return 1;
}

int builtInFuncSwitch(char** args, int x){
	int i;
	switch(x){
		case 0:
			i = setEnv(args);
			break;
		case 1:
			i = unsetEnv(args);
			break;
		case 2:
			i = exitShell(args);
			break;
		case 3:
			i = cngDir(args);
			break;
	}
	return i;
}


int kapexec(char** args) {
	int i;
	if(args[0] == NULL){
		return 1;
	}
	for(i=0; i<numBuiltIn(); i++){
		if(strcmp(args[0], builtInList[i])==0){
			return builtInFuncSwitch(args, i);
		}
	}
	return launch(args);
}

char** listToArray(struct List* list){
	char** arr = malloc(list->length * sizeof(char*));
	int i = 0;
	while(list->head){
		arr[i] = pop(list);
		i++;
	}
	return arr;
}

void testPrint(struct List* args){
	printList(args);
	printListRev(args);
}

void argsReader() {
	char* input;
	struct List* args;
	int status;

	do{
		printf("? ");
		input = intakeLine();
		args = getTokens(input);
		//testPrint(args);
		status = kapexec(listToArray(args));

		free(input);
		free(args);
	} while (status);
}

int main(int argc, char **argv) {
	// Load config files, if any.

	// Run command loop.
	argsReader();
	// Perform any shutdown/cleanup.

	return EXIT_SUCCESS;
}