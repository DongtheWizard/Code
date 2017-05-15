#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char * argv[]){
  char perm[9];
  strcpy(perm, "---------");
  struct stat fl;
  stat(argv[1], &fl);
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
  printf("%s ", ctime(&fl.st_mtime));
  
}
/*dev_t     st_dev;     ID of device containing file 
    ino_t     st_ino;     inode number 
    mode_t    st_mode;    protection 
    nlink_t   st_nlink;   number of hard links 
    uid_t     st_uid;     user ID of owner 
    gid_t     st_gid;     group ID of owner 
    dev_t     st_rdev;     device ID (if special file) 
    off_t     st_size;    total size, in bytes 
    blksize_t st_blksize; blocksize for file system I/O 
    blkcnt_t  st_blocks;  number of 512B blocks allocated
    time_t    st_atime;   time of last access 
    time_t    st_mtime;   time of last modification 
    time_t    st_ctime;   time of last status change 
    -rwx------ 1 er160985 ece-summer2016 0 juil.  5 11:37 f1

*/
