
/*
*标准库智能指针，非侵入式智能指针的实现
*/
#include <iostream>
#include <stdio.h>

template <typename T>
class SharedPtr{
public:
    SharedPtr(T* ptr);
    SharedPtr(const SharedPtr<T>& sp);
    SharedPtr<T>& operator=(const SharedPtr<T>& sp);
    ~SharedPtr();
    T& operator*();
    T* operator->();
    int GetCount() const;
    T* GetPtr() const;

private:
    T* ptr_;
    int* count_;
};

template<typename T>
SharedPtr<T>::SharedPtr(T* ptr):ptr_(ptr),count_(new int(1)){
    printf("SharedPtr constructor\n");
}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& sp):ptr_(sp.ptr_),count_(sp.count_){
    ++(*this->count_);
    printf("SharedPtr copy %d\n",*this->count_);
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& sp){
    if (this != &sp){
        if (--(*this->count_)==0){
            delete ptr_;
            delete count_;
        }
        ptr_ = sp.ptr_;
        count_ = sp.count_;
        ++(*this->count_);
    }
    printf("SharedPtr operator %d\n",*this->count_);
    return *this;
}

template<typename T>
SharedPtr<T>::~SharedPtr(){
    if (--(*this->count_) == 0){
        delete this->count_;
        delete this->ptr_;
    }
    printf("SharedPtr des %d\n",*this->count_);
}

template<typename T>
T& SharedPtr<T>::operator*(){
    return *(this->ptr_);
}

template<typename T>
T* SharedPtr<T>::operator->(){
    return this->ptr;
}

template<typename T>
int SharedPtr<T>::GetCount() const{
    return *this->count_;
}

template<typename T>
T* SharedPtr<T>::GetPtr() const{
    return this->ptr;
}
