#include"graph.h"
using namespace std;

class Minus:public OperationNodeTwo{
public:
    Minus(string name, Node* x1, Node* x2):OperationNodeTwo(name,x1,x2){};
    void UpdateValue() override{
        value_=input1->value()-input2->value();
    };
    ~Minus(){};
};