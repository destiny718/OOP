#include<iostream>
#include<string>
#include"tarnished.h"
using namespace std;

int normal_weapon_number=0;
int somber_weapon_number=0;
int normal_stone_number=1;
int somber_stone_number=1;

void upgrade_successfally(int start,int target,string name){
    cout<<"Upgrade "<<name;
    if(start!=0)    cout<<"+"<<start;
    cout<<" to "<<name<<"+"<<target<<" Successfully."<<endl;
}

void weapon_upgraded(int start,int type,string name){
    if(type==0)     cout<<"Normal weapon ";
    else    cout<<"Somber weapon ";
    cout<<name;
    if(start!=0)    cout<<"+"<<start;
    cout<<" was upgraded to "<<name<<"+"<<start+1<<"."<<endl;
}

inline int required_stone1(int start,int target,int stone_level){
    int num1=0,num2=0,num3=0;
    if(stone_level*3-2>start)   num1=1;
    if((stone_level*3-1)>start&&(stone_level*3-1)<=target)  num2=1;
    if(stone_level*3<=target)     num3=1;
    return (2*num1+4*num2+6*num3);
}

inline int required_stone(int number){
    return (number%3+1)*2;
}

void upgrade_failed(int level,int type){
    cout<<"Upgrade failed for lacking ";
    if(type==0){
        cout<<"normal smithing stone "<<level<<"."<<endl;
    }
    else{
        cout<<"somber smithing stone "<<level<<"."<<endl;
    }
}

void substract(int level,int type,int number){
    if(type==0){
        cout<<"Normal smithing stone "<<level<<" was substracted with "<<number<<"."<<endl;
    }
    else{
        cout<<"Somber smithing stone "<<level<<" was substracted with "<<number<<"."<<endl;
    }
}

Tarnished::Tarnished(){
    for(int i=0;i<MAX_STONES;++i){
        somber_smithing_stones[i]=nullptr;
        normal_smithing_stones[i]=nullptr;
    }
}

Tarnished::~Tarnished(){
    for(int i=1;i<=normal_stone_number;++i){
        if(normal_smithing_stones[i]!=nullptr)   normal_smithing_stones[i]->~NormalSmithingStone();
    }  
    for(int i=1;i<=somber_stone_number;++i){
        if(somber_smithing_stones[i]!=nullptr)   somber_smithing_stones[i]->~SomberSmithingStone(); 
    }  
    for(int i=0;i<normal_weapon_number;++i)  normal_weapons[i]->~NormalWeapon();
    for(int i=0;i<somber_weapon_number;++i)  somber_weapons[i]->~SomberWeapon();
}

void Tarnished::pick_up_stone(int type, int level, int number){
    if(type==0){
        if(!normal_smithing_stones[level]){
            normal_smithing_stones[level]=new NormalSmithingStone(level);
        }
        if(level>normal_stone_number)   normal_stone_number=level;
        normal_smithing_stones[level]->Add_number(number);
    }
    else{
        if(!somber_smithing_stones[level]){
            somber_smithing_stones[level]=new SomberSmithingStone(level);
        }
        if(level>somber_stone_number)   somber_stone_number=level;
        somber_smithing_stones[level]->Add_number(number);
    }
}

void Tarnished::pick_up_weapon(int type, string name){
    if(type==0){
        normal_weapons[normal_weapon_number]=new NormalWeapon(name);
        normal_weapon_number++;
    }
    else{
        somber_weapons[somber_weapon_number]=new SomberWeapon(name);
        somber_weapon_number++;
    }
}

void Tarnished::upgrade_weapon(int target,string name){
    bool check_exist=false;
    for(int i=0;i<normal_weapon_number;++i){
        if(normal_weapons[i]&&normal_weapons[i]->get_name()==name){
            check_exist=true;
            if(target<=normal_weapons[i]->get_level()){
                cout<<"Stay calm!"<<endl;
                return ;
            }
            int j=normal_weapons[i]->get_level(),j0=j;
            int stone_level=(j/3)+1;
            int total_number=0;
            for(;j<target;++j){
                if(j%3==0&&j!=j0){
                    stone_level++;
                    total_number=0;
                }
                total_number+=required_stone(j);   
                if((normal_smithing_stones[stone_level])==nullptr||(!normal_smithing_stones[stone_level]->greater_equal(total_number))){
                    upgrade_failed(stone_level,0);
                    return;
                }
            }
            j=j0;
            stone_level=(j/3)+1;
            for(;j<target;++j){
                if(j%3==0&&j!=j0)   stone_level++;
                normal_smithing_stones[stone_level]->add_amount((-1*required_stone(j)));
                substract(stone_level,0,required_stone(j));
                if(!normal_smithing_stones[stone_level]->greater_equal(1)){
                    //delete normal_smithing_stones[stone_level];
                    normal_smithing_stones[stone_level]->~NormalSmithingStone();
                    normal_smithing_stones[stone_level]=nullptr;
                }  
                normal_weapons[i]->upgrade();
                weapon_upgraded(j,0,name);
            }
            upgrade_successfally(j0,target,name);
            return;
        }
    }
    if(!check_exist){
        for(int i=0;i<somber_weapon_number;++i){
            if(somber_weapons[i]&&somber_weapons[i]->get_name()==name){
                check_exist=true;
                if(target<=somber_weapons[i]->get_level()){
                    cout<<"Stay calm!"<<endl;
                    return;
                }
                int j=somber_weapons[i]->get_level();
                for(;j<target;++j){ 
                    if(!somber_smithing_stones[j+1]){
                        upgrade_failed(j+1,1);
                        return;
                    }
                }
                int j0=somber_weapons[i]->get_level();
                j=j0;
                for(;j<target;++j){
                    somber_smithing_stones[j+1]->add_amount(-1);
                    substract(j+1,1,1);
                    if(!somber_smithing_stones[j+1]->greater_equal(1)){
                        //delete somber_smithing_stones[j+1];
                        somber_smithing_stones[j+1]->~SomberSmithingStone();
                        somber_smithing_stones[j+1]=nullptr;
                    }  
                    somber_weapons[i]->upgrade();
                    weapon_upgraded(j,1,name);
                }
                upgrade_successfally(j0,target,name);
                return ;
            }
        }
    }
    if(!check_exist){
        cout<<"You don't have the right!"<<endl;
        return ;
    }        
}