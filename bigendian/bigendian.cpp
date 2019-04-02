#include <iostream>
#include <stdio.h>

void IsBigEndian(){
    short int a = 0x1234;
    char b = *(char*)&a;
    if (b == 0x12){
        printf("big endian\n");
    }else if(b == 0x34){
        printf("little endian\n");
    }
    else{
        printf("errror1\n");
    }
}

void IsBigEndian2(){
    union tmp{
        short int a;
        char b;
    }tmp;

    tmp.a = 0x1234;
    if (tmp.b == 0x12){
        printf("big endian\n");
    }else if(tmp.b == 0x34){
        printf("little endian\n");
    }
    else{
        printf("errror1\n");
    }
}

int main(){
    IsBigEndian();
    IsBigEndian2();
}

//g++ -o test bigendian.cpp