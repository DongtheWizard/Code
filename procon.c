#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
sem_t sem, sem2;
int * n;
void * con();
void *pro();
int main(){
  n=malloc(25*sizeof(int));
  pthread_t thread, thread2;
  
  sem_init(&sem, 1, 1);
  sem_init(&sem2, 1, 1);
  
  pthread_create(&thread, NULL, pro, NULL);
  pthread_create(&thread2, NULL, con, NULL);

  pthread_join(thread, 0, 0);
  pthread_join(thread2, 0, 0);
  free(n);
}
void * pro(){

}
void * con(){
}
