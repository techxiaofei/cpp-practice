//string面试实现

#include <utility>
#include <string.h>
#include <stdio.h>
#include <vector>

class String{
public:
    String():data_(new char[1]){
        *data_ = '\0';
        printf("default constructor\n");
    }

    String(const char* str):data_(new char[strlen(str)+1]){
        strcpy(data_, str);
        printf("constructor\n");
    }

    String(const String& rhs):data_(new char[rhs.size()+1]){
        strcpy(data_, rhs.c_str());
        printf("copy constructor\n");
    }

    String(String&& rhs){
        data_ = rhs.data_;
        rhs.data_ = nullptr;
        printf("move constructor\n");
    }

    String& operator=(const String& rhs){
        if (this == &rhs)return *this;
        delete[] data_;
        data_ = new char[strlen(rhs.c_str()+1)];
        strcpy(data_,rhs.c_str());
        printf("assign constructor\n");
        return *this;
    }

    String& operator=(String&& rhs){
        if (this!=&rhs){
            delete[] data_;
            data_ = rhs.data_;
            rhs.data_ = nullptr;
        }
        printf("move assign\n");
        return *this;
    }

    ~String(){
        printf("desconstructor\n");
        delete[] data_;
    }

    int size() const{
        return strlen(data_);
    }

    const char* c_str() const{
        return data_;
    }

private:
    char* data_;

};

int main(){
    /*
    printf("before str\n");
    String str("aaa");
    printf("before str2\n");
    String str2(str);
    printf("before str3\n");
    String str3("bbb");
    printf("before str4\n");
    String str4;
    str4 = str3;
    */
   std::vector<String> vec;
   vec.push_back("abcdef");
   printf("===============1\n");
   String tmp1("abcdef");
   printf("===============\n");
   vec.push_back(tmp1);
   printf("===============2\n");
   //String tmp2("abcdef");
   printf("===============\n");
   vec.push_back(String("abcdef"));
   printf("===============3\n");
   //String tmp3("abcdef");
   printf("===============\n");
   vec.emplace_back(String("abcdef"));
   printf("===============4\n");
   String tmp4("abcdef");
   printf("===============\n");
   vec.emplace_back(std::move(tmp4));
    printf("===============\n");

    return 0;
}

//g++ -o test String2.cpp