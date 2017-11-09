#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include "ArrayFunctions.h"

namespace ArrayFunctions
{
  //array filling
  void iArrayRandFilling(int *pArr,const int SIZE, int iDivider)
  {
    static bool isFirstCall = true;

    //prevent reusing same rand sequence
    if(isFirstCall)
      srand((unsigned int)time(0));
    
    isFirstCall = false;
    
    for(int i=0;i<SIZE;++i)
      {
	pArr[i] = rand()%iDivider;
      }
  }
  //pseudo-random array filling
  void iArrayFilling(int *pArr,const int SIZE, int iValue)
  {
    for(int i=0;i<SIZE;++i)
      {
	pArr[i] = iValue;
      }
  }
  
  void iArrayBubbleSort (int *pArr,const int SIZE, int order)
  {
    int nTemp; //temporary variable
    
    if (order==0)
      return; //no sorting
    else if
      (order>0)
      {
	//ascending order
	for(int i=0;i<SIZE-1;++i)
	  for(int j=0;j<SIZE-1;++j)
	    if(pArr[j] > pArr[j+1])
	      {
		nTemp = pArr[j+1];
		pArr[j+1] = pArr[j];
		pArr[j] = nTemp;
	      }
      }
    else
      {
	//descending order
	for(int i=0;i<SIZE-1;++i)
	  for(int j=0;j<SIZE-1;++j)
	    if(pArr[j] < pArr[j+1])
	      {
		nTemp = pArr[j+1];
		pArr[j+1] = pArr[j];
		pArr[j] = nTemp;
	      }
      }
  }

  void iArrayOptimizedBubbleSort (int *pArr,const int SIZE, int order)
{
  int nTemp; //temporary variable

  if (order==0)
    return; //no sorting
  else if
    (order>0)
    {
  //ascending order
  for(int i=0;i<SIZE-1;++i)
    for(int j=0;j<SIZE-1-i;++j)
      if(pArr[j] > pArr[j+1])
        {
          nTemp = pArr[j+1];
          pArr[j+1] = pArr[j];
          pArr[j] = nTemp;
        }
    }
  else
    {
  //descending order
  for(int i=0;i<SIZE-1;++i)
    for(int j=0;j<SIZE-1-i;++j)
      if(pArr[j] < pArr[j+1])
        {
      nTemp = pArr[j+1];
      pArr[j+1] = pArr[j];
      pArr[j] = nTemp;
        }
    }
}

void iArraySelectionSort(int * pArr,const int SIZE)
{
  int nMin;
  int iMinIndex;
  for(int i=0;i<SIZE;++i)
    {
      nMin = pArr[i];
      iMinIndex = i;
      for(int j = i+1;j < SIZE;++j)
        {
          if(pArr[j] < pArr[iMinIndex]) //ascending //if(pArr[j] < pArr[iMinIndex]) //descending
            {
              iMinIndex = j;
            }
        }
      pArr[i] = pArr[iMinIndex];
      pArr[iMinIndex] = nMin;
    }
}

int iArrayBinarySeacrh(int nKey,int * pArr,unsigned int iMax,unsigned int iMin)
{
  unsigned int iMiddle = ( iMax + iMin ) / 2;

  if(iMin + 1 == iMax)
    {

      if(nKey == pArr[iMax])
        return iMax;
      else if(nKey == pArr[iMin])
        return iMin;
      else
        return -1;
    }
  else if (nKey == pArr[iMiddle])
    return iMiddle;

  else if(nKey <= pArr[iMiddle])
    return iArrayBinarySeacrh(nKey,pArr,iMiddle,iMin);

  else if(nKey >= pArr[iMiddle])
    return iArrayBinarySeacrh(nKey,pArr,iMax,iMiddle);

}  
  
  void iArrayShow(const int *pArr,const int SIZE,int iSymbolWidth,char cSpaceSymbol)
  {
    for(int i=0;i<SIZE;++i)
      {
	std::cout<<std::setw(iSymbolWidth)<<pArr[i]<<cSpaceSymbol;
      }
  }


}


