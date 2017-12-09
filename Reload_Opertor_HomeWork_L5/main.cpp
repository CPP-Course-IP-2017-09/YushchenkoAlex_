#include <iostream>
#include "array.h"
using namespace std;

int main()
{
    Array iArray_1(5);
    iArray_1.fillArrayRand();
    iArray_1.ShowTheArray();

    Array iArray_2(10);
    iArray_2.fillArrayRand();
    iArray_2+20;
    iArray_2.ShowTheArray();

    Array iArray_3;
    iArray_3 = iArray_1+iArray_2 + iArray_1;
    iArray_3.ShowTheArray();

    return 0;
}
