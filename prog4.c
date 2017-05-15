#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#define KEY 4567
#define PERMS 0660
int main(int argc, char **argv) {
int id;
 int a[4];
int *ptr;
 int i;
 for(i=0; i<4; i++){
   printf("Enter a value: ");
   a[i]=getchar();
   getchar();
 }
//system("ipcs -m");
id = shmget(KEY, sizeof(int), IPC_CREAT | PERMS);
//system("ipcs -m");
ptr = (int *) shmat(id, NULL, 0);
*ptr = 0;

if (fork() == 0) {
  *ptr=(a[2]+a[3]);
  exit(0);
} 
else {
wait(NULL);
 *ptr=(a[0]+a[1])-*ptr;
printf("Value of *ptr = %d\n", *ptr);
shmctl(id, IPC_RMID, NULL);
}
}
