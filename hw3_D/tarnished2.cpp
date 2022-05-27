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

inline int required_stone(int start,int target,int level){
    int num1=(start%3==0||)?1:0;
    int num2=(start%3==1)?1:0;
    int num3=(start%3==2)?1:0;
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

Tarnished::Tarnished(){}

Tarnished::~Tarnished(){
    for(int i=1;i<=normal_stone_number;++i){
        if(normal_smithing_stones[i])   delete normal_smithing_stones[i];
    }  
    for(int i=1;i<=somber_stone_number;++i){
        if(somber_smithing_stones[i])   delete somber_smithing_stones[i]; 
    }  
    for(int i=0;i<normal_weapon_number;++i) delete normal_weapons[i];
    for(int i=0;i<somber_weapon_number;++i) delete somber_weapons[i];
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
            if(target<=normal_weapons[i]->get_level()){
                cout<<"Stay calm!"<<endl;
                break;
            }
            int init_level=normal_weapons[i]->get_level();
            int stone_level=init_level/3+1;
            for(int j=stone_level;3*j<=target;++j){
                if(!normal_smithing_stones[j]||!normal_smithing_stones[j]->greater_equal(required_stone(init_level,target,j))){
                    upgrade_failed(j,0);
                    break;
                }
            }
        }
    }
    if(!check_exist){
        for(int i=0;i<somber_weapon_number;++i){
            if(somber_weapons[i]&&somber_weapons[i]->get_name()==name){
                check_exist=true;
                if(target<=somber_weapons[i]->get_level()){
                    cout<<"Stay calm!"<<endl;
                    break;
                }
                bool check_stone=true;
                int j=somber_weapons[i]->get_level();
                for(;j<target;++j){ 
                    if(!somber_smithing_stones[j+1]){
                        check_stone=false;
                        break;
                    }
                }
                if(!check_stone){
                    upgrade_failed(j+1,1);
                    break;
                }
                else{
                    int j0=somber_weapons[i]->get_level();
                    j=somber_weapons[i]->get_level();
                    for(;j<target;++j){
                        somber_smithing_stones[j+1]->add_amount(-1);
                        substract(j+1,1,1);
                        if(!somber_smithing_stones[j+1]->greater_equal(1)){
                            delete somber_smithing_stones[j+1];
                            somber_smithing_stones[j+1]=nullptr;
                        }  
                        somber_weapons[i]->upgrade();
                        weapon_upgraded(j,1,name);
                    }
                    upgrade_successfally(j0,target,name);
                    break;
                }
            }
        }
    }
    if(!check_exist){
        cout<<"You don't have the right!"<<endl;
    }        
}