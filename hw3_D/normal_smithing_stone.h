#pragma once
#include"smithing_stone.h"
using namespace std;

class NormalSmithingStone: public SmithingStone{
public:
    using SmithingStone::greater_equal;
    using SmithingStone::add_amount;
    NormalSmithingStone(int _level):SmithingStone(_level){
        cout << "Normal smithing stone " << get_level() << " was created." << endl;
    }
    void Add_number(int number){
        add_amount(number);
        cout<<"Normal smithing stone "<< get_level()<<" was added with "<<number<<"."<<endl;
    }
    ~NormalSmithingStone(){
        cout<<"Normal smithing stone "<<get_level()<<" was destroyed."<<endl;
    };
};