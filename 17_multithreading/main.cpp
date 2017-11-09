#include <iostream>
#include <pthread.h>
#include <memory.h>
#include "getUnsignedInt.h"
#include "ArrayFunctions.h"

void * ThreadFunc(void * pV);

struct ArrayInfo
{
  unsigned int      m_nMultiplier;  //multiplier, which Array elements will be multiply inside ThFunc
  unsigned int      m_nArraySize;   //Array Size
           int    * m_pArray;       //pointer to Array
  pthread_mutex_t * m_pMutex;       //pointer to mutex
  unsigned int    * m_piIndex;      //pointer to index
};

int main()
{
    std::cout<<"Test"<<std::endl;

    unsigned int nArraySize    = getUnsignedInt(1,10000000,"Get Array size:","Error, ");
    unsigned int nThreadsCount = getUnsignedInt(1,1000,"Get threads count:","Error, ");
    unsigned int iIndex        = 0;

    if(nArraySize < nThreadsCount)
        nArraySize = nThreadsCount;

    int *  pArray = new int[nArraySize];                                   //creating Array in heap
    ArrayFunctions::iArrayFilling(pArray,nArraySize, 1);                   //Array fill

    ArrayInfo ** pArrayInfo = new ArrayInfo * [nThreadsCount];  //creating Array of pointers to ArrayInfo
    pthread_t * id = new pthread_t[nThreadsCount];            //Array of id for thread
    void ** pV = new void *[nThreadsCount];                 //creating void * Array

    //create mutex for Array
    pthread_mutex_t ArrayMutex;             //mutex declaration
    pthread_mutex_init(&ArrayMutex,0);      //mutex initialization


    ////creating ArrayInfo struct object for each thread
    for(int i=0;i<nThreadsCount;++i)
    {
        pArrayInfo[i] =  new ArrayInfo;
        pArrayInfo[i]->m_nMultiplier = i+2;
        pArrayInfo[i]->m_nArraySize = nArraySize;
        pArrayInfo[i]->m_pArray = pArray;
        pArrayInfo[i]->m_pMutex = &ArrayMutex;
        pArrayInfo[i]->m_piIndex = &iIndex;
    }


        //creating and join threads
        for(int i=0;i<nThreadsCount;++i)
        {
            //creating and join threads series
            pthread_create(&(id[i]),0,ThreadFunc,(void *)pArrayInfo[i]);

            //series view
            //pthread_join(id[i],&pV[i]);
        }

        //non-haos view
        for(int i=0;i<nThreadsCount;++i)
           pthread_join(id[i],&pV[i]);

        //delete mutex
        pthread_mutex_destroy(&ArrayMutex);


    //array show
    std::cout<<std::endl;
    for(int i=0;i<nArraySize;++i)
    {
        std::cout<<pArray[i]<<" ";
    }
    std::cout<<std::endl;

    delete [] pArray;

    delete [] pArrayInfo ;                                  //delete Array of pointers to ArrayInfo
    delete [] id;                                           //delete Array of id for threads
    delete [] pV;                                           //delete void * Array

    return 0;
}

void * ThreadFunc(void * pV)
{
    //converting void pointer to pointer to pArrayInfo struct
    ArrayInfo * pArrayInfo = (ArrayInfo *)pV;

    //multiply and show Array

    //std::cout<<std::endl<<"ArraySize:"<<pArrayInfo->m_nArraySize<<std::endl;

    unsigned int iIndex = 0;

    while(true)
    {
        pthread_mutex_lock(pArrayInfo->m_pMutex);     //lock mutex
        iIndex = (*(pArrayInfo->m_piIndex))++;        //get and ++ index
        pthread_mutex_unlock(pArrayInfo->m_pMutex);
        //unlock mutex

        if(iIndex < pArrayInfo->m_nArraySize)
            pArrayInfo->m_pArray[iIndex] = pArrayInfo->m_pArray[iIndex] * pArrayInfo->m_nMultiplier;
        else
            break;
    }

    //std::cout<<std::endl;

    //delete ArrayInfo struct object for thread
    delete pArrayInfo;

    //diagnostic
    //std::cout<<"Diagnostic"<<std::endl;
}
