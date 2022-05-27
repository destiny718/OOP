#include<iostream>
#include<string>
#include"tarnished.h"
using namespace std;

int normal_weapon_number=0;
int somber_weapon_number=0;

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
    for(int i=0;normal_smithing_stones[i];++i)  delete normal_smithing_stones[i];
    for(int i=0;somber_smithing_stones[i];++i)  delete somber_smithing_stones[i];
    for(int i=0;i<normal_weapon_number;++i) delete normal_weapons[i];
    for(int i=0;i<somber_weapon_number;++i) delete somber_weapons[i];
}

void Tarnished::pick_up_stone(int type, int level, int number){
    if(type==0){
        if(!normal_smithing_stones[level]){
            normal_smithing_stones[level]=new NormalSmithingStone(level);
        }
        normal_smithing_stones[level]->Add_number(number);
    }
    else{
        if(!somber_smithing_stones[level]){
            somber_smithing_stones[level]=new SomberSmithingStone(level);
        }
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
            check_exist=true;
            bool check_stone=false;
            int stone_level=(target/3)+1;
            int now_target=target;
            int j=1;
            int uptime=0;
            for(;j<=stone_level;++j){
                if(now_target==1){
                    if(normal_smithing_stones[j]&&normal_smithing_stones[j]->greater_equal(2)){
                        check_stone=true;
                        uptime++;
                    }
                    break;
                }
                else if(now_target==2){
                    if(normal_smithing_stones[j]&&normal_smithing_stones[j]->greater_equal(4)){
                        check_stone=true;
                        uptime+=2;
                    }
                    break;
                }
                else if(now_target>=3){
                    if(normal_smithing_stones[j]&&normal_smithing_stones[j]->greater_equal(6)&&now_target==3){
                        check_stone=true;
                        uptime+=3;
                        break;
                    }
                    else if(!normal_smithing_stones[j]||!normal_smithing_stones[j]->greater_equal(6)){
                        break;
                    }
                    else{
                        now_target-=3;
                    }
                }
            }
            if(!check_stone){
                upgrade_failed(j,0);
                break;
            }
            else{
                int initlevel=normal_weapons[i]->get_level();
                for(int k=1;k<j;++k){
                    normal_smithing_stones[k]->add_amount(-2);
                    substract(k,0,2);
                    normal_weapons[i]->upgrade();
                    if(normal_weapons[i]->get_level()==1){
                        cout<<"Normal weapon "<<normal_weapons[i]->get_name()<<" was upgraded to "<<normal_weapons[i]->get_name()<<"+1."<<endl;
                    }
                    else{
                        cout<<"Normal weapon "<<normal_weapons[i]->get_name()<<"+"<<normal_weapons[i]->get_level()-1<<" was upgraded to "<<normal_weapons[i]->get_name()<<"+"<<normal_weapons[i]->get_level()<<"."<<endl;
                    }
                    normal_smithing_stones[k]->add_amount(-4);
                    substract(k,0,4);
                    normal_weapons[i]->upgrade();
                    cout<<"Normal weapon "<<normal_weapons[i]->get_name()<<"+"<<normal_weapons[i]->get_level()-1<<" was upgraded to "<<normal_weapons[i]->get_name()<<"+"<<normal_weapons[i]->get_level()<<"."<<endl;
                    normal_smithing_stones[k]->add_amount(-6);
                    substract(k,0,6);
                    if(!normal_smithing_stones[k]->greater_equal(1))    delete normal_smithing_stones[k];
                    normal_weapons[i]->upgrade();
                    cout<<"Normal weapon "<<normal_weapons[i]->get_name()<<"+"<<normal_weapons[i]->get_level()-1<<" was upgraded to "<<normal_weapons[i]->get_name()<<"+"<<normal_weapons[i]->get_level()<<"."<<endl;
                }
                if(uptime==1){
                    normal_smithing_stones[j]->add_amount(-2);
                    substract(j,0,2);
                    if(!normal_smithing_stones[j]->greater_equal(1))    delete normal_smithing_stones[j];
                    normal_weapons[i]->upgrade();
                    if(normal_weapons[i]->get_level()==0){
                        cout<<"Normal weapon "<<normal_weapons[i]->get_name()<<" was upgraded to "<<normal_weapons[i]->get_name()<<"+1."<<endl;
                    }
                    else{
                        cout<<"Normal weapon "<<normal_weapons[i]->get_name()<<"+"<<normal_weapons[i]->get_level()-1<<" was upgraded to "<<normal_weapons[i]->get_name()<<"+"<<normal_weapons[i]->get_level()<<"."<<endl;
                    }
                }   
                else if(uptime==2){
                    normal_smithing_stones[j]->add_amount(-2);
                    substract(j,0,2);
                    if(!normal_smithing_stones[j]->greater_equal(1))    delete normal_smithing_stones[j];
                    normal_weapons[i]->upgrade();
                    if(normal_weapons[i]->get_level()==0){
                        cout<<"Normal weapon "<<normal_weapons[i]->get_name()<<" was upgraded to "<<normal_weapons[i]->get_name()<<"+1."<<endl;
                    }
                    else{
                        cout<<"Normal weapon "<<normal_weapons[i]->get_name()<<"+"<<normal_weapons[i]->get_level()-1<<" was upgraded to "<<normal_weapons[i]->get_name()<<"+"<<normal_weapons[i]->get_level()<<"."<<endl;
                    }
                    normal_smithing_stones[j]->add_amount(-4);
                    substract(j,0,4);
                    if(!normal_smithing_stones[j]->greater_equal(1))    delete normal_smithing_stones[j];
                    normal_weapons[i]->upgrade();
                    cout<<"Normal weapon "<<normal_weapons[i]->get_name()<<"+"<<normal_weapons[i]->get_level()-1<<" was upgraded to "<<normal_weapons[i]->get_name()<<"+"<<normal_weapons[i]->get_level()<<"."<<endl;
                }  
                else if(uptime==3){
                    normal_smithing_stones[j]->add_amount(-2);
                    substract(j,0,2);
                    if(!normal_smithing_stones[j]->greater_equal(1))    delete normal_smithing_stones[j];
                    normal_weapons[i]->upgrade();
                    if(normal_weapons[i]->get_level()==0){
                        cout<<"Normal weapon "<<normal_weapons[i]->get_name()<<" was upgraded to "<<normal_weapons[i]->get_name()<<"+1."<<endl;
                    }
                    else{
                        cout<<"Normal weapon "<<normal_weapons[i]->get_name()<<"+"<<normal_weapons[i]->get_level()-1<<" was upgraded to "<<normal_weapons[i]->get_name()<<"+"<<normal_weapons[i]->get_level()<<"."<<endl;
                    }
                    normal_smithing_stones[j]->add_amount(-4);
                    substract(j,0,4);
                    if(!normal_smithing_stones[j]->greater_equal(1))    delete normal_smithing_stones[j];
                    normal_weapons[i]->upgrade();
                    cout<<"Normal weapon "<<normal_weapons[i]->get_name()<<"+"<<normal_weapons[i]->get_level()-1<<" was upgraded to "<<normal_weapons[i]->get_name()<<"+"<<normal_weapons[i]->get_level()<<"."<<endl;
                    normal_smithing_stones[j]->add_amount(-6);
                    substract(j,0,6);
                    if(!normal_smithing_stones[j]->greater_equal(1))    delete normal_smithing_stones[j];
                    normal_weapons[i]->upgrade();
                    cout<<"Normal weapon "<<normal_weapons[i]->get_name()<<"+"<<normal_weapons[i]->get_level()-1<<" was upgraded to "<<normal_weapons[i]->get_name()<<"+"<<normal_weapons[i]->get_level()<<"."<<endl;
                }
                cout<<"Upgrade "<<normal_weapons[i]->get_name();
                if(initlevel==0)    cout<<" to "<<normal_weapons[i]->get_name()<<"+"<<normal_weapons[i]->get_level()<<" Successfully."<<endl;
                else    cout<<"+"<<initlevel<<" to "<<normal_weapons[i]->get_name()<<"+"<<normal_weapons[i]->get_level()<<" Successfully."<<endl;
                break;
            }
        }
    }
    if(!check_exist){
        for(int i=0;i<somber_weapon_number;++i){
            if(somber_weapons[i]&&somber_weapons[i]->get_name()==name){
                if(target<=somber_weapons[i]->get_level()){
                    cout<<"Stay calm!"<<endl;
                    break;
                }
                check_exist=true;
                bool check_stone=false;
                int stone_level=(target/3)+1;
                int now_target=target;
                int j=1;
                int uptime=0;
                for(;j<=stone_level;++j){
                    if(now_target==1){
                        if(somber_smithing_stones[j]&&somber_smithing_stones[j]->greater_equal(2)){
                            check_stone=true;
                        }
                        break;
                    }
                    else if(now_target==2){
                        if(somber_smithing_stones[j]&&somber_smithing_stones[j]->greater_equal(4)){
                            check_stone=true;
                        }
                        break;
                    }
                    else if(now_target>=3){
                        if(somber_smithing_stones[j]&&somber_smithing_stones[j]->greater_equal(6)&&now_target==3){
                            check_stone=true;
                            break;
                        }
                        else if(!somber_smithing_stones[j]||!somber_smithing_stones[j]->greater_equal(6)){
                            break;
                        }
                        else{
                            now_target-=3;
                        }
                    }
                }
                if(!check_stone){
                    upgrade_failed(j,1);
                    break;
                }
                else{
                int initlevel=somber_weapons[i]->get_level();
                for(int k=1;k<j;++k){
                    somber_smithing_stones[k]->add_amount(-2);
                    substract(k,1,2);
                    somber_weapons[i]->upgrade();
                    if(somber_weapons[i]->get_level()==1){
                        cout<<"Somber weapon "<<somber_weapons[i]->get_name()<<" was upgraded to "<<somber_weapons[i]->get_name()<<"+1."<<endl;
                    }
                    else{
                        cout<<"Somber weapon "<<somber_weapons[i]->get_name()<<"+"<<somber_weapons[i]->get_level()-1<<" was upgraded to "<<somber_weapons[i]->get_name()<<"+"<<somber_weapons[i]->get_level()<<"."<<endl;
                    }
                    //cout<<"Somber weapon "<<somber_weapons[i]->get_name()<<"was upgraded to "<<somber_weapons[i]->get_name()
                    somber_smithing_stones[k]->add_amount(-4);
                    substract(k,1,4);
                    somber_weapons[i]->upgrade();
                    cout<<"Somber weapon "<<somber_weapons[i]->get_name()<<"+"<<somber_weapons[i]->get_level()-1<<" was upgraded to "<<somber_weapons[i]->get_name()<<"+"<<somber_weapons[i]->get_level()<<"."<<endl;
                    somber_smithing_stones[k]->add_amount(-6);
                    substract(k,1,6);
                    if(!somber_smithing_stones[k]->greater_equal(1))    delete somber_smithing_stones[k];
                    somber_weapons[i]->upgrade();
                    cout<<"Somber weapon "<<somber_weapons[i]->get_name()<<"+"<<somber_weapons[i]->get_level()-1<<" was upgraded to "<<somber_weapons[i]->get_name()<<"+"<<somber_weapons[i]->get_level()<<"."<<endl;
                }
                if(uptime==1){
                    somber_smithing_stones[j]->add_amount(-2);
                    substract(j,1,2);
                    if(!somber_smithing_stones[j]->greater_equal(1))    delete somber_smithing_stones[j];
                    somber_weapons[i]->upgrade();
                    if(somber_weapons[i]->get_level()==0){
                        cout<<"Somber weapon "<<somber_weapons[i]->get_name()<<" was upgraded to "<<somber_weapons[i]->get_name()<<"+1."<<endl;
                    }
                    else{
                        cout<<"Somber weapon "<<somber_weapons[i]->get_name()<<"+"<<somber_weapons[i]->get_level()-1<<" was upgraded to "<<somber_weapons[i]->get_name()<<"+"<<somber_weapons[i]->get_level()<<"."<<endl;
                    }
                }   
                else if(uptime==2){
                    somber_smithing_stones[j]->add_amount(-2);
                    substract(j,1,2);
                    if(!somber_smithing_stones[j]->greater_equal(1))    delete somber_smithing_stones[j];
                    somber_weapons[i]->upgrade();
                    if(somber_weapons[i]->get_level()==0){
                        cout<<"Somber weapon "<<somber_weapons[i]->get_name()<<" was upgraded to "<<somber_weapons[i]->get_name()<<"+1."<<endl;
                    }
                    else{
                        cout<<"Somber weapon "<<somber_weapons[i]->get_name()<<"+"<<somber_weapons[i]->get_level()-1<<" was upgraded to "<<somber_weapons[i]->get_name()<<"+"<<somber_weapons[i]->get_level()<<"."<<endl;
                    }
                    somber_smithing_stones[j]->add_amount(-4);
                    substract(j,1,4);
                    if(!somber_smithing_stones[j]->greater_equal(1))    delete somber_smithing_stones[j];
                    somber_weapons[i]->upgrade();
                    cout<<"Somber weapon "<<somber_weapons[i]->get_name()<<"+"<<somber_weapons[i]->get_level()-1<<" was upgraded to "<<somber_weapons[i]->get_name()<<"+"<<somber_weapons[i]->get_level()<<"."<<endl;
                }  
                else if(uptime==3){
                    somber_smithing_stones[j]->add_amount(-2);
                    substract(j,1,2);
                    if(!somber_smithing_stones[j]->greater_equal(1))    delete somber_smithing_stones[j];
                    somber_weapons[i]->upgrade();
                    if(somber_weapons[i]->get_level()==0){
                        cout<<"Somber weapon "<<somber_weapons[i]->get_name()<<"was upgraded to "<<somber_weapons[i]->get_name()<<"+1."<<endl;
                    }
                    else{
                        cout<<"Somber weapon "<<somber_weapons[i]->get_name()<<"+"<<somber_weapons[i]->get_level()-1<<" was upgraded to "<<somber_weapons[i]->get_name()<<"+"<<somber_weapons[i]->get_level()<<"."<<endl;
                    }
                    somber_smithing_stones[j]->add_amount(-4);
                    substract(j,1,4);
                    if(!somber_smithing_stones[j]->greater_equal(1))    delete somber_smithing_stones[j];
                    somber_weapons[i]->upgrade();
                    cout<<"Somber weapon "<<somber_weapons[i]->get_name()<<"+"<<somber_weapons[i]->get_level()-1<<" was upgraded to "<<somber_weapons[i]->get_name()<<"+"<<somber_weapons[i]->get_level()<<"."<<endl;
                    somber_smithing_stones[j]->add_amount(-6);
                    substract(j,1,6);
                    if(!somber_smithing_stones[j]->greater_equal(1))    delete somber_smithing_stones[j];
                    somber_weapons[i]->upgrade();
                    cout<<"Somber weapon "<<somber_weapons[i]->get_name()<<"+"<<somber_weapons[i]->get_level()-1<<" was upgraded to "<<somber_weapons[i]->get_name()<<"+"<<somber_weapons[i]->get_level()<<"."<<endl;
                }
                cout<<"Upgrade "<<somber_weapons[i]->get_name();
                if(initlevel==0)    cout<<" to "<<somber_weapons[i]->get_name()<<"+"<<somber_weapons[i]->get_level()<<" Successfully."<<endl;
                else    cout<<"+"<<initlevel<<" to "<<somber_weapons[i]->get_name()<<"+"<<somber_weapons[i]->get_level()<<" Successfully."<<endl;
                break;
            }
            }
        }
    }
    if(!check_exist){
        cout<<"You don't have the right!"<<endl;
    }
}