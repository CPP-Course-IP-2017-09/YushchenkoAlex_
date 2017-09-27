#include "array.h"
using namespace std;
Array::Array(int sizeArr)
{
    sizeArray = sizeArr;
    dataArray = new int[sizeArray];
    cout << "constructor of array " << this <<
            "  size of array is "<< sizeArray  << endl;
    if (sizeArray != 0) {
        // initializing all element by 0
        for (int i = 0; i < sizeArray; ++i) {
            dataArray[i] = 0;
        }
        cout <<  "All element of Array is 0 " << endl;
    }
}

Array::Array(Array & dArr)
{
    cout << "copy constructor  " << endl;
    sizeArray = dArr.ShowTheSize();
    dataArray = new int[sizeArray];
    for (int i = 0; i < sizeArray; i++) {
        dataArray[i] = dArr.dataArray[i];
    }
}

Array::~Array()
{
    cout << "destructor !!!!" << this << "this is spartaaaaaa )))" << endl;
    //delete [] dataArray;


}

int Array::ShowTheSize()
{
    cout << "This metod return size of array " << sizeArray << " " << endl;
    return sizeArray;
}

void Array::ShowTheArray()
{
    if (sizeArray == 0) {
        cout<< "Array is empty!!!" << endl;
    } else {
        // show all element of array
        cout << "start of array" << endl;
        for (int i = 0; i < sizeArray; ++i) {
            cout << dataArray[i] << endl;
        }
        cout << "end of array" << endl;
    }
}

void Array::fillArrayRand()
{
    if (sizeArray == 0) {
        cout<< "Array is empty!!! Filling is not possible" << endl;
    } else {
        // initializing all element by rand()
        for (int i = 0; i < sizeArray; ++i) {
            dataArray[i] = rand()%10;
        }
    }
}

Array Array::operator+(int x)
{
    Array Temp(*this);
    cout << "We in operator + "<< endl;
    for (int i = 0; i < sizeArray; ++i) {
        Temp.dataArray[i] = Temp.dataArray[i]+x;
        cout << "+";
    }
    cout << endl;
    return Temp;
}
