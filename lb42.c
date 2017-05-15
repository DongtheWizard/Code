#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <errno.h>

void realls(char *);
void direct(char *);
int main(int argc, char * argv[]){
  direct(argv[1]);
}

void direct(char* a){

  struct stat s;
  chdir(a);
  DIR * w=opendir(".");
  struct dirent * d;

  while((d=readdir(w))!=NULL)
    {
      realls(d->d_name);
      if(strcmp(d->d_name, ".")!=0 && strcmp(d->d_name, "..")!=0)
      {
	stat(d->d_name, &s);
	if(S_ISDIR(s.st_mode))
	  {
	    //chdir(d->d_name);
	    direct(d->d_name);
	    chdir("..");
	  }
      }
    }

}
void realls(char * ar){
char perm[9];
  strcpy(perm, "---------");
  struct stat fl;
  
  if (stat(ar, &fl) == -1) {
    perror("stat");
    return;
  }

  switch(fl.st_mode & S_IFMT){
  case S_IFSOCK:
    printf("s");
    break;
  case S_IFLNK:
    printf("l");
    break;
  case S_IFREG:
    printf("-");
    break;
  case S_IFBLK:
    printf("b");
    break;
  case S_IFDIR:
    printf("d");
    break;
  case S_IFCHR:
    printf("c");
    break;
  case S_IFIFO:
    printf("p");
    break;
    
  default:
    printf("");
  }
  
  if((fl.st_mode & S_IRUSR)!=0){
    perm[0]='r';
  }
   if((fl.st_mode & S_IWUSR)!=0){
    perm[1]='w';
   }
  if((fl.st_mode & S_IXUSR)!=0){
    perm[2]='x';
  }
   if(fl.st_mode & S_IRGRP){
    perm[3]='r';
  }
 if(fl.st_mode & S_IWGRP){
    perm[4]='w';
  }
  if(fl.st_mode & S_IXGRP){
    perm[5]='x';
  }
  if(fl.st_mode & S_IROTH){
    perm[6]='r';
  }
  if(fl.st_mode & S_IWOTH){
    perm[7]='w';
  }
  if(fl.st_mode & S_IXOTH){
    perm[8]='x';
  }
 
  printf("%s ", perm);
  printf("%ld ", fl.st_nlink);
  struct passwd *p=getpwuid(fl.st_uid);
  printf("%s ", p->pw_name);
  struct group *p1=getgrgid(fl.st_gid);
  printf("%s ", p1->gr_name);
  printf("%ld ", fl.st_size);
  
  char *str = ctime(&fl.st_mtime);
  str[strlen(str)-1]=0;
  printf("%s ", str);

  printf("%s\n", ar);
  }
