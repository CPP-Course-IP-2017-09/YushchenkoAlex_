#include <iostream>
#include <pthread.h>
#include "getUnsignedInt.h"
#include "ArrayFunctions.h"

void * ThreadFunc(void * pV);

struct ArrayInfo
{
  unsigned int m_nMultiplier;  //multiplier, which array elements will be multiply inside ThFunc
  unsigned int m_nArraySize;   //array Size
           int * m_pArray;     //pointer to array
};

int main()
{
    unsigned int nArraySize    = getUnsignedInt(1,100000,"Get array size:","Error, ");
    unsigned int nThreadsCount = getUnsignedInt(1,11,"Get threads count:","Error, ");

    int Array[nArraySize];                                   //creating array in stack
    ArrayFunctions::iArrayFilling(&Array[0],nArraySize, 1);  //array fill

    ArrayInfo *pArrayInfo[nThreadsCount];  //creating array of pointers to ArrayInfo
    pthread_t id[nThreadsCount];           //array of id for thread
    void * pV[nThreadsCount];              //creating void * array


    //show current array
    ArrayFunctions::iArrayShow(&Array[0],nArraySize,2,' ');
    std::cout<<std::endl;

    ////creating ArrayInfo struct object for each thread
    for(int i=0;i<nThreadsCount;++i)
    {
        pArrayInfo[i] =  new ArrayInfo;
        pArrayInfo[i]->m_nMultiplier = i+2;
        pArrayInfo[i]->m_nArraySize = nArraySize;
        pArrayInfo[i]->m_pArray = &Array[0];
    }

    //creating and join threads
    for(int i=0;i<nThreadsCount;++i)
    {
        //creating and join threads series
        pthread_create(&id[i],0,ThreadFunc,(void *)pArrayInfo[i]);

        //series view
        pthread_join(id[i],&pV[i]);
    }

    //haos view
    //for(int i=0;i<nThreadsCount;++i)
       //pthread_join(id[i],&pV[i]);



    return 0;
}

void * ThreadFunc(void * pV)
{
    //converting void pointer to pointer to ArrayInfo struct
    ArrayInfo * pArrayInfo = (ArrayInfo *)pV;

    //multiply and show array

    std::cout<<"ArraySize:"<<pArrayInfo->m_nArraySize<<std::endl;

    for(int i=0;i<pArrayInfo->m_nArraySize;++i)
        std::cout<<((pArrayInfo->m_pArray[i]) * (pArrayInfo->m_nMultiplier));

    std::cout<<std::endl;

    //delete ArrayInfo struct object for thread
    delete pV;

    //diagnostic
   std::cout<<"Diagnostic";
}
