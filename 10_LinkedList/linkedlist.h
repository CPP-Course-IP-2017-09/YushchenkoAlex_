#ifndef LINKEDLIST_H
#define LINKEDLIST_H


class LinkedList
{
    struct Node
    {
        int ma;
        Node *mpNext;
        Node(int a);
    };
    Node *mpBeg;
    Node *mpEnd;

public:
    LinkedList();
    ~LinkedList();

    void push_back(int a);
    void Show();
};

#endif // LINKEDLIST_H
