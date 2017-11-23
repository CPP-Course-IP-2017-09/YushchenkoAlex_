
#include "A10.h"
#include <iostream>
using namespace std;

A10::A10(int a):m_a(a)
{
	cout<<"A10(int a) "<<this<<' '<<m_a<<endl;
}
A10::~A10()
{
	cout<<"~A10() "<<this<<' '<<m_a<<endl;
}

int A10::Mult(int a, int b)
{
	return a * b * m_a;
}
void A10::Destroy()
{
	delete this;
}
