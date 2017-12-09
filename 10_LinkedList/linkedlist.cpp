#include "linkedlist.h"
#include <iostream>
using namespace std;


LinkedList::LinkedList():mpBeg(0),mpEnd(0)
{
    cout << "New LinkedList-object at " << this << endl;
}

LinkedList::~LinkedList()
{
    Node *pCur=mpBeg;
    Node *pBuf;
    while (pCur!=0)
    {
        pBuf = pCur->mpNext;
        delete pCur;
        pCur = pBuf;

    }
    cout << "Deleting LinkedList-object at " << this << endl;
}

LinkedList::Node::Node(int a):ma(a), mpNext(0)
{
}

void LinkedList::push_back(int a)
{
    Node *pTemp=new Node(a);
    if (mpBeg==0)
        mpBeg=mpEnd=pTemp;
    else
    {
        mpEnd->mpNext=pTemp;
        mpEnd=pTemp;
    }
}

void LinkedList::Show()
{
    Node *pCur=mpBeg;
    while (pCur!=0)
    {
        cout << pCur->ma << endl;
        pCur=pCur->mpNext;
    }
}
