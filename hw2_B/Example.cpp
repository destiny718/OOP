#include <iostream>
#include "Example.h"

using namespace std;

	// (2)
Example::Example(int data) {
	// (3)
	num=data+3;
	if(data!=3)
		cout<<"Example #"<<num<<" is"<<" created"<<endl;
	if(data==0||data==1||data==2){
		wor=data;
	}
	else if(data==-2){
		wor=23;
	}
	else if(data==-1){
		wor=233;
	}
	else if(data==3){
		wor=2333;
	}
	else if(data==4){
		wor=23333;
	}

}

void Example::getData() {
	// (4)
	cout<<"The data of Example #"<<num<<" is "<<wor<<endl;
}

Example::~Example() {
	// (5)
	cout<<"Example #"<<num<<" is"<<" destroyed"<<endl;
}