#include "Array.h"
#include <iostream>
#include <iomanip>
#include <memory.h>

template <class T> //class vs typename because we expect class data structure only for readability
void CopyObject(const T & Right, T * pThis)
{
    char sBuff [sizeof(T)];
    T Temp(Right);
    memcpy(sBuff,pThis, sizeof(T));
    memcpy(pThis,&Temp,sizeof(T));
    memcpy(&Temp,sBuff,sizeof(T));
}

Array::Array(int nSize):m_nSize(nSize), m_iCurIndex(0), m_pArr(0) //constructor with initialization of parameters
{
    if(nSize<=0) m_nSize = 0;
    else         m_pArr = new int [m_nSize];

    //diagnostic
    std::cout<<"Array(int)"<<this<<" "<<m_nSize<<std::endl;
}
Array::Array(int ** ppArr,const unsigned int nSize):m_nSize(nSize),m_pArr( * ppArr),m_iCurIndex(0) //constructor, that get dynamic array
{
    *ppArr = NULL; //if we take resources, we must set pointer to ZERO

    //diagnostic
    std::cout<<"Array "<<this<<" (int **ppArr, const unsigned int nSize)"<<std::endl;
}
Array::Array(int * pArr, const unsigned int nSize):m_nSize(nSize),m_pArr(0),m_iCurIndex(0) //constructor, that array on stack
{
    if(nSize<=0) m_nSize = 0;
    else
    {
        m_pArr = new int [m_nSize]; //creating dymamic array
        memcpy(m_pArr,pArr,nSize*sizeof(int));//copy array from stack inside object
        m_iCurIndex = m_nSize;
    }

    //diagnostic
    std::cout<<"Array "<<this<<" (int * pArr, const unsigned int nSize)"<<std::endl;
}
Array::~Array() //destructor
{
    delete [] m_pArr;
    std::cout<<"~Array(int)"<<this<<" "<<m_nSize<<std::endl;
}

Array::Array(const Array & Right): m_nSize(Right.m_nSize), m_iCurIndex(Right.m_iCurIndex), m_pArr(0) //copy constructor Right - any word
{
    if(Right.m_pArr != 0) //if previous pointer not null
    {
        m_pArr = new int [m_nSize];
        memcpy(m_pArr,Right.m_pArr,sizeof(int)*m_iCurIndex);
    }
    std::cout<<"Array copy constructor "<<this<<" from"<<&Right<<" "<<m_nSize<<" elements"<<std::endl;
}
void Array::show()
{
    std::cout<<"void Array::show() "<<this<<std::endl;
    for(int i=0;i<m_iCurIndex;++i)
        {
            std::cout<<std::setw(5)<<"A["<<i<<"]:"<<m_pArr[i]<<"\t";
        }
    std::cout<<std::endl;
}
void Array::addMemory() //private function for realocation
{

    if(m_iCurIndex == m_nSize)
        {
          m_nSize *= 2;
          int * pTemp = new int [m_nSize];
          memcpy(pTemp,m_pArr,m_nSize/2*sizeof(int));
          delete [] m_pArr;
          m_pArr = pTemp;
        }

    //dynamic memory algorithm realocation
    //dyagnostic old size, new size
}
void Array::push_back(int a)
{
    if(m_iCurIndex == m_nSize) addMemory();
    m_pArr[m_iCurIndex] = a;
    m_iCurIndex++;
}
Array Array::operator+(const Array & Right)
{
    Array TempArray(this->m_iCurIndex+Right.m_iCurIndex);   //creating temporary object, that will be consist of two arrays
                                                              //2 - because index less size by 1
    memcpy(TempArray.m_pArr,this->m_pArr,(this->m_iCurIndex+1)*sizeof(int));                   //copy first array to big array
    memcpy(TempArray.m_pArr+this->m_iCurIndex,Right.m_pArr,(Right.m_iCurIndex+1)*sizeof(int)); //copy second array to big array

    TempArray.m_nSize = this->m_iCurIndex + Right.m_iCurIndex;   //calculating new m_nSize
    TempArray.m_iCurIndex = this->m_iCurIndex + Right.m_iCurIndex; //calculating new m_iCurIndex

    //diagnostic
    std::cout<<"Array(int)("<<this<<") operator+ new size:["<<m_nSize<<"]"<<std::endl;

    return TempArray;
}
Array Array::operator+(const int nNumber)
{
    Array TempArray(this->m_nSize); //creating temporary array

    memcpy(TempArray.m_pArr,this->m_pArr,this->m_iCurIndex*sizeof(int));  //copy first array to second array
    TempArray.m_iCurIndex = this->m_iCurIndex;                            //equaling indexes of both arrays

    for(int i=0;i<TempArray.m_iCurIndex;++i)
    {
        TempArray.m_pArr[i] = TempArray.m_pArr[i] + nNumber;              //adding nNumber to array
    }

    //diagnostic
    std::cout<<"Array(int)("<<this<<")"<<"operator+("<<nNumber<<")"<<std::endl;

    return TempArray;
}
Array& Array::operator=(const Array &Right)
{
    if(this !=&Right)
    {
        CopyObject(Right, this);
    }
    return *this;
}
