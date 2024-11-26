#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/wait.h>
#include "file12.h"

void prog(){
  printf("%ld about to create 2 child processes.\n", (long) getpid());
  pid_t p;
  p = fork();
  int x = 0;
  if(p<0){
    perror("fork fail\n");
    exit(1);
  } else if ( p == 0){
    long childp = (long) getpid();
    
    x = randomint() % 5 + 1;
    printf("%ld %dsec\n", childp, x);
    
    for (int c = 0; c < x; c++){
      sleep(1);
    }
    
    printf("%ld finished after %d seconds.\n", childp, x);
  }
  else{
    printf("x = %d\n", x);
    printf("Main Process %ld is done. Child %ld slept for %d sec\n", (long) getpid(), (long) p, x);
    pid_t p2;
    int status;
    p2 = wait(WEXITSTATUS(status));
    p2 = fork();
    int y = 0;
    if(p<0){
      perror("fork fail\n");
      exit(1);
    } else if ( p == 0){
      long childp2 = (long) getpid();
      
      y = randomint() % 5 + 1;
      printf("%ld %dsec\n", childp2, y);
      
      for (int c = 0; c < y; c++){
        sleep(1);
      }
      
      printf("%ld finished after %d seconds.\n", childp2, y);
    }
    else{
      printf("y = %d\n", y);
      printf("Main Process %ld is done. Child %ld slept for %d sec\n", (long) getpid(), (long) p, y);
    }
  }
}
  
int randomint(){
  int r_file = open("/dev/random", O_RDONLY , 0);
  
  int buff;
  int *p = &buff;
  int bytes = read(r_file, p, sizeof(int));
  
  close(r_file);
  
  return buff;
}
