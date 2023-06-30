#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <sys/ipc.h>
#include <semaphore.h>
#include <stdlib.h>
sem_t sem1;
int count=0;
void pthread1(void *arg)
{
  do{
     sem_wait(&sem1);
     count++;
     sem_post(&sem1);
  }while(count<100);
}
void pthread2(void *arg)
{
  while(count<100){ 
   sem_wait(&sem1);
   printf("count=%d\n",count);
   sem_post(&sem1);
  }
}
int main(int argc, char **argv)
{
        int ret;
        pthread_t id1,id2;
	
        ret=sem_init(&sem1,0,1);

        if(ret!=0)
        {
                perror("sem_init");
        }


        ret=pthread_create(&id1,NULL,(void *)pthread2, NULL);
        if(ret!=0)
                perror("pthread cread1");
        ret=pthread_create(&id2,NULL,(void *)pthread1, NULL);
        if(ret!=0)
                perror("pthread cread2");
        
        pthread_join(id1,NULL);
        pthread_join(id2,NULL);


        printf("compltete\n");
	return 0;
}
