#include <stdio.h>
#include "sample.h"

static Sample * instance = NULL;

Sample* Sample::getInstance(){
    if (instance != NULL){
        printf("not null return\n");
        return instance;
    }
    printf("null create\n");
    instance = new Sample();
    return instance;
}

Sample::Sample(){
    a = 0;
    b.clear();
    b.push_back(1);
}

Sample::~Sample(){

}