#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <errno.h>
#include"driver.h"
int main(void){
	int fd;
	int quantum;
	 fd = open("/dev/mydevice",O_RDWR);
	if(fd  < 0)
	{
		printf("open error ! \n");
		return -1;
	}
	printf("open mydevice!\n");
	printf("请输入一个整数:");
	scanf("%d",&quantum);
	if(ioctl(fd,SCULL_IOCSQUANTUM,&quantum) < 0){
		perror("ioctl");
		printf("ioctl SCULL_IOCSQUANTUM error !\n");
		return -1;
	}
	printf("SCULL_IOCSQUANTUM-SCULL_IOCQQUANTUM:scull_quantum=%d\n",
			ioctl(fd,SCULL_IOCQQUANTUM,NULL));
	if(ioctl(fd,SCULL_IOCGQUANTUM,&quantum) < 0){
		printf("ioctl SCULL_IOCGQUANTUM error !\n");
		return -1;
	}
	printf("SCULL_IOCTQUANTUM-SCULL_IOCGQUANTUM:sucll_quantum=%d\n"
			,quantum);
	close(fd);
	printf("close sucess!\n");
	return 0;
}

