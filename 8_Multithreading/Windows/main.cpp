#include <iostream>
#include <windows.h>

#include "ArrayFunctions.h"

#define DEFAULT_VALUE 10

DWORD WINAPI ThreadFunc(CONST LPVOID parameter);

struct ArrayInfo
{
  unsigned int m_nMultiplier;  //multiplier, which array elements will be multiply inside ThFunc
  unsigned int m_nArraySize;   //array Size
           int * m_pArray;     //pointer to array
};

int main()
{
    unsigned int nArraySize;    std::cout<<"Enter array size: ";    std::cin>>nArraySize;
    unsigned int nThreadsCount; std::cout<<"Enter threads count: "; std::cin>>nThreadsCount;

    if(nThreadsCount > 10 || nThreadsCount <1)
        nThreadsCount = DEFAULT_VALUE;

    if(nArraySize > 100 || nArraySize <1)
        nArraySize = DEFAULT_VALUE;

    int Array[nArraySize];                                   //creating array in stack
    ArrayFunctions::iArrayFilling(&Array[0],nArraySize, 1);  //array fill

    ArrayInfo *pArrayInfo[nThreadsCount];  //creating array of pointers to ArrayInfo
    HANDLE hHandle[nThreadsCount];         //array of id for threads
//    void * pV[nThreadsCount];              //creating void * array

    //show current array
    ArrayFunctions::iArrayShow(&Array[0],nArraySize,2,' ');
    std::cout<<std::endl;

    //creating ArrayInfo struct object for each thread
    for(int i=0;i<nThreadsCount;++i)
    {
        pArrayInfo[i] =  new ArrayInfo;
        pArrayInfo[i]->m_nMultiplier = i+2;
        pArrayInfo[i]->m_nArraySize = nArraySize;
        pArrayInfo[i]->m_pArray = &Array[0];

    }

    //creating and join threads series
    for(int i=0;i<nThreadsCount;++i)
    {
        //creating and join threads series
        hHandle[i] = CreateThread(NULL,0,ThreadFunc,pArrayInfo[i],0,NULL);

//        //series view
//        WaitForSingleObject(hHandle[i],INFINITE);
    }

    //haos view
    for(int i=0;i<nThreadsCount;++i)
        WaitForSingleObject(hHandle[i],INFINITE);

    return 0;
}


DWORD WINAPI ThreadFunc(CONST LPVOID parameter)
{
    //converting void pointer to pointer to ArrayInfo struct
    ArrayInfo * pArrayInfo = (ArrayInfo *)parameter;

    //multiply and show array
    std::cout<<"ArraySize:"<<pArrayInfo->m_nArraySize<<std::endl;

    for(int i=0;i<pArrayInfo->m_nArraySize;++i)
        std::cout<<((pArrayInfo->m_pArray[i]) * (pArrayInfo->m_nMultiplier));

    std::cout<<std::endl;

    //delete ArrayInfo struct object for thread

    delete pArrayInfo;

    //diagnostic
       std::cout<<"Diagnostic";

    ExitThread(0);
}
