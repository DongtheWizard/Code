#include <stdio.h>
#include <stdlib.h>

int mymalloc(int);
void mywrite(int, int);
int myread(int);
void myfree(int, int);
void myInit(int[]);
void tblinit();
int getphys();

#define SIZE 65536
#define PGSZ 1024
#define ALOMEM 4096

//char mem[SIZE];
int holes[SIZE];
char physmem[SIZE];
int used[SIZE/PGSZ];
int pgtbl[SIZE/PGSZ];



int main(){

  myInit(); // init physical memory
  //myContInit(used);
  //tblinit();
  
  int ptr=mymalloc(ALOMEM);
  int firstpage=ptr/PGSZ;
  int lastpage=((ptr+ALOMEM)/PGSZ);
  
  int index;
  int i;
  for(i=firstpage; i<lastpage; i++){
    if(pgtbl[i]==-1){
      index=getphys(i);
      pgtbl[i]=index;
    }     
  }
  
  /*mywrite(ptr+2, 6);
    int b=myread(ptr+2);*/
  printf("%d\n", (pgtbl[ptr/PGSZ]*PGSZ+(ptr%PGSZ)));  
  myfree(ptr, ALOMEM);
}

void myInit() {
  myContInit(used);
  tblinit();
  
}


int getphys(int a){
  int i=a*PGSZ;
  for(; i<SIZE && used[i]==0; i++){
    if(i/ ){
      int j;


      }
      

    }
  }
    

}
void tblinit(){
  int i;
  for(i=0; i<(SIZE/PGSZ); i++)
    pgtbl[i]=-1;

}

void myContInit(int a[SIZE]) {
  int i;
  for (i = 0; i < SIZE; i++)
    a[i] = 0;
}

int myContmalloc(int a){
  int i;

  for (i = 0; i < SIZE; i++)
    if (holes[i] == 0) {
      int j = 0;
      for (; j < a && holes[i+j] == 0; j++);
      if (j == a) {
	for (j = 0; j < a; j++)
	  holes[i+j] = 1;

	return i;
      }

    }
 
  return -1;
}


int mymalloc(int sz) {
  int ptr = myContmalloc(sz);
  int i;


  int firstpage = ptr/PGSZ;
  int lastpage = (ptr+sz)/PGSZ;

  for (i = firstpage; i < lastpage; i++)
    if (pgtbl[i] == -1) {
      
    }


  return ptr;
}


/*
void mywrite(int ptr, int val){
  mem[ptr]=val;
}
int myread(int ptr){

      return mem[ptr];

}
*/



void myContfree(int ptr, int a){
  int i=ptr; 

  for (; i < ptr+a; i++)
    holes[i] = 0;

  
}

