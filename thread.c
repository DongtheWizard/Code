#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <sys/times.h>
#include <sys/resource.h>
#include <unistd.h>
void * f1();
void * f2();
void * f3();
int val[9];//9th is the result
int flag=0;
pthread_t thread1, thread2, thread3;
int main (){
  int i;
  struct tms t;
  struct rusage r;
  for(i=0; i<8; i++){
    printf("Input a value: ");
    scanf("%d", &val[i]);
    scanf("%c");
  }
  val[2]=val[2]*val[3];
  pthread_create(&thread1, NULL, f1, NULL); 
  pthread_create(&thread2, NULL, f2, NULL); 
  pthread_create(&thread3, NULL, f3, NULL);
  pthread_join(thread1, NULL);
  val[2]=val[2]/val[4];
  pthread_join(thread2, NULL);
  val[8]=val[0]-val[2];
  pthread_join(thread3, NULL);
  val[8]=val[8]+val[6];
  time(&t);
  getrusage(RUSAGE_SELF, &r);
  printf("The result is %d\n time: %d\n usage: %d", val[8], t, r);
  


  exit(EXIT_SUCCESS);
}
// (a+b)–[(c*d) / (e-f)] + (g+h)
void * f1(){
    val[4]=val[4]-val[5];

  }
void * f2(){
    val[0]=val[0]+val[1];

  }
void * f3(){
    val[6]=val[6]+val[7];

  }
