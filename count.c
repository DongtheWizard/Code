#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void * inc1();
void * inc2();
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  cond = PTHREAD_COND_INITIALIZER;
int count=0;
int main(){
  pthread_t thread, thread2;
  
  pthread_create(&thread, NULL, inc1, NULL);
  pthread_create(&thread2, NULL, inc2, NULL);
  pthread_join(thread, NULL);
  pthread_join(thread2, NULL);
 
  printf("%d\n", count);
}
void * inc1(){
  while(1){
    pthread_mutex_lock(&mut);
    pthread_cond_wait(&cond, &mut);
    printf("here\n");
    ++count;
    pthread_mutex_unlock(&mut);
    if(count>=10)
      return;
  }
}
void * inc2(){
  while(1){
    pthread_mutex_lock(&mut);
    if(count<3 || count>7)
      pthread_cond_signal(&cond);
    else{
      printf("there\n");
      ++count;
    }
    pthread_mutex_unlock(&mut);
    if(count>=10)
      return;
  }
}
