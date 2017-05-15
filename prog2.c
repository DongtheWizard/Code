#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
void mysystem(char[100]);
void display();
int main(int argc, char **argv) {
int s;
 display();
 scanf("%d", &s);
 switch(s){
 case 1:
    mysystem("cat ./f1");
   break;
 case 2:
   mysystem("chmod 700 ./f1");
   break;
 case 3:
   mysystem("chown 752 f1");
   break;
 case 4:
   mysystem("mkdir new");
   mysystem("rm -R new");
   break;
 case 5:
   mysystem("ln -s ./shell newshell");
   break;
 case 6:
   mysystem("ls -l f1");
   break;
case 7:
  mysystem("cd folder3");
   break;
case 8:
  mysystem("mv f1 f2");
   break;
case 9:
  mysystem("cp f1 folder3/f1");
  mysystem("rm f1");
   break;
case 10:
  mysystem("rm f1");
   break;
case 11:
  mysystem("ps");
   break;
case 12:
  char t [100];
  printf("INPUT A PID TO KILL ");
  scanf("%*c");
  gets(t);
  mysystem(t);
   break;
 default:
   printf("PLEASE INPUT 1-12\n");
 }
}
void mysystem(char a[100]){
  if(fork()==0){
    execlp("sh", "shell", "-c" , a, NULL);
  }
    wait(NULL);
}
void display(){
  printf("1. Read a file\n2.Change file permissions\n3.Change file owner\n4.Create and remove a directory\n5.Create a symlink\n6.Display file information\n7.Change directory (Does it really change folders ? Why ?)\n8.Rename a file\n9.Move a file\n10.Remove a file\n11.Show process status\n12.Send a signal to a process\n");
}

