        #include<stdio.h>
        #include<unistd.h>
        #include<fcntl.h>
        #include<string.h>
        #include<sys/mman.h>
        #include<unistd.h>
        #include<semaphore.h>
	#include<stdlib.h>
	#include<signal.h>
        int z[9],fd;
        sem_t *sem;	
        char *shm;
	int i,n;
        void alarmHandler()
        {
    	shm[z[i]]='A';
       	sem_post(sem);
    	munmap(shm, 200);
            close(fd);
    	exit(0);
        }
        void main(){
        	int j,k,c=0;
     
    	signal(SIGALRM, alarmHandler);
    	signal(SIGINT, alarmHandler);
        	fd = shm_open("/bin", O_CREAT|O_RDWR, 0666);
        	ftruncate(fd, 9);
        	shm = mmap(0, 9, PROT_WRITE, MAP_SHARED, fd, 0);
        //	memset(shm, 0, 200);
        	printf("SEAT FORMAT\nIf A:-Available\nX:-Blocked\nD:-Booked\n");
        	for(i=0;i<3;i++)
        	{
        		for(j=0;j<3;j++)
        		{
        			k=(i*3)+(j);
        			printf("%c\t",shm[k]);
				if(shm[k]=='A')
					c++;
    		}
        		printf("\n");
        	}
        	printf("Enter the number of seats: \n");
		scanf("%d", &n);
		while(n>c)
{
		printf("Seats not available\n");
		printf("Enter the number of seats: \n");
		scanf("%d",&n);
}
		int x[n],y[n];
		for(i=0;i<n;i++)
		{
		printf("Enter the row and column of the seat to be booked\n");
	   	scanf("%d %d",&x[i],&y[i]);
        	z[i]=(x[i]*3)+(y[i]);
             	while(shm[z[i]]=='D')
        	{
        		printf("Seat already occupied\n");
        		printf("Enter the row and column of the seat to be booked\n");
        		scanf("%d %d",&x[i],&y[i]);
        		z[i]=(x[i]*3)+(y[i]);
        	}
    		}
		for(i=0;i<n;i++)
		{
        	switch(z[i])
        	{
        	case 0:
        		sem = sem_open("/A1", O_CREAT|O_RDWR, 0666, 1);     
        		break;     
        	case 1:
        		sem = sem_open("/A2", O_CREAT|O_RDWR, 0666, 1);     
        		break;
        	case 2:
        		sem = sem_open("/A3", O_CREAT|O_RDWR, 0666, 1);     
        		break;
        	case 3:
        		sem = sem_open("/A4", O_CREAT|O_RDWR, 0666, 1);     
        		break;
        	case 4:
        		sem = sem_open("/A5", O_CREAT|O_RDWR, 0666, 1);     
        		break;
        	case 5:
        		sem = sem_open("/A6", O_CREAT|O_RDWR, 0666, 1);     
        		break;
        	case 6:
        		sem = sem_open("/A7", O_CREAT|O_RDWR, 0666, 1);     
        		break;
        	case 7:
        		sem = sem_open("/A8", O_CREAT|O_RDWR, 0666, 1);    
        		break;
        	case 8:
        		sem = sem_open("/A9", O_CREAT|O_RDWR, 0666, 1);     
        		break;
        	}	
     
     		
     
        	if(shm[z[i]]=='A')
        	{	
    			
    		shm[z[i]]='X';  
    		alarm(7);
    	    	sem_wait(sem);
    	    	printf("Transaction started\n");
    	    	sleep(6);
    	    	sem_post(sem);
    	    	printf("Transaction finished\n");
   		shm[z[i]]='D';
        	}
     
        	else
    		{
    		printf("Semaphore is acquired\n");
    		sem_wait(sem);
    		if(shm[z[i]]=='D')
    		{
    			printf("The seat is already occupied\nPlease book another seat\n");
    			sem_post(sem);
    		}
    		else
    		{
    				
    			shm[z[i]]='X';  
    			alarm(7);
    		    	//sem_wait(sem);
    		    	printf("Transaction started\n");
    		    	sleep(6);
    		    	sem_post(sem);
    		    	printf("Transaction finished\n");
    			shm[z[i]]='D';
    	   		close(fd);
         		}
     
        	}     
}
        //	munmap(shm, 200);
        //	close(fd);
        //	shm_unlink("/name");
        	return;
        }
