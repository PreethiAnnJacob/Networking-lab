#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
int main() 
{ 
    //We use one pipe to send input string from parent to child and to read it from child process. 
    int fd[2];  // Used to store two ends of pipe     
    char str[100];  
    pid_t p; 
    if (pipe(fd)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
    p = fork(); 
    if (p < 0) 
    { 
        fprintf(stderr, "fork Failed" ); 
        return 1; 
    } 
    // Parent process 
    else if (p > 0) 
    {  
        close(fd[0]);  // Close reading end of pipe 
	printf("Parent: Enter the string:");
	scanf("%s",str);
        // Write input string and close writing end of pipe. 
        write(fd[1],str, strlen(str)+1); 
        close(fd[1]);  
    } 
    // child process 
    else
    { 	char readstr[100];
        close(fd[1]);  // Close writing end of pipe 
        // Read a string using pipe  
        read(fd[0], readstr, 100); 
        // Close reading end
        close(fd[0]);  
	//print read string
	printf("child process: %s was read from parent\n",readstr);
        exit(0); 
    } 
} 
