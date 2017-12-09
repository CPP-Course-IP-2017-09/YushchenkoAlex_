// serverVS.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "serverVS.h"
#include <iostream>


// This is an example of an exported variable
SERVERVS_API int nserverVS=0;

// This is an example of an exported function.
SERVERVS_API int fnserverVS(void)
{
    return 42;
}

// This is the constructor of a class that has been exported.
// see serverVS.h for the class definition
CserverVS::CserverVS()
{
    return;
}
// -lmath
extern "C" SERVERVS_API int Mult(int a, int b)
{
	std::cout << "FRom dll =========== " << std::endl;
	return a * b;
}
