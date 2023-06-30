#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#define buf_size 8192 
int main(int argc, char **argv)
{
	int fd_in, fd_out1,fd_out2,fd_out3;
        int length,len1,len2,len3;
	char buf[buf_size];
        int i=0,j=0;
        struct timeval t_start,t_end;
        float timeuse;
        if(argc != 2)
	{
		printf("Using : %s srcfilename \n", argv[0]);
		return -1;
	}
        gettimeofday(&t_start, NULL);

	if((fd_in = open(argv[1], O_RDONLY)) < 0)
	{
		perror("open");
		return -1;
	}
        length = lseek(fd_in, 0, SEEK_END);	
        j = length/buf_size;
        len1 = length/3;
        len2 = 2*len1;
        printf("file length=%d,len1=%d,len2=%d\n",length,len1,len2);
        
	if((fd_out1 = open("out1.txt", O_WRONLY| O_CREAT | O_TRUNC, 0666))  < 0)
	{
		perror("open");
		return -1;
	}
        if((fd_out2 = open("out2.txt", O_WRONLY| O_CREAT | O_TRUNC, 0666))  < 0)
        {       
                perror("open");
                return -1;
        }
        if((fd_out3 = open("out3.txt", O_WRONLY| O_CREAT | O_TRUNC, 0666))  < 0)
        {       
                perror("open");
                return -1;
        }
        lseek(fd_in,0,SEEK_SET);
	while(i<len1)
	{
	   read(fd_in, buf, sizeof(buf));
      	   write(fd_out1, buf, sizeof(buf));
           i=i+buf_size;
	}
	close(fd_out1);
	
        while(i<len2)
        {
           read(fd_in, buf, sizeof(buf));
           write(fd_out2, buf, sizeof(buf));
           i=i+buf_size;
        }
        close(fd_out2);

        while(i<j*buf_size)
        {
           read(fd_in, buf, sizeof(buf));
           write(fd_out3, buf, sizeof(buf));
           i=i+buf_size;
        }
        if(i<length)
        {
           len3= read(fd_in, buf, sizeof(buf));
           write(fd_out3, buf, len3);
        }
        close(fd_out3);
        gettimeofday(&t_end, NULL);
        timeuse=1000000*(t_end.tv_sec-t_start.tv_sec)+t_end.tv_usec-t_start.tv_usec; 
        timeuse/=1000000; 
        printf("Used Time:%f s\n",timeuse); 
        
        close(fd_in);
	return 0;
}
