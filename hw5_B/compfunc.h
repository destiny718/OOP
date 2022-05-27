#pragma once

#include "func.h"

class CompFunc : public Func{
private:
    // Todo
    // 声明成员变量
    Func *otr,*inr;
public:
    CompFunc(Func *outer, Func* inner):otr(outer),inr(inner){};
    double getPoint(double point){
        return (otr->getPoint(inr->getPoint(point)));
    }
    ~CompFunc(){
        delete otr;
        delete inr;
    }
    // compute f(g(x))
    // Todo
    // 请参照指数函数类(ExpFunc)实现一个复合函数类
    // 并且要求，传入的参数的析构在该类被析构时同时析构
};