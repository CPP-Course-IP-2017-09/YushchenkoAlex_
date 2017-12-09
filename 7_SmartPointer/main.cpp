#include <iostream>
#include "SmartPointer.hpp"
#include "Array.h"

#define ARRAY_SIZE 10

using namespace std;

#define SIZE 100

int main()
{
//creating first object
    Array * a = new Array(ARRAY_SIZE);
//creating first group of smart pointers
    SmartPointer<Array>sp_a(a);          //constructor call
    SmartPointer<Array>sp_a_1(sp_a);     //copy constructor call
    SmartPointer<Array>sp_a_2;           //assignment operator call
    sp_a_2 = sp_a_1;

//operator->()
    for(int i=0;i<ARRAY_SIZE;++i)
        sp_a->push_back(i);              // equal to sp_a.operator->()->push_back(i);

    sp_a->show();                        // equal to sp_a.operator->()->show();

    cout<<endl;

//creating second object
    Array * b = new Array(ARRAY_SIZE);
//creating first group of smart pointers
    SmartPointer<Array>sp_b(b);          //constructor call
    SmartPointer<Array>sp_b_1(sp_b);     //copy constructor call
    SmartPointer<Array>sp_b_2;           //assignment operator call
    sp_b_2 = sp_b_1;

//operator->()
    for(int i=0;i<ARRAY_SIZE;++i)
        sp_b->push_back(i+10);           // equal to sp_a.operator->()->push_back(i);

    sp_b->show();                        // equal to sp_a.operator->()->show();

    cout<<endl;

    return 0;
}
