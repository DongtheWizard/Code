#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
int main(){
  
 int key=3151;
  int key2=2135;
   int i;
int key3=1513;
  int id3=shmget(key3, sizeof(char), IPC_CREAT | 0600);
  int id2=shmget(key2, 5*sizeof(int), IPC_CREAT | 0600);
   int* flag2=shmat(id3, NULL, 0);
  int * pt=shmat(id2, NULL, 0); 
   pt[3]=1+2;
   while(*flag2 == 1);
    pt[4]= pt[2]/pt[3];
   exit(0);
  


}
