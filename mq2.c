#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h> 
#include<sys/msg.h> 

void main(){
	int n, i, j, pid;
	printf("Process A:\n");
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
		printf("Process B:\n");
		for(i=0; i<n; i++){
			for(j=0; j<n; j++){
				msgrcv(msgid,&mat2[i][j],1,0,0);
			}
		}
		printf("\nDiagonal elements are:"); 
  		for(i=0; i<n; i++){
			printf("%d ",mat2[i][i]);
		}
	}
	else if(pid > 0){
		
		for(i=0; i<n; i++){
			for(j=0; j<n; j++){
				msgsnd(msgid,&mat1[i][j],1,0);
			}
		}
		printf("Send complete matrix to message queue\n");
	}
	else{
		printf("\nProcess creation failed\n");
	}
}
