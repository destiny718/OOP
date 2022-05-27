#include <iostream>

using namespace std;

class Test {
    int *buf;
public:
    Test() {
        buf = new int(0);
        cout << "Test(): this->buf @ " << hex << buf << endl;
    }
    Test(int val) {
        buf = new int(val);
        cout << "Test(int): this->buf @ " << hex << buf << endl;
    }
    ~Test() {
        cout << "~Test(): this->buf @ " << hex<<"&&" << buf << endl;
        if (buf){
            cout<<" "<<buf<<endl;
            delete buf; 
        }
    }
    Test(const Test& t) : buf(new int(*t.buf)) {
        cout << "Test(const Test&) called. this->buf @ "
            << hex << buf << endl;
    }
    Test(Test&& t) : buf(t.buf) {
        cout << "Test(Test&&) called. this->buf @ "
            << hex << buf << endl;
        t.buf = nullptr;
    }
    Test& operator= (const Test& right) {
        if (this != &right){
            if(buf) delete buf;
            buf = new int(*right.buf);
            cout<<"const Test& ="<<endl;
        }
        return *this;
    }
    Test& operator= (Test&& right) {
        if (this != &right){
            if(buf) delete buf;
            this->buf = right.buf;
            right.buf = nullptr;
            cout<<"Test&& ="<<endl;
        }
        return *this;
    }
    void print(const char *name) {
        cout << name << ".buf @ " << hex << buf << endl;
    }
};

// E
/*const Test& F(const Test& a){
    Test b = a;
    return Test(1);
}
int main() {
    Test a;
    const Test &A = F(std::move(a));
    return 0;
}*/

// C
/*Test F(Test &&a){
    Test b = std::move(a);
    return b;
}
int main(){
    Test A = F(1);
    return 0;
}*/

// B
Test F(const Test& a){
    Test b = std::move(a);
    return b;
}
int main(){
    Test A = F(1);
    return 0;
}