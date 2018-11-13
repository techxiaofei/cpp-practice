#include <iostream>

using namespace std;

class B
{
public:
     B() :data(0)    //默认构造函数  
    {
        cout << "Default constructor is called." << endl;
    }
    B(int i) :data(i) //带参数的构造函数  
    {
        cout << "Constructor is called." << data << endl;
    }
    B(const B &b)   // 复制（拷贝）构造函数  
    {
        data = b.data; 
        cout << "Copy Constructor is called." << data << endl;
    }
    B(B&& b)      // 移动构造函数，严格意义上移动构造函数的作用是，this去接管b的资源，同时b的资源被销毁
    {
        this->data = b.data;
        cout << "Move Constructor is called." <<data<< endl;
    }
    B& operator = (const B &b) //赋值运算符的重载  
    {
        this->data = b.data;
        cout << "The operator \"= \" is called." << data << endl;
        return *this;
    }
    ~B() //析构函数  
    {
        cout << "Destructor is called. " << data <<" "<<&data<< endl;
    }
private:
    int data;
};

B fun(B c)
{
    cout << "split2" << endl;
    return c;
}

B func2()
{
    B t;
    return t;
}

int main(){
    //B a0(0);
    //cout << "split" << endl;
    //B&& a1 = fun(a0);

    B a;
    a = func2();
}

//g++ -o test move.cpp --std=c++11 -fno-elide-constructors