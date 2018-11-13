#ifndef __SAMPLE_H__
#define __SAMPLE_H__

#include <vector>

class Sample{

public:
    Sample();
    ~Sample();

    static Sample* getInstance();

private:
    int a;
    std::vector<int> b;
};

#endif