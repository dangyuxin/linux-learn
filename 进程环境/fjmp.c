#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
    //实现函数跳转
static jmp_buf save;

void d(){
    printf("%s begin\n",__FUNCTION__);
    printf("%s jump now!\n",__FUNCTION__);
    longjmp(save,1);//用0捣乱不行，函数会返回1
    printf("%s end\n",__FUNCTION__);
}
void c(){
    printf("%s begin\n",__FUNCTION__);
    printf("%s call d()\n",__FUNCTION__);
    d();
    printf("%s d() return \n",__FUNCTION__);
    printf("%s end\n",__FUNCTION__);
}
   
void b(){
    printf("%s begin\n",__FUNCTION__);
    printf("%s call c()\n",__FUNCTION__);
    c();
    printf("%s c() return \n",__FUNCTION__);
    printf("%s end\n",__FUNCTION__);
}
void a(){
    int res;
    printf("%s begin\n",__FUNCTION__);
    res = setjmp(save);
    if(!res){
        printf("%s call b()\n",__FUNCTION__);
        b();
        printf("%s b() return \n",__FUNCTION__);
    }
    else{
        printf("%s jump back herr with code %d\n",__FUNCTION__,res);
    }
    printf("%s end\n",__FUNCTION__);
} 

int main(){
    a();
    return 0;
}