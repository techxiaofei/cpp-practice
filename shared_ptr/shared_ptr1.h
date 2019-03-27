#include<iostream>
#include<stdio.h>

template<class T>
class SharedPtr{
public:
    SharedPtr();
    SharedPtr(T* ptr);
    SharedPtr(const SharedPtr<T>& ap);
    ~SharedPtr();
    SharedPtr<T>& operator=(SharedPtr<T> ap);
    T& operator*();
    T* operator->();
    long GetCount() const;
    T* GetPtr()const;

private:
    T* _ptr;
    long* _pCount;
};

template<class T>
SharedPtr<T>::SharedPtr():_ptr(NULL),_pCount(new long(1)){}

template<class T>
SharedPtr<T>::SharedPtr(T* ptr):_ptr(ptr),_pCount(new long(1)){
    printf("SharedPtr constructor\n");
}

template<class T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& ap):_ptr(ap._ptr),_pCount(ap._pCount){
    ++(*this->_pCount);
    printf("SharedPtr copy %ld\n",*this->_pCount);
}

template<class T>
SharedPtr<T>::~SharedPtr(){
    if(--(*this->_pCount) == 0){
        delete this->_ptr;
        delete this->_pCount;
    }
    printf("SharedPtr des %ld\n",*this->_pCount);
}

template<class T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T> ap){
    if (this != &ap){
        if(--(*this->_pCount) == 0){
            delete this->_ptr;
            delete this->_pCount;
        }
        this->_ptr = ap._ptr;
        this->_pCount = ap._pCount;
        ++(*this->_pCount);
    }
    printf("SharedPtr operator %ld\n",*this->_pCount);
    return *this;
}

template<class T>
T& SharedPtr<T>::operator*(){
    return *(this->_ptr);
}

template<class T>
T* SharedPtr<T>::operator->(){
    return this->_ptr;
}

template<class T>
long SharedPtr<T>::GetCount() const{
    return *(this->_pCount);
}

template<class T>
T* SharedPtr<T>::GetPtr()const{
    return this->_ptr;
}