#include "String.h"
#include <string.h>
#include <stdio.h>

String::String(const char* str){
    if (str == nullptr || str == ""){
        str_ = new char[1];
        *str_ = '\0';
    }
    else{
        int length = strlen(str);
        str_ = new char[length+1];
        strcpy(str_, str);
        printf("constructor\n");
    }
}

String::~String(){
    delete[] str_;
    printf(" destructor\n");
}

String::String(const String& other){
    int length = strlen(other.str_);
    str_ = new char[length+1];
    strcpy(str_, other.str_);
    printf("copy constructor\n");
}

String& String::operator=(const String& other){
    if (this == &other){
        return *this;
    }
    delete[] str_;

    int length = strlen(other.str_);
    str_ = new char[length+1];
    strcpy(str_, other.str_);
    printf("assignment constructor\n");
    return *this;
}