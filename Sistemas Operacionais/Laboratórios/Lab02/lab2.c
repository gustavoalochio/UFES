#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#define MAX 128

// Custom SIGINT (Ctrl+C) signal handler.
void my_handler(int sig_no) {
	printf("Shell: Process %d killed\n", getpid());
	_exit(0);
}

int main(void) {
	signal(SIGINT, my_handler); // Setting a new handler for SIGINT.
	printf("Shell: Process %d started.\n", getpid());
	pid_t pid; // Fork a child process
	char stdinput[MAX];
	char* command[MAX];

	while(1){
		printf(":) >>");
		fgets(stdinput,MAX, stdin);
		stdinput[strlen(stdinput) - 1] = '\0';

		char* token = strtok(stdinput," ");
		memset(command,0,sizeof(command));

		for(int i = 0; token != NULL; i++) {
			command[i] = token;
			token = strtok(NULL," ");
		}

		pid = fork();

		if(pid < 0) {//Error
			fprintf(stderr, "Shell: Fork failed!\n");
			_exit(1);
		} else if(pid == 0){//Child process.
			execvp(command[0], command);
		} else{//Parent Process
			wait(NULL);
		}
	}
	return 0;
}