#include <stdio.h>
#include <functional>
#include <memory>

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

typedef std::function<void (void* params)> WrapFunc;

class Wrap{
public:

    class WrapData{
    public:
        WrapData(WrapFunc func, void* params){
            func_ = func;
            params_ = params;
        }

        WrapFunc func_;
        void* params_;
    };

    void start(WrapFunc func, void* params){
        WrapData* data = new WrapData(func, params);
        call_func(startWrap, (void*)data);
    }  

    static void startWrap(void* params){
        WrapData* data = static_cast<WrapData*>(params);
        data->func_(data->params_);
    }
};


class A{
public:
    void Start(){
        printf("start func:%p\n",this);
        std::function<void (void*)> f = std::bind(&A::func, this, std::placeholders::_1);
       std::unique_ptr<Wrap> wrap(new Wrap());
       wrap->start(f, nullptr);
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