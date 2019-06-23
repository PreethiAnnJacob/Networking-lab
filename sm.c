//Preethi Ann Jacob 22-03-2019
/*To implement a program to read a string in one process and print the string in another process using shared memory*/
#include <stdio.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/shm.h>
int main()
{	int p=fork();
	key_t key = ftok("shmfile",65);
	int shmid = shmget(key,1024,0666|IPC_CREAT); 
	char *str = (char*) shmat(shmid,(void*)0,0); 
	if(p<0)
		printf("Fork Failed\n");
	else if (p==0)
	{	printf("\nData read from memory: %s\n",str); 
	    	shmdt(str); 
	    	shmctl(shmid,IPC_RMID,NULL);
	
	} 
	else
	{	
		scanf("%s",str);
		printf("Data written in memory: %s\n",str);
		shmdt(str);
		 
	}
	return 0;
}
