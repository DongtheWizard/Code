#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char* argv[]){
  int fd1=open(argv[1], O_CREAT | O_RDONLY);
  int fd2=open(argv[2], O_CREAT | O_WRONLY);
  char ch;

  dup2(fd1, 0);
  dup2(fd2, 1);
  while(read(0, &ch, 1)!=0)
    {
      write(1, &ch, 1);
     
    }

}
