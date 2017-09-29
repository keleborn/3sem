/*
  Write a program which allow you to: 
- run another programs via command line.
- get exit codes of terminated programs

## TIPS:
1. Use "2_fork_wait_exit.c" and "4_exec_dir.c" from examples. Combine them.
2. Parse input string according to the type of exec* (see "man exec").
   a) if execvp is used, string splitting into "path" and "args" is all you need.
3. Collect exit codes via waitpid/WEXITSTATUS.
*/


#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define ArgNumb 4096

int main(){
	char S[256] = "";
	do{
		printf("To exit the programme enter 'quit'\n");
		char *arg[ArgNumb];
		char s[256];
		fgets(S, 255, stdin);	
		int counter = 0;
		int i = 0;
		do{
			sscanf(S, "%s", s);
			arg[counter] = s;
			counter++;
			i += strlen(s);
		} while(i <= strlen(S));
		int status;
		pid_t pid = fork();
		switch(pid){
			default:
				waitpid(pid, &status, 0);
				printf("Ret code: %d\n", WEXITSTATUS(status));
				break;
			case -1:
				printf("Error (fork)\n");
				exit(-1);
				break;
			case 0:
				execvp(arg[0], arg+1);
				printf("Error (exec)\n");
				break;
		}	
	}while(strcmp(S, "quit\n"));
	return 0;
}
