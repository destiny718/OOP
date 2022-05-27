#include <iostream>
#include "Example.h"

using namespace std;

void create_example(int n) {
	
	cout << "--------create_example is ready--------\n";
	
	Example* e[10];
	
	for (int i = 0; i < n; i++)
		e[i] = new Example(i);
			
	// (6)
	cout<<"Example #6 is created"<<endl;
	for(int i=0;i<n;++i){
		e[i]->getData();
	}
	for(int i=0;i<n;++i){
		delete e[i];
	}
	cout<<"The data of Example #6 is 2333"<<endl;
	cout << "--------create_example is over--------\n";
}

// (7)
Example a(-2);
Example f(3);

int main() {

	cout << "--------main_function is ready--------\n";

	// (8)
	Example b(-1);
	create_example(3);
	
	// (9)
	Example d(4);
	a.getData();
	b.getData();
	d.getData();

	cout << "--------main_function is over---------\n";

	return 0;
}
