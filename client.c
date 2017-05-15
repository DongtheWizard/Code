#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
void error(const char *msg)
{
  perror(msg);
  exit(0);
}
int main(int argc, char *argv[])
{
  int sockfd, portno, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  char buffer[256];
  if (argc < 3) {
    fprintf(stderr,"usage %s hostname port\n", argv[0]);
    exit(0);
  }
  portno = atoi(argv[2]);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    error("ERROR opening socket");
  server = gethostbyname(argv[1]);
  if (server == NULL) {
    fprintf(stderr,"ERROR, no such host\n");
    exit(0);
  }
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr,
	(char *)&serv_addr.sin_addr.s_addr,
	server->h_length);
  serv_addr.sin_port = htons(portno);
  if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
    error("ERROR connecting");
  // bzero(buffer,256);
  //int a, b, res;
  //char op='\0';
  char me[255];
  char them[255];
 
  
  if (fork() == 0) {

    while(1){
      //if(fork()==0){
      //scanf("%s", me);
      gets(me);
      int len = strlen(me);
      me[len] = '\n'; 
      write(sockfd, me, (len+1) * sizeof(char));
      //strcpy(me, "");
    }
  }

     //}
  //if(fork()==0){
    while(1) {
      char c;
      if ( read(sockfd, them, strlen(them)*sizeof(char)) > 0)
      //printf("%s", them);
	write(1, them, strlen(them)*sizeof(char));

      
	}
    /*
  while(1){
    
    scanf("%d%d%c", &a, &b, &op);
    
      //fgets(buffer,255,stdin);
    n = write(sockfd,&a,sizeof(int));
    if (a == -1) break;
    write(sockfd, &b, sizeof(int));
    write(sockfd, &op, sizeof(char));
    
    read(sockfd, &res, sizeof(int));
    printf("%d\n", res);
  }
    */
    /*
      if (n < 0)
      error("ERROR writing to socket");
      bzero(buffer,256);
      n = read(sockfd,buffer,255);
      if (n < 0)
      error("ERROR reading from socket");
      printf("%s\n",buffer);
    */
  
  close(sockfd);
  return 0;
}
