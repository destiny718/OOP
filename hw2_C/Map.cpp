#include<iostream>
#include<cstring>
#include"Map.h"
using namespace std;

Map::Map(int n){
    data=new Pair[n];
}
int Map::operator[](string s) const{
    for(int i=0;i<sz;++i){
        if(data[i].hasKey(s)){
            return data[i].getVal();
        }
    }
    return 0;
};
int& Map::operator[](string s){
    for(int i=0;i<sz;++i){
        if(data[i].hasKey(s)){
            return data[i].getVal();
        }
    }
    data[sz].reset(s,0);
    sz++;
    return data[sz-1].getVal();
};
int Map::size(){
    return sz;
};
Map::~Map(){
    delete []data;
}