#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<pthread.h>
void read1()	
{
int fda, i=0;
int fdb;
static char ch[20];
	fda= open("shaktiman",O_RDONLY);
	while(read(fda,ch,1)){
	write(1,ch,1);
	}
	close(fda);
}

void write1()
{
int fda, i=0;
int fdb;
static char ch[20];
	fdb=open("shakti",O_WRONLY);
	while(1)
		{			
			printf(">>\n ");
			gets(ch);
			int len=sizeof(ch);
			ch[len]='\n';
			write(fdb,ch,sizeof(ch)+1);
		}
	close(fdb);
}
void main()
{
	pthread_t ta, tb;
		pthread_create(&ta,NULL,(void*)read1,NULL);
		pthread_create(&tb,NULL,(void*)write1,NULL);
		pthread_join(ta,NULL);
		pthread_join(tb,NULL);
}
