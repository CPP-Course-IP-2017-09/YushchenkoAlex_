#include "server.h"
#include "A10.h"
#include <stdlib.h>
#include <memory.h>


extern "C" int Mult(int a, int b)
{
    return a * b;
}

extern "C" BaseA * GetFactory(char * sCatName, int * pLength)
{
	int nCetNameLen = sizeof("Flowers");
	int nMin = nCetNameLen;
	if(*pLength < nCetNameLen)
		nMin = *pLength;
	memcpy(sCatName, "Flowers", nCetNameLen);
	*pLength = nMin;

	return new A10(nMin);
}
