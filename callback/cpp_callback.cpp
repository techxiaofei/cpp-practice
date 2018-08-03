#include <stdio.h>

typedef void(*CB_FUNC)(void* params);

/*
void func(void* params){
    printf("callback func\n");
}
*/

/*
* 外部提供c语言的函数指针回调接口，需要在c++里面通过成员函数方式调用，需要wrap一下。
*/
void call_func(CB_FUNC callback, void* params){
    callback(params);
}

template <class X>
class Wrap{
public:

    typedef void(X::*WrapFunc)(void* params);

    class WrapData{
    public:
        WrapData(X* x, WrapFunc func, void* params){
            x_ = x;
            func_ = func;
            params_ = params;
        }

        X* x_;
        WrapFunc func_;
        void* params_;
    };

    void start(X* x, WrapFunc func, void* params){
        WrapData* data = new WrapData(x, func, params);
        call_func(startWrap, (void*)data);
    }  

    static void startWrap(void* params){
        WrapData* data = static_cast<WrapData*>(params);
        ((data->x_)->*(data->func_))(data->params_);
    }
};


class A{
public:
    typedef void (A::*CPP_FUNC)(void* params);
    void Start(){
        printf("start func:%p\n",this);
       CPP_FUNC f = &A::func;
       Wrap<A>* wrap = new Wrap<A>();
       wrap->start(this, f, nullptr);
    }

    void func(void* params){
        printf("call func:%p\n",this);
    }
};


int main(){
    A a;
    a.Start();
    return 0;
}