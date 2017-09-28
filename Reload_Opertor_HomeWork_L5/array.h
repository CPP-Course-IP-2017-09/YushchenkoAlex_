#ifndef ARRAY_H
#define ARRAY_H
#include <iostream>

class Array
{
    int * dataArray; //pointer to array
    int sizeArray; // size of array
public:
    Array(int sizeArray = 0); // constructor
    Array(Array & dArr); // copy constructor
    ~Array();
    int getSize();
    void ShowTheArray();
    void fillArrayRand();

    // reload the operator + where if 'our class + int' whill for each element add a int
    Array &operator+(const int x);
    Array operator+(const Array &dArr);
    Array operator=(const Array &dArr);
};

#endif // ARRAY_H
