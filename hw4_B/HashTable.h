#pragma once
#include <string>
#include "Hash.h"
using namespace std;

template <typename T1, typename T2>
class HashTable
{
private:
    int n;
    Hash <T1> A;
    T2 *Value[6000];
public:
    HashTable(int _n):n(_n),A(_n){
        for(int i=0;i<_n;++i){
            Value[i]=nullptr;
        }
    };
    void addItem(const T1 &key, const T2 &value){
        if(!Value[A(key)]){
            Value[A(key)]=new T2;
        }
        *Value[A(key)]=value;
    };
    void removeItem(const T1 &key){
        delete Value[A(key)];
        Value[A(key)]=nullptr;
    };
    T2 *findByKey(const T1 &key){
        return Value[A(key)];
    };
};
