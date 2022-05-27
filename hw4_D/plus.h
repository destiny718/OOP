#include"graph.h"
using namespace std;

class Plus:public OperationNodeTwo{
public:
    Plus(string name, Node* x1, Node* x2):OperationNodeTwo(name,x1,x2){};
    void UpdateValue() override{
        value_=input1->value()+input2->value();
    };
    ~Plus(){};
};