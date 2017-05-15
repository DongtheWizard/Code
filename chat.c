#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc, char *argv[]) {
  pid_t cpid;
  int n;
  cpid = fork();
  if (cpid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
    
  if (cpid == 0) {    /* Child writes to pipe */
    char buf[255];

    int wr=open(argv[2], O_WRONLY);
    while ((n = read(STDIN_FILENO, buf, 255)) != 0)
      write(wr, buf, n);
    
    exit(0);
      
  
  } else {            /* Parent reads from pipe */

      char buf[255];
      int rd=open(argv[1], O_RDONLY); 
      while((n = read(rd, buf, 255)) != 0)
	write(1, buf, n);

      exit(0);
      //close(fd);
    }
}
