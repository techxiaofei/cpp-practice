#include <iostream>

using namespace std;

int GetHashCode(string str){
    int hash = 0;
    for (int i = 0; i < str.size(); i++){
        hash = s[i] + (31 * hash);
    }
    return hash;
}

int GetHashCode2(string str){
    int hash = 0;
    int skip = max(1, str.size()/8);
    for (int i = 0; i < str.size(); i+=skip){
        hash = s[i] + (31 * hash);
    }
    return hash;
}