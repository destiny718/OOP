#include"Vector.h"
using namespace std;

Vector::Vector(int n){
    capacity=n;
    len=0;
    array=new Node[n];
}

Vector::~Vector(){
    len=0;
    delete[] array;
}

Vector::Vector(const Vector& other):array(new Node[other.capacity]){
    this->capacity=other.capacity;
    this->len=other.len;
    for(int i=0;i<len;++i){
        array[i]=other.array[i];
    }
}

Vector::Vector(Vector&& other):array(other.array){
    this->capacity=other.capacity;
    this->len=other.len;
    /*for(int i=0;i<len;++i){
        array[i]=other.array[i];
    }*/
    this->array=other.array;
    other.array=nullptr;
}

Vector & Vector::operator=(const Vector & other){
    if(this!=&other){
        this->capacity=other.capacity;
        this->len=other.len;
        if(array)   delete[] array;
        //array=new Node(*other.array);
        array=new Node[other.capacity];
        for(int i=0;i<len;++i){
            array[i]=other.array[i];
        }
    }
    return *this;
}

Vector & Vector::operator=(Vector && other){
    if(this!=&other){
        this->capacity=other.capacity;
        this->len=other.len;
        if(array)   delete[] array;
        this->array=other.array;
        other.len=0;
        other.array=nullptr;
    }
    return *this;
}

Node& Vector::operator[](int pos){
    return this->array[pos];
}

void Vector::append(int value){
    array[len++]=move(value);
}

void Vector::insert(int pos,int value){
    for(int i=len;i>pos;--i){
        array[i]=move(array[i-1]);
    }
    array[pos]=move(value);
    len++;
}

void Vector::swap(int pos1,int pos2){
    Node tmp(move(array[pos1]));
    array[pos1]=move(array[pos2]);
    array[pos2]=move(tmp);
}

void Vector::dilatation(){
    capacity*=2;
    Vector tem_double(capacity);
    tem_double.len=len;
    for(int i=0;i<len;++i){
        tem_double.array[i]=move(array[i]);
    }
    delete[] array;
    array=tem_double.array;
    tem_double.array=nullptr;
}

int Vector::getlen(){
    return this->len;
}