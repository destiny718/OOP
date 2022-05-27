#pragma once
#include"weapon.h"
using namespace std;

class SomberWeapon:public Weapon{
public:
    using Weapon::get_name;
    using Weapon::get_level;
    using Weapon::upgrade;
    SomberWeapon(string name):Weapon(name){
        cout<<"Somber weapon "<<name<<" was created."<<endl;
    }
    ~SomberWeapon(){
        if(get_level()==0)    cout<<"Somber weapon "<<get_name()<<" was destroyed."<<endl;
        else  cout<<"Somber weapon "<<get_name()<<"+"<<get_level()<<" was destroyed."<<endl;
    }
};