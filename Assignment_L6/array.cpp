#include "array.h"

Array::Array(int x)
{
    A = x;
    cout << "i am constructor "<< this << " A = " << A << endl;
}
Array::~Array(){
    cout<< "destructor " << endl;
}

void Array::Show()
{
    cout << "I am Show function" << endl;
}
