### 进程环境


#### 1.main函数

    int main(int argc,char **argv);


#### 2.进程的终止

##### 正常终止
- 从main函数返回
- 调用exit
- 调用_exit 或 _Exit
- 最后一个线程从其启动历程返回
- 最后一个线程调用pthread_exit
    
##### 异常终止
- 调用abort
- 接到一个信号并终止
* 最后一个线程对其取消请求做出响应

#### 3.命令行参数分析
    getopt();



#### 4.环境变量
    KEY = VALUE

    getenv();
    setenv();
    putenv();

#### 5.C程序的存储空间布局


#### 6.库

#### 7.函数跳转

#### 8.资源的获取及其控制




