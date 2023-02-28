#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char **argv){
    puts("begin");
    //fflush(NULL);
    execl("/bin/ls","l",NULL);
    puts("end");
    exit(0);
}