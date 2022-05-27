#pragma once
#include"smithing_stone.h"
using namespace std;

class SomberSmithingStone: public SmithingStone{
public:
    using SmithingStone::greater_equal;
    using SmithingStone::add_amount;
    SomberSmithingStone(int level):SmithingStone(level){
        cout<<"Somber smithing stone "<<get_level()<<" was created."<<endl;
    }
    void Add_number(int number){
        add_amount(number);
        cout<<"Somber smithing stone "<< get_level()<<" was added with "<<number<<"."<<endl;
    }
    ~SomberSmithingStone(){
        cout<<"Somber smithing stone "<<get_level()<<" was destroyed."<<endl;
    }
};