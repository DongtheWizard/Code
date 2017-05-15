#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
int main(){
  
 int key=3151;
  int key2=2135;
  int id=shmget(key, sizeof(char), IPC_CREAT | 0600);
  int id2=shmget(key2, 5*sizeof(int), IPC_CREAT | 0600);
  int* flag=shmat(id, NULL, 0);
  int* pt=shmat(id2, NULL, 0);
  *flag=1; 
   pt[1]=4+3;
   
  


}
