#pragma once
#include<vector>
#include<string>
#include<cmath>

using namespace std;

class Student{
public:
    vector<int> courses;
    virtual vector<int> choose(vector<int> credit,int l,int r)=0;
};

class StudentTypeA:public Student{
public:
    vector<int> choose(vector<int> credit,int l,int r){
        for(int i=l;i<=r;++i){
            if(credit[i-1]<=2){
                courses.push_back(i);
            }
        }
        return courses;
    }
};

class StudentTypeB:public Student{
public:
    bool IsPrime(int num){
        if(num==1)   return false;
        if(num==2)	return true;
        for(int i=2;i<sqrt(num)+1;i++){
            if((num%i)==0)	return false;
        }
        return true;
    }
    vector<int> choose(vector<int> credit,int l,int r){
        for(int i=l;i<=r;++i){
            if(IsPrime(i))  courses.push_back(i);
        }
        return courses;
    }
};

class StudentTypeC:public Student{
public:
    vector<int> choose(vector<int> credit,int l,int r){
        for(int i=l;i<=r;++i){
            if(i%credit[i-1]==0)  courses.push_back(i);
        }
        return courses;
    }
};