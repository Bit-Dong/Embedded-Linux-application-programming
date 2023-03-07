#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#define LENGTH 100

void main(int argc, char *argv[])
{
	int fd,len;
	char buf[100];
	char str[LENGTH];
	fd=open(argv[1],O_CREAT|O_RDWR,0777);
	if(fd)
	{
		printf("\n%s open success!\n",argv[1]); 
		printf("Write to %s: ",argv[1]); 
		fgets(buf,128,stdin);
		write(fd,buf,strlen(buf));
		printf("Write success!\n"); 
		close(fd);
	}
	fd=open(argv[1],O_RDWR);
	printf("Read to %s: ",argv[1]); 
	len=read(fd,str,LENGTH);
	str[len]='\0';
	printf("%s\n",str);
	close(fd);
}
