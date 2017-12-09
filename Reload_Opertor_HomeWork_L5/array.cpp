#include "array.h"
using namespace std;
Array::Array(int sizeArr)
{
    sizeArray = sizeArr;
    dataArray = new int[sizeArray];
    cout << "constructor of array   ====>  " << this <<
            "  size of array is "<< sizeArray  << endl;
    if (sizeArray != 0) {
        // initializing all element by 0
        for (int i = 0; i < sizeArray; ++i) {
            dataArray[i] = 0;
        }
        cout <<  "All element of Array is 0 " << endl;
    }
}

Array::Array(const Array & dArr)
{
    cout << "copy constructor  ====>  " << this << endl;
    sizeArray = dArr.sizeArray;
    dataArray = new int[sizeArray];
    for (int i = 0; i < sizeArray; ++i) {
        dataArray[i] = dArr.dataArray[i];
    }
}

Array::~Array()
{
    cout << "destructor !!!!    ====>  " << this << endl;
    delete [] dataArray;
}

int Array::getSize()
{
    //cout << "This metod return size of array " << sizeArray << " " << endl;
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

Array & Array::operator+(const int x)
{

    cout << " We in operator + "<< endl;
    for (int i = 0; i < sizeArray; ++i) {
        dataArray[i] = dataArray[i]+x;
        cout << "+";
    }
    return *this;
}

Array Array::operator+(const Array &dArr)
{
    Array Temp(*this);
    cout << " We in operator Arr+Arr "<< endl;
    delete [] dataArray;
    int firstArr = Temp.sizeArray;
    int secondArr = dArr.sizeArray;
    sizeArray = firstArr + secondArr;
    dataArray = new int[firstArr+secondArr];
    for (int i = 0; i < firstArr; ++i) {
        dataArray[i] = Temp.dataArray[i];
        cout << "+";
    }
     cout << endl;
    for (int i = 0; i < secondArr; ++i) {
        dataArray[i+firstArr] = dArr.dataArray[i];
        cout << "+";
    }
    cout << endl;
    return *this;
}

template <class T>
void SwopT(T * pThis,const T & dArr){
    char sBuff[sizeof(T)];
    T Temp(dArr);
    memcpy(sBuff,pThis,sizeof(T));
    memcpy(pThis,&Temp,sizeof(T));
    memcpy(&Temp,sBuff,sizeof(T));
}


Array & Array::operator=(const Array &dArr)
{
    if (this != &dArr) {

        // написать шаблонную функцию
//        char sBuff[sizeof(Array)];
//        Array Temp(dArr);
//        memcpy(sBuff,this,sizeof(Array));
//        memcpy(this,&Temp,sizeof(Array));
//        memcpy(&Temp,sBuff,sizeof(Array));
SwopT(this, dArr);

        cout << " reload operator = " << endl;
//        delete[] dataArray;
//        sizeArray = dArr.sizeArray;
//        dataArray = new int[sizeArray];
//        for (int i = 0; i < sizeArray; i++) {
//            dataArray[i] = dArr.dataArray[i];
//        }
    }
    else {
        cout << " self reloading " << endl;
    }
    return *this;
}
