#include <stdio.h>
#include <pthread.h>

/**
 * c++11中是线程安全的，在之前的版本不是线程安全的
 */
/*
class Singleton{
public:
    static Singleton& getInstance(){
        static Singleton singleton;
        return singleton;
    }
};
*/

/**
 * 线程不安全
 */
/*
class Singleton{
public:
    Singleton(){}
    static Singleton* getInstance();
private:
    static Singleton* p;
};

Singleton* Singleton::p = NULL;
Singleton* Singleton::getInstance(){
    if (p == NULL)p = new Singleton();
    return p;
}
*/

/**
 * 懒汉模式
 */
class Singleton{
public:
    //Singleton(){
        //pthread_mutex_init(&mutex, NULL);
    //}

    static Singleton* getInstance();

private:
    Singleton(){}
    static pthread_mutex_t mutex;
    static Singleton* p;
};
pthread_mutex_t Singleton::mutex = PTHREAD_MUTEX_INITIALIZER;
Singleton* Singleton::p = NULL;
Singleton* Singleton::getInstance(){
    if (p == NULL){
        pthread_mutex_lock(&mutex);
        if (p == NULL)p = new Singleton();
        pthread_mutex_unlock(&mutex);
    }
    return p;
}

/**
 * 懒汉模式2
 */
/*
class Singleton{
public:
    Singleton(){
        //pthread_mutex_init(&mutex, NULL);
    }

    static Singleton* getInstance();

private:
    static pthread_mutex_t mutex;
};
pthread_mutex_t Singleton::mutex = PTHREAD_MUTEX_INITIALIZER;
Singleton* Singleton::getInstance(){
    pthread_mutex_lock(&mutex);
    static Singleton p;
    pthread_mutex_unlock(&mutex);
    return &p;
}
*/

/**
 * 恶汉模式
 */
/*
class Singleton{
public:
    Singleton(){};
    static Singleton* getInstance();
private:
    static Singleton* p;
};

Singleton* Singleton::p = new Singleton();
Singleton* Singleton::getInstance(){
    return p;
}
*/

int main(){
    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();
    printf("s1 addr=%p, s2 addr=%p\n",s1, s2);
    return 0;
}

//g++ -O singleton.cpp --std=c++11