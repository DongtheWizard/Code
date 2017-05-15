#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main(){
  int i=5;
  if(fork()==0){
    
    i++;
    printf("ppid = %ld\n", getpid());
    execlp("chrome", "hello", NULL);
    printf("%d\n", i);

  }
  else{

    sleep(3);
    
    wait(NULL);
    }

}
