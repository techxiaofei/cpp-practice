#include <stdio.h>

//typedef void(*p)(int a, int b);

void func(int a, int b){
    printf("callback func:%d+%d\n",a,b);
}

void c_callback(void (*callback)(int,int), int a, int b){
    callback(a, b);
}
//以上是c语言回调示例

/*
typedef void (*CPP_FUNC)(int, int);

class Cpp{

public:
    Cpp(){

        CPP_FUNC callback = (CPP_FUNC)&Cpp::cpp_func;
        c_callback(callback, 3, 4);
    }

    void cpp_func(int a, int b){
        printf("callback cpp_func:%d+%d\n",a,b);
    }

};
*/


int main(){
    //c语言回调
    c_callback(func, 3, 4);
    //封装成c++的回调
    //Cpp cpp;

    return 0;
}