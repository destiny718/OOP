#pragma once
#include "Pair.h"

class Map{
    Pair * data;
    int sz=0;
public:
    Map(int n);
    int& operator[](string);
    int operator[](string) const;
    int size();
    ~Map();
};