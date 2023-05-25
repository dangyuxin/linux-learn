#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFSIZE 1024

int main(int argc, char *argv[])
{
    int pd[2];
    char buf[BUFSIZE];
    if(pipe(pd)<0)
    {
        perror("pipe()");
        exit(1);
    }

    pid_t pid = fork();
    if(pid<0)
    {
        perror("fork()");
        exit(1);
    }

    if(pid==0)
    {
        close(pd[1]);
        int len = read(pd[0],buf,BUFSIZE);
        write(1,buf,len);
        close(pd[0]);
        exit(0);
    }
    else 
    {
        close(pd[0]);
        write(pd[1],"Hello World\n",12);
        close(pd[1]);
        wait(NULL);
    }

    return EXIT_SUCCESS;
}
