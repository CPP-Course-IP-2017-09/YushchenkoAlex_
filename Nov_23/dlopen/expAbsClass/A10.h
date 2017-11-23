#ifndef _A10_
#define _A10_

#include "BaseA.h"

class A10 : public BaseA
{
	int m_a;
public:
	A10(int a);
	~A10();

	virtual int Mult(int a, int b); 
	virtual void Destroy();
};

#endif //A10
