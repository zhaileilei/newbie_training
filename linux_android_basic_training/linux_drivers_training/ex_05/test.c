#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
int main(void){
	
	int fd,fd1;
	int cnt =2;
	fd = open("/dev/cseq", O_RDWR);

	if(fd < 0) {
		printf("open myseq failed.\n");
		return -1;
	}
	if(fork()==0){
		while(cnt){
			cnt--;
			write(fd,"hello,china",12);
			printf("wo shi zi jin cheng\n");
		}
	}

	else {
		while(cnt){
			cnt--;
			write(fd,"hello,shanxi",13);
			printf("wo shi fu jin cheng \n");
		}
	}

	close(fd);
	wait(NULL);
	return 0;
}
