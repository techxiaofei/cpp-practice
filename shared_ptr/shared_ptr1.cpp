#include<iostream>
#include "shared_ptr.h"
using namespace std;

int main(){
    SharedPtr<int> ap1(new int(2));
    SharedPtr<int> ap2(ap1);
    SharedPtr<int> ap3 = ap2;
    return 0;
}

//g++ -o test shared_ptr1.cpp