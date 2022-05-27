#pragma once
#include<cstring>
#include"Task.h"

struct Gra{
    char nam[201][21];
    int tim[201];
    int mem[201];
    bool check;
};
class Server{
    int n,m;
    public:
        Gra gra[101]={0};
        Server(int N,int M):n(N),m(M){};
        void tick();
        bool submit_task(Task a);
        bool cancel_task(char a[30]);
};