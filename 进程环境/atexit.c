#include <stdio.h>
#include <stdlib.h>

void f1(){
    printf("11111\n");
}
void f2(){
    printf("22222\n");
}
void f3(){
    printf("333333\n");
}
int main(){
    puts("begin");
    atexit(f1);
    atexit(f2);
    atexit(f3);
    puts("end");
    return 0;
}