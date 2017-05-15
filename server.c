/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
void error(const char *msg)
{
  perror(msg);
  exit(1);
}
int main(int argc, char *argv[])
{
  int sockfd, newsockfd, portno;
  socklen_t clilen;
  char buffer[256];
  struct sockaddr_in serv_addr, cli_addr;
  int n;
  if (argc < 2) {
    fprintf(stderr,"ERROR, no port provided\n");
    exit(1);
  }
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    error("ERROR opening socket");
  bzero((char *) &serv_addr, sizeof(serv_addr));
  portno = atoi(argv[1]);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);
  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    error("ERROR on binding");
  int i;

  listen(sockfd,5);
  clilen = sizeof(cli_addr);
  

  while(1){
    
      newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
      if (newsockfd < 0)
	error("ERROR on accept");
  
    // bzero(buffer,256);
      char me[255];
      char them[255];
      if(fork()==0){
	while (1) {

	  char c;
	  if (read(newsockfd, them, sizeof(char)) > 0)
	    write(1, them, sizeof(char));
	    
	}
      }
      // if(fork()==0){
	while (1) {
	  gets(me);
	  me[strlen(me)]='\n';
	  write(newsockfd, me, sizeof(char)*(strlen(me) +1));
	  //strcpy(me, "");
	}
	
	/*
	  int a, b, res=0; 
	char c;
	char out='n';
	while(out != 'y') {
	  read(newsockfd,&a,sizeof(int));
	  if (a == -1) 
	    out = 'y';
	  else {
	    
	    read(newsockfd, &b, sizeof(int));
	    read(newsockfd, &c, sizeof(char));
	    
	    if(c=='+')
	      res=a+b;
	    else if(c=='-')
	      res=a-b;
	    else if(c== '*')
	      res=a*b;
	    else if(c== '/')
	      res=a/b;
      
    
	    write(newsockfd, &res, sizeof(int));
	
	  }

	*/

	//}
	
	close(newsockfd);	  

      }
  
    
    /* 
       if (n < 0) error("ERROR reading from socket");
       int a=atoi(buffer);
       int b=atoi(buffer[);
       int result=0;
       switch (buffer[1]){
       case '-':
       result=a-b;
       break;
       case '+':
       result=a+b;
       break;
       case '*':
       result=a*b;
       break;
       case '/':
       result=a/b;
       break;

       }
       printf("Here is the message: %d\n", result);
       n = write(newsockfd,"I got your message",18);
       if (n < 0) error("ERROR writing to socket");
    */
   

  close(sockfd);

  return 0;
}
