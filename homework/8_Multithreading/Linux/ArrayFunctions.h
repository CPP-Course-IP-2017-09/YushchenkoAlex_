#ifndef ARRAY_FUNCTIONS_H
#define ARRAY_FUNCTIONS_H

namespace ArrayFunctions
{
  //array filling
  void iArrayRandFilling(int *pArr,const int SIZE, int iDivider);
  
  //pseudo-random array filling
  void iArrayFilling(int *pArr,const int SIZE, int iValue);

  //bubble sort, order = 0 no sort, <0 descending, >0 ascending
  void iArrayBubbleSort (int *pArr,const int SIZE, int order);

  //optimized bibble sort, order = 0 no sort, < 0 descending, > 0 ascending
  void iArrayOptimizedBubbleSort (int *pArr,const int SIZE, int order);

  //ascending selection sort
  void iArraySelectionSort(int * pArr,const int SIZE);
  
  //array show
  void iArrayShow(const int *pArr,const int SIZE,int iSymbolWidth,char cSpaceSymbol);

  //binary search returns element index if element is equal to nKey, or -1 if nKey not founded in array
  int iArrayBinarySeacrh(int nKey, int * pArr, unsigned int iMax, unsigned int iMin = 0);
}


#endif
