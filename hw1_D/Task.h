#pragma once
#include<cstring>


class Task{
    public:
    int d,n,m;
    char s[30];
        Task(char a[30],int D,int N,int M){
            d=N;n=M;m=D;
            strcpy(s,a);
        }
};