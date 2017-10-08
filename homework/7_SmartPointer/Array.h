#ifndef ARRAY_H
#define ARRAY_H
class Array
{
    int m_nSize, m_iCurIndex;
    int * m_pArr;
    void addMemory();//private function for realocation
public:
     Array(int nSize);                                    //constructor with obyazatelniy parameter
     Array(int ** ppArr,const unsigned int nSize);        //constructor, that get dynamic array
     Array(int * pArr, const unsigned int nSize);         //constructor, that get array on stack

     Array(const Array & Right);                          //copy constructor Right - any word explicit only copying
     Array& operator=(const Array &Right);                //assgnment operator

     Array operator+(const Array & Right);                //operator+ for concatenation arrays
     Array operator+(const int nNumber);                  //operator+ for adding nNumber to all array elements

     ~Array();                                            //destructor

     void show();                                         //show array
     void push_back(int a);                               //add element into tail of array






};
#endif // ARRAY_H
