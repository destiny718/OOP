#pragma once

#include<vector>
#include"animal.h"

using namespace std;

void action(Animal* animal, std::vector<Dog> & dogzone, std::vector<Bird> & birdzone){
    Dog* tmp=dynamic_cast<Dog*>(animal);
    if(tmp!=nullptr){
        dogzone.push_back(move(*tmp));
    }
    else{
        Bird* tmp=dynamic_cast<Bird*>(animal);
        birdzone.push_back(move(*tmp));
    }
}
