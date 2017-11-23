// somefunc.h
#ifndef _SOMEFUNC_
#define _SOMEFUNC_

#ifdef __cplusplus
extern "C" {
#endif

class BaseA;
BaseA * GetFactory(char * sCatName, int * pLength);
int Mult(int a, int b);
//int ctest1(int * pAr, int nSize);
//void ctest2(int a, int b);
//  @AHMultAH?A

#ifdef __cplusplus
}
#endif

#endif
