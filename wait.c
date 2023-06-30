/*wait.c*/

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main()
{
       pid_t pc, pr;
       pc = fork();

      if ( pc < 0 ){
          printf("create child prcocess error: %s\n", strerror(errno));
          exit(1);
	    }else if ( pc == 0){
          printf("I am child process with pid %d \n", getpid());
          sleep(3);
          exit(0);
  	  }else{
          printf("Now in parent process, pid = %d\n", getpid());
          printf("I am waiting child process to exit.\n");
          pr = wait(NULL); 
          if ( pr > 0 ){
              printf("I catched a child process with pid of %d\n", pr);
          }else{
              printf("error: %s\n", strerror(errno));
          }
      }
      exit(0);
}
