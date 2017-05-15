#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>          
#include <sys/stat.h> 
void * inc();
void *dec();
int i=0;
sem_t sem, sem2;
int main(){
  pthread_t thread, thread2;
  sem_init(&sem, 0, 0);
  //sem_open("first", O_CREAT);
  sem_init(&sem2, 0, 0);
  

  pthread_create(&thread, NULL, inc, NULL);
  pthread_create(&thread2, NULL, dec, NULL);
  
  pthread_join(thread, NULL);
  pthread_join(thread2, NULL);
  
   printf("%d\n", i);
 
}
void* inc(){
  // sem_wait(&sem);
  int temp;
  temp=i;
  sleep(1);
  ++temp;
  i=temp;
  sem_post(&sem);
  
}
void* dec(){
  sem_wait(&sem);
  int temp;
  temp=i;
  sleep(2);
  --temp;
  i=temp;
  //sem_post(&sem);
 
}

