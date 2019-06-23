/*#include <stdio.h>
#include <sys/ipc.h> 
#include <sys/msg.h> 

int n;
int a[10][10];

int *writeMatrix();

int main()
{	key_t key; 
    	int msgid;   
	pid_t p=fork();
	if(p<0)
	{	fprintf(stderr,"Fork failed");
		return 1;
	}
	else if (p>0)//Parent process
	{	msgid = msgget(key, 0666 | IPC_CREAT);
		writeMatrix();
	}
	else//childprocess
	{	
	}
	return 0;
}
int *writeMatrix()
{	int n;
	printf("Enter the number of rows:");
	scanf("%d",&n);
	printf("Enter the element rowwise:\n");
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",&a[i][j]);
	return a;
}*/

#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h> 
#include <sys/msg.h> 

void main(){
	int n, i, j, pid;
	printf("\nEnter the order of matrix:");
	scanf("%d",&n);
	int mat1[n][n], mat2[n][n];
	printf("\nEnter the elements in row order:");
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			scanf("%d",&mat1[i][j]);
		}
	}
	key_t key;
	int msgid;
	key = ftok("progfile",65);
	msgid = msgget(key, 0666 | IPC_CREAT); 
	pid = fork();
	if(pid == 0){
		
				msgrcv(msgid,mat2,n,0,0);
			
		printf("\nDiagonal elements are:"); 
  		for(i=0; i<n; i++){
			printf("%d ",mat2[i][i]);
		}
	}
	else if(pid > 0){
		
				msgsnd(msgid,mat1,n,0);
		
	}
	else{
		printf("\nProcess creation failed");
	}
}
