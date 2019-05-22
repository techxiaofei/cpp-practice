/*
* 参考代码： https://docs.microsoft.com/zh-cn/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=vs-2019
*/

#include <iostream>
#include <vector>

using namespace std;

class B
{
public:
    explicit B(int length):length_(length),data_(new int[length]){ //带参数的构造函数  
        cout << "Constructor is called." << length_ << endl;
    }
    B(const B &b):length_(b.length_),data_(new int[b.length_]){   // 复制构造函数
        //copy data
        cout << "Copy Constructor is called." << length_ << endl;
    }
    B& operator = (const B &b){ //赋值操作符
        if (this != &b){
            delete[] data_;
            length_ = b.length_;
            data_ = b.data_;
        }
        cout << "The operator \"= \" is called." << length_ << endl;
        return *this;
    }
    B(B&& b)      // 移动构造函数，严格意义上移动构造函数的作用是，this去接管b的资源，同时b的资源被销毁
    {
        length_ = b.length_;
        data_ = b.data_;
        cout << "Move Constructor is called." <<length_<< endl;
    }
    B& operator = (B&& b){
        if (this != &b){
            delete[] data_;
            length_ = b.length_;
            data_ = b.data_;
        }
        cout << "Move operator is called." <<length_<< endl;
    }
    ~B() //析构函数  
    {
        if (data_ != nullptr){
            delete[] data_;
        }
        cout << "Destructor is called. " << length_ << endl;
    }

    inline int length() const{return length_;}

private:
    int length_;
    int* data_;
};
/**
 * 移动语义提高程序性能示例1
 */
B func()
{
    B t(2);
    return t;
}
/**
 * 移动语义提高程序性能示例2
 */
template <typename T>
void swap2(T& a, T& b){
    T tmp(std::move(a));
    a=std::move(b);
    b=std::move(tmp);
    
   /*
   T tmp = a;
   a = b;
   b = tmp;
   */
}

int main(){
    /*
    B a(2);
    a = func();
    */
    /*
    B a(4);
    B b(2);
    swap2(a,b);
    std::cout<< a.length() << b.length() << std::endl;
    */
    /**
     * 移动语义提高程序性能示例3
     */
    std::vector<B> v;
    std::cout<<"111"<<std::endl;
    v.push_back(B(2));
    std::cout<<"222"<<std::endl;
    v.push_back(B(4));
    std::cout<<"333"<<std::endl;
}

//g++ -o test move.cpp --std=c++11 -fno-elide-constructors