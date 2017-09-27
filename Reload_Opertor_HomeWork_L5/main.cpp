#include <iostream>
#include "array.h"
using namespace std;

int main()
{
    Array iArray_1(10);
    cout << iArray_1.ShowTheSize() << endl;
    //iArray_1.ShowTheArray();
    iArray_1.fillArrayRand();
    iArray_1.ShowTheArray();
    iArray_1 = iArray_1+10;
    iArray_1.ShowTheArray();




    cout << "Hello World!" << endl;
    return 0;
}
