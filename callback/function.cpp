#include <stdio.h>
#include <functional>


class A{
public:
    void Start(){
        std::function<void (int)> f = std::bind(&A::func, this, std::placeholders::_1);
        f(100);
    }

    void func(int a){
        printf("call func:%d\n",a);
    }
};


int main(){

    A a;
    a.Start();

    return 0;
}