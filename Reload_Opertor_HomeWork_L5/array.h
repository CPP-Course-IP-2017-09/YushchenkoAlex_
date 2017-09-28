#ifndef ARRAY_H
#define ARRAY_H
#include <iostream>

class Array
{
    int * dataArray;
    int sizeArray;
public:
    Array(int sizeArray = 0); // constructor
    Array(Array & dArr); // copy constructor
    ~Array();
    int ShowTheSize();
    void ShowTheArray();
    void fillArrayRand();

    // reload the operator + where if 'our class + int' whill for each element add a int
    Array operator+(int x);
    Array operator=(const Array & dArr);
};

#endif // ARRAY_H
