#include<iostream>
#include<cmath>
#include<cstring>
#include"Monomial.h"
using namespace std;

Monomial::Monomial(){}

Monomial::Monomial(int _c, int _d):coe(_c),deg(_d){}

istream& operator>>(istream& in,Monomial& dst){
    string s;
    in>>s;
    int _c=0,_d=0;
    int num[1000]={0};
    if(s.length()==1){
        dst.coe=_c;
        dst.deg=_d;
        return in;
    }
    else if(s.at(0)!='-'){
        int i=0;
        while(s.at(i)!='x'){
            num[i]=s.at(i)-'0';
            i++;
        }
        int pow=1;
        for(int j=0;j<i;++j){
            _c+=(num[i-j-1]*pow);
            pow*=10;
        }
        if(s.at(i+2)!='-'){
            if(s.length()>(i+3)){
                _d=(s.at(s.length()-2)-'0')*10+s.at(s.length()-1)-'0';
            }
            else{
                _d=s.at(s.length()-1)-'0';
            }
        }
        else{
            if(s.length()>(i+4)){
                _d=(s.at(s.length()-2)-'0')*10+s.at(s.length()-1)-'0';
                _d=_d*(-1);
            }
            else{
                _d=s.at(s.length()-1)-'0';
                _d=_d*(-1);
            }
        }
        dst.coe=_c;
        dst.deg=_d;
        return in;
    }
    else{
        int i=1;
        while(s.at(i)!='x'){
            num[i]=s.at(i)-'0';
            i++;
        }
        int pow=1;
        for(int j=1;j<i;++j){
            _c+=(num[i-j]*pow);
            pow*=10;
        }
        _c=_c*(-1);
        if(s.at(i+2)!='-'){
            if(s.length()>(i+3)){
                _d=(s.at(s.length()-2)-'0')*10+s.at(s.length()-1)-'0';
            }
            else{
                _d=s.at(s.length()-1)-'0';
            }
        }
        else{
            if(s.length()>(i+4)){
                _d=(s.at(s.length()-2)-'0')*10+s.at(s.length()-1)-'0';
                _d=_d*(-1);
            }
            else{
                _d=s.at(s.length()-1)-'0';
                _d=_d*(-1);
            }
        }
        dst.coe=_c;
        dst.deg=_d;
        return in;
    }
}

ostream& operator<<(ostream& out,Monomial& src){
    out<<src.coe<<"x^"<<src.deg<<endl;
    return out;
}

Monomial Monomial::operator+(const Monomial &x) const{
    Monomial tmp=x;
    if(tmp.coe==0){
        Monomial new_m(this->coe,this->deg);
        return new_m;
    }
    else if(this->coe+tmp.coe==0){
        Monomial new_m(0,0);
        return new_m;
    }
    else{
        Monomial new_m(this->coe+tmp.coe,tmp.deg);
        return new_m;
    }
}

Monomial Monomial::operator-(const Monomial &x) const{
    Monomial tmp=x;
    if(tmp.coe==0){
        Monomial new_m(this->coe,this->deg);
        return new_m;
    }
    else if(this->coe-tmp.coe==0){
        Monomial new_m(0,0);
        return new_m;
    }
    else{
        Monomial new_m(this->coe-tmp.coe,tmp.deg);
        return new_m;
    }
}

Monomial Monomial::operator*(const Monomial &x) const{
    Monomial tmp=x;
    if(tmp.coe==0||this->coe==0){
        Monomial new_m(0,0);
        return new_m;
    }
    else{
        Monomial new_m(this->coe*tmp.coe,this->deg+tmp.deg);
        return new_m;
    }
}

Monomial Monomial::operator/(const Monomial &x) const{
    if(this->coe!=0){
        Monomial tmp=x;
        Monomial new_m(this->coe/tmp.coe,this->deg-tmp.deg);
        return new_m;
    }
    else{
        Monomial new_m(0,0);
        return new_m;
    }
}

int Monomial::definite_integral(const int a, const int b) const{
    Monomial new_m(this->coe/(this->deg+1),this->deg+1);
    return (new_m.get_val(b)-new_m.get_val(a));
}

int Monomial::get_val(int x) const{
    int num=pow(x,this->deg)*this->coe;
    return num;
}

Monomial Monomial::derive() const{
    if(this->deg!=0){
        Monomial new_m(this->coe*this->deg,this->deg-1);
        return new_m;
    }
    else{
        Monomial new_m(0,0);
        return new_m;
    }
}
