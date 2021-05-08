
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX_LINE 80


void execute(const char *str){
    int pid = fork();
    if(pid == 0){
      system(str);
      exit(1);
    }
    else
      wait(NULL);
}

int main(void){

	char history[MAX_LINE];
	int should_run = 1;
  char args[MAX_LINE];
  int i=0,histc=0;
	while(should_run){
		printf("osh>");
    fflush(stdout);
		fgets(&args[i],MAX_LINE,stdin);

		if(strcmp(&args[i],"exit\n") == 0){
		    break;
		}
    else if(strcmp(&args[i],"!!\n") == 0){
      if(histc==0){
        printf("No History\n");
        continue;
      }
      else{
        strncpy(&args[i],&history[0],strlen(history));
        goto exe;
      }
		}
    else{

		    strncpy(&history[0], &args[i],strlen(args));
        histc=1;
        goto exe;
    }
    i++;
    exe:
    execute(&args[i]);
	}
	return 0;
}
