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
 int id2 = shmget(3246, sizeof(sem_t), IPC_CREAT | 0600);
  sem_t *sem2 = shmat(id2, 0, 0);
  int id3 = shmget(3247, sizeof(sem_t), IPC_CREAT | 0600);
  sem_t *sem3 = shmat(id3, 0, 0);

  sem_init(sem, 1, 1);
  sem_init(sem2, 1, 1);
  sem_init(sem3, 1, 1);
  
  if (fork() == 0) {
    sem_wait(sem2);
    sleep(1);
    sem_wait(sem3);
    sem_post(sem2);
    sem_post(sem3);
    printf("p2 is done\n");
    exit(0);
  }

  if (fork() == 0) {
    sem_wait(sem3);
    sleep(1);
    sem_wait(sem);
    sem_post(sem3);
    sem_post(sem);
    printf("p3 is done\n");
    exit(0);
  }

  sem_wait(sem);
  sleep(1);
  sem_wait(sem2);
  sem_post(sem);
  sem_post(sem2);
  printf("p1 is done\n");
  exit(0);

}
