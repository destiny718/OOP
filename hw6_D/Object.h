#pragma once
#include <list>
#include <iostream>
#include <memory>
#include "CustomClass.h"
using namespace std;

class Object;

class Content{
public:
	virtual void output(){ //virtual function for output
		cout << "the operator is not supported for this type." << std::endl;
	}
	virtual void operator+=(const int& other){};
	virtual void operator+=(const string& other){};
	virtual void operator+=(Content src){};
};

class IntContent: public Content{
private:
	int x;
public:
	IntContent(int _x): x(_x) {}
	void output(){ //???
		cout << x;
	}
	void operator+=(const int& other){
		x+=other;
	}
};
class StringContent: public Content
{
private:
	string x;
public:
	StringContent(std::string _x): x(_x) {}
	void output(){  //???
		cout << x;
	}
	void operator+=(const string& other){
		x+=other;
	}
};
// The following codes are not working
class VectorContent: public Content{
private:
	vector<Object> x; //Object is not defined???
public:
	VectorContent(const std::vector<Object>& _x): x(_x) {}
	void operator+=(Content src){
		std::vector<Object> tmp = dynamic_cast<VectorContent&>(src).x;
		for(Object& i:tmp){
			x.push_back(i);
		}
	}
	Object& operator[](int flag){
		return x[flag];
	}
};

class CustomContent: public Content{
private:
	CustomClass x;
public:
	CustomContent(const CustomClass& _x): x(_x) {}
};

class Object{
private:
	shared_ptr<Content> pt;

public:
	Object() {}
	Object(int x) {
		pt = make_shared<IntContent>(x); // where to delete? maybe use std::shared_ptr?
	}
	Object(const string &x){
		pt = make_shared<StringContent>(x);
	}
	//The following codes are not working
	Object(const std::vector<Object> &x){
		pt = make_shared<VectorContent>(x);
	}
	Object(const CustomClass &x){
		pt = make_shared<CustomContent>(x);
	}

	friend std::ostream& operator<<(std::ostream& out, const Object& obj) {
		obj.pt->output();
		return out;
	}

	Object& operator+=(int y){
		pt->operator+=(y);
		return *this;
	}
	Object& operator+=(const string &y){
		pt->operator+=(y);
		return *this;
	}
	Object& operator[](int flag){
		Content* ptr=pt.get();
		if (dynamic_cast<VectorContent*>(ptr) != nullptr) {
			return dynamic_cast<VectorContent*>(ptr)->operator[](flag);
		}
		Object tmp(1);
		return tmp;
	}
	//need more operators......
};
//honor code:https://github.com/Ashitemaru/OOPHomework/blob/master/UOJ_64/Object.h
//代码内的注释可以忽略，源于题目自带。
//关于这种解法的highlight:
//				Content* ptr=pt.get();用于获得存储的指针
//				通过两次重载[]来实现对于vector<Object>的输出.

//============================================================================================

//可以在Object类中增加一个vector<Object>*的成员（也要用shared_ptr）,专门用于处理vector<Object>，然后删去VectorContent类。
//似乎这样也可以处理多次vector<Object>嵌套的情况，能AC.
//在声明时Object(const std::vector<Object> &x)删掉就行。
//~~搞出来了让人不适的无限嵌套~~