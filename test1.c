#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<sys/mman.h>
#include<unistd.h>
void main()
{
	int fd;
	void *shm;
	fd = shm_open("/bin", O_CREAT|O_RDWR, 0666);
	ftruncate(fd,9);
	shm = mmap(0, 9, PROT_WRITE, MAP_SHARED, fd, 0);
	memset(shm, 0, 9);
	strcpy(shm, "AAAAAAAAA");
	return;
}
