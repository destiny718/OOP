#include<iostream>
#include<string>
#include"Pokemon.h"

using namespace std;

Pokemon::Pokemon(int hp,int atk,string name):hp(hp),atk(atk),name(name){
    tot_hp=hp;
}

string Pokemon::get_name(){
    return this->name;
}

bool Pokemon::alive(){
    if(Pokemon::hp>0)   return true;
    else    return false;
}

int Pokemon::get_hp(){
    return Pokemon::hp;
}

int Pokemon::get_atk(){
    return Pokemon::atk;
}

Pokemon::~Pokemon(){}

////
Squirtle::Squirtle(int hp,int atk,string name):Pokemon(hp,atk,name){}

void Squirtle::use_skill(int idx, Pokemon* target){
    if(idx==0){//Regen
        int bandage=this->tot_hp/5;
        if(this->hp+bandage>this->tot_hp){
            hp=tot_hp;
        }
        else{
            hp+=bandage;
        }
        cout<<this->get_name()<<" used Regen"<<endl;
    }
    else{//Splash
        cout<<this->get_name()<<" used Splash to "<<target->get_name()<<endl;
        target->hurt(this->atk,this);
    }
}

void Squirtle::hurt(int dmg,Pokemon* from){
    int get_hurt=0;
    if(this->hp<this->tot_hp/5){
        get_hurt=dmg/2;
        if(get_hurt==0) get_hurt=1;
    }
    else{
        get_hurt=dmg;
    }
    this->hp-=get_hurt;
    cout<<this->get_name()<<" received "<<get_hurt<<" damage from "<<from->get_name()<<endl;
}

Squirtle::~Squirtle(){}

////
Charizard::Charizard(int hp,int atk,string name):Pokemon(hp,atk,name){
    fire=1;
}

void Charizard::use_skill(int idx, Pokemon* target){
    if(idx==0){//Ignite
        fire+=1;
        atk*=2;
        cout<<this->get_name()<<" used Ignite"<<endl;
        hurt(fire*10,this);
    }
    else{//Flame
        cout<<this->get_name()<<" used Flame to "<<target->get_name()<<endl;
        target->hurt(atk,this);
    }
}

void Charizard::hurt(int dmg,Pokemon* from){
    this->hp-=dmg;
    cout<<this->get_name()<<" received "<<dmg<<" damage from "<<from->get_name()<<endl;
    if(dmg>10&&this!=from){
        int fhurt=dmg/5;
        from->hurt(fhurt,this);
    }
}

Charizard::~Charizard(){}