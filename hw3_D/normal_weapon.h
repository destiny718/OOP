#pragma once
#include"weapon.h"
#include<string>
using namespace std;

class NormalWeapon: public Weapon{
public:
    using Weapon::get_name;
    using Weapon::get_level;
    using Weapon::upgrade;
    NormalWeapon(string name):Weapon(name){
        cout<<"Normal weapon "<<name<<" was created."<<endl;
    }
    ~NormalWeapon(){
        if(get_level()==0)    cout<<"Normal weapon "<<get_name()<<" was destroyed."<<endl;
        else  cout<<"Normal weapon "<<get_name()<<"+"<<get_level()<<" was destroyed."<<endl;
    }
};