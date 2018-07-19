#include "String.h"

int main(){
    String a = "abc";
    String b;
    b = a;
    return 0;
}

//g++ -o test String.cpp main.cpp std=c++11