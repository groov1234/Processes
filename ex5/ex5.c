// Write a program that forks a child and creates a shared pipe
// between the parent and child processes. Have the child write 
// the three messages to the parent and have the parent print out 
// the messages. 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MSGSIZE 16

char* msg1 = "hello world #1";
char* msg2 = "hello world #2";
char* msg3 = "hello world #3";

int main()
{
    // Your code here
    char inbuf[MSGSIZE];
    int p[2], pid, nbytes;
 
    if (pipe(p) < 0) {
        fprintf(stderr, "Pipe has burst");
        exit(1);
    }
 
    if ((pid = fork()) > 0) {

        printf("The child has written on a pipe\n");

        write(p[1], msg1, MSGSIZE);
        write(p[1], msg2, MSGSIZE);
        write(p[1], msg3, MSGSIZE);
 
        // Close the write end of the pipe
        close(p[1]);
        wait(NULL);
    }
 
    else {
        // Close the write end of the pipe
        close(p[1]);

        printf("Parent reading pipe\n");

        while ((nbytes = read(p[0], inbuf, MSGSIZE)) > 0) {
            printf("%s\n", inbuf);
        }
        if (nbytes != 0) {
            exit(2);
        }
        printf("Parent cleaned the pipe after reading\n");
    }
    return 0;
}
