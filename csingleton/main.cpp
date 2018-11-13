//#include "sample.h"
//#include "a.h"
#include <stdio.h>
#include <string>
#include <map>
#include <vector>

class Test{
public:
    Test(){
        printf("Test new\n");
        a = 1;
        b = 2;
        c = 3;
    }

    ~Test(){
        printf("Test delete\n");
    }

private:
    int a;
    int b;
    int c;
};

//extern Sample* func();
//std::map<int, Test*> map_info;
//std::map<std::string, char*> cache;
std::vector<Test> vec;

int main(){

    Test test;
    vec.push_back(test);

    printf("===>%d,%d\n",vec.size(),vec.capacity());
    vec.clear();

    printf("===>%d,%d\n",vec.size(),vec.capacity());
    
    Test test2;
    vec.push_back(test2);
    printf("===>%d,%d\n",vec.size(),vec.capacity());
    std::vector<Test>().swap(vec);
    printf("===>%d,%d\n",vec.size(),vec.capacity());
    /*
    map_info[1] = new Test();

    printf("map.ptr=%p\n",map_info[1]);

    Test a;
    *map_info[1] = a;
    printf("map.ptr=%p\n",map_info[1]);
    /*
    Test b;
    map_info[2] = b;
    Test c;
    map_info[3] = c;
    */
   /*
    printf("map.size=%d\n",map_info.size());
    
    delete map_info[1];
    map_info.clear();
    /*
    Test d;
    map_info[4] = &d;
    printf("map.size=%d\n",map_info.size());
    */
    return 0;
}

//g++ -o test sample.cpp a.cpp main.cpp --std=c++11