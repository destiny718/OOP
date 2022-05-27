#pragma once
#include<string>
#include<vector>
#include"Student.h"

using namespace std;

vector<int> select(vector<int> credit,int l,int r,Student* student){
    return student->choose(credit,l,r);
}
