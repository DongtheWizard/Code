#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
int pipefd[2];
int p[2];
pid_t cpid;
char buf[255];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    if (pipe(p) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    
    if (cpid == 0) {    /* Child reads from pipe */
      if(fork()==0){
        close(pipefd[0]);
	close(pipefd[1]);
	close(p[1]);           
	dup2(p[0], STDIN_FILENO);
	system("more");
	close(p[0]);
	close(STDIN_FILENO);
      }
      else {
	close(pipefd[1]);
	dup2(pipefd[0], 0);

	close(p[0]);
	dup2(p[1], 1);
	system(" grep p");/**/
	close(p[1]);
	close(pipefd[0]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);

	
	}
      
  
    } else {            /* Parent writes argv[1] to pipe */
        close(pipefd[0]);    /* Close unused read end */
	close(p[0]);
	close(p[1]);
	dup2(pipefd[1], 1);
	system("ps aux");
	close(pipefd[1]);
	close(STDOUT_FILENO);

    }
}
