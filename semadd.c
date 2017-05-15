//part 3
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>          
#include <sys/stat.h>  
#include <semaphore.h>
#include <unistd.h>
void *p2();
void *p3();
void *p4();
int res[6];
sem_t sem, sem2;
int main(){
  pthread_t thread, thread2, thread3;
  sem_init(&sem, 1, 0);
  sem_init(&sem2, 1, 0);

  int i, result;
  for(i=0; i<6; i++){
    printf("Enter a value ");
    scanf("%d", &res[i]);
    scanf("%c");
  }
  pthread_create(&thread, NULL, p2, NULL);
  pthread_create(&thread2, NULL, p3, NULL);
  pthread_create(&thread3, NULL, p4, NULL);
  pthread_join(thread, NULL);
  pthread_join(thread2, NULL);
  pthread_join(thread3, NULL);
  sem_wait(&sem);
  sem_wait(&sem);	
  result=res[0]*res[2];
  sem_wait(&sem2);
  result*=res[4];
  printf("The result is %d\n", result);
}
void * p2()
{
  res[0]=res[0]+res[1];
  sem_post(&sem);
}
void * p3()
{
 res[2]=res[2]-res[3];
 sem_post(&sem);

}
void * p4()
{
  res[4]=res[4]+res[5];
  sem_post(&sem2);

}
/*Use sempahores to implement the following parallelized calculation (a+b)*(c-d)*(e+f)
T1 runs (a+b) and stores the result in a shared table (1st available spot)
T2 runs (c+d) and stores the result in a shared table (1st available spot)
T3 runs (e+f) and stores the result in a shared table (1st available spot)
T4 awaits for two tasks to end and does the corresponding calculation
T4 awaits for the remaining task to end and does the final calculation then displays the result*/
