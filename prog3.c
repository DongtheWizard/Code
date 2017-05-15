#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
void display();
int main(){
  char buf;
  char buffer[100];
  int s;
  int fd;
  display();
  scanf("%d", &s);
  switch(s){
  case 1:
  fd=open("./file", O_CREAT|O_RDWR, S_IRWXU|S_IRGRP);
  break;
  case 2:
  while(read(fd, &buf, 1) != 0) 
    printf("%c", buf);
  break;
  case 3:
  chmod("./file", S_IRUSR| S_IWUSR | S_IXUSR| S_IRGRP| S_IXGRP);
  break;
  case 4:
    chown("./file", 31585, 752);
    break;
  case 5:
    mkdir("folder1", O_CREAT|O_RDWR);
    break;
  case 6:
    rmdir("folder1");
    break;
  case 7:
    symlink("file", "filelink");
    break;
  case 8:
    readlink("filelink", buffer, 100);
    strcat(buffer, "\0");
    printf("%s\n", buffer);
    break;
  case 9:
   chdir("folder3");
   break;
  case 10:
   rename("file", "newfile");
   break;
  case 11:
    link("./file", "folder3");
    break;
  case 12:
    remove("file");
    break;
  default:
    printf("Please input a # 1-12\n");

  }

}
void display(){
  printf("1.Create a file\n2.Read a file\n3.Change file permissions\n4.Change file owner\n5.Create a directory\n6.Remove a directory\n7.Create a symlink\n8.Read a symbolic link\n9.Change directory\n10.Rename a file\n11.Move a file\n12.Remove a file\n");
}

