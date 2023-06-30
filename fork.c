#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	pid_t result;
	result = fork();
	if(result == -1){
		perror("fork");
		exit;
	}
	else if(result == 0){
         	printf("result = %d In child process!! pid=%d\n",result,getpid());
}
	else{
	       printf("result = %d In father process!! pid= %d\n",result,getpid());
	}
}

