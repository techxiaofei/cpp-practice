/* 测试String.h
#include "String.h"

int main(){
    String a = "abc";
    String b;
    b = a;
    return 0;
}

//g++ -o test String.cpp main.cpp --std=c++11
*/

#include <stdio.h>
#include <iostream>
#include <string>

int main(){
    std::string str1("abc");
    printf("pointer str1:%p\n", str1.c_str());
    std::string str2 = str1;
    printf("pointer str2:%p\n", str2.c_str());
    str2[1] = '1';
    //printf("str2 get:%c\n",str2[1]);
    printf("pointer str2:%p\n", str2.c_str());
    return 0;
}

//g++ -o test main.cpp --std=c++11