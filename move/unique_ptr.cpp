#include <memory>
#include <map>
#include <stdio.h>

using namespace std;

class Foo{
public:
    Foo(){
        printf("constructor\n");
    }

    ~Foo(){
        printf("destructor\n");
    }

    Foo(const Foo& foo){
        printf("copy constructor\n");
    }

    Foo(Foo&& foo){
        printf("move constructor\n");
    }

    Foo& operator=(const Foo& foo){
        printf("assign constructor\n");
        return *this;
    }

    Foo& operator=(Foo&& foo){
        printf("move assign constructor\n");
        return *this;
    }
    
    void test(){
        printf("test\n");
    }
};

map<int, unique_ptr<Foo>> maps;

unique_ptr<Foo>* getFoo(){
    return &maps[1];
}

int main(){
    
    maps[1] = unique_ptr<Foo>(new Foo());
    printf("%d\n",(int)maps.size());
    unique_ptr<Foo>* foo = getFoo();
    (*foo)->test();
    printf("%d\n",(int)maps.size());
    return 0;
}

//g++ -o test unique_ptr.cpp --std=c++11