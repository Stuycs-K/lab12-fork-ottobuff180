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
  int x = randomint() % 5 + 1;
  p = fork();
  if(p<0){
    perror("fork fail\n");
    exit(1);
  } else if ( p == 0){
    long childp = (long) getpid();
    
    printf("%ld %dsec\n", childp, x);
    
    for (int c = 0; c < x; c++){
      sleep(1);
    }
    
    printf("%ld finished after %d seconds.\n", childp, x);
  }
  else{
    pid_t p2;
    int x2 = randomint() % 5 + 1;
    p2 = fork();
    if(p2<0){
      perror("fork fail\n");
      exit(1);
    } else if ( p2 == 0){
      long childp = (long) getpid();
      
      printf("%ld %dsec\n", childp, x2);
      
      for (int c = 0; c < x2; c++){
        sleep(1);
      }
      
      printf("%ld finished after %d seconds.\n", childp, x2);
    }
    else {
      int status;
      pid_t p3 = wait(WEXITSTATUS(status));
      int y = x;
      if(p3 == p2){
        y = x2;
      }
      printf("Main Process %ld is done. Child %ld slept for %d sec\n", (long) getpid(), (long) p3, y);
    }
  }
}
  
int randomint(){
  int r_file = open("/dev/random", O_RDONLY , 0);
  
  int buff;
  int *p = &buff;
  int bytes = read(r_file, p, sizeof(int));
  
  close(r_file);
  
  if (buff < 0){
    return -buff;
  }
  return buff;
}
