#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>  
int main(){

  int id=shmget(3245, sizeof(sem_t), IPC_CREAT | 0660);
  sem_t * sem=shmat(id, 0, 0);
  sem_init(sem, 1, 1);
  int id2=shmget(3246, sizeof(sem_t), IPC_CREAT | 0660);
  sem_t * sem2=shmat(id2, 0, 0);
  sem_init(sem2, 1, 1);
  
if(fork()==0)
  {
       sem_wait(sem);
       execlp("emacs", "p2", NULL);
       sem_post(sem2);
  }
  if(fork()==0)
  {
   
       sem_wait(sem2);
       execlp("vi", "p3", NULL);
       sem_post(sem2);
  }
  execlp("firefox", "p1", NULL);
  sem_post(sem);
 
 
}
 
 
