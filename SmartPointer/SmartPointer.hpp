#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include <iostream>
template <typename T>
class SmartPointer
{
    T            * m_pPointer;         //pointer that store allocated memory address
    unsigned int * m_pnPointersCounter; //variable, that store # of SmartPointer allocated for the same memory
public:

    SmartPointer(T * p_Pointer):m_pPointer(NULL),m_pnPointersCounter(NULL) //constructor
    {
        m_pPointer = p_Pointer;                    //pointer assert
        m_pnPointersCounter = new unsigned int;    //creating counter
        *this->m_pnPointersCounter = 1;            //counter initialization

        //diagnostic
        std::cout<<"SmartPointer(void * p_Pointer) ["<<this<<"] "<<"( for type:"<<sizeof(T)<<" bytes)"<<std::endl;
        std::cout<<" \t this->m_pPointer:"<<this->m_pPointer<<std::endl;
        std::cout<<" \t this->m_pnPointersCounter:"<<this->m_pnPointersCounter<<std::endl;
        std::cout<<" \t counter:"<<*this->m_pnPointersCounter<<std::endl;
    }

    SmartPointer():m_pPointer(NULL),m_pnPointersCounter(NULL) //constructor
    {
        m_pnPointersCounter = new unsigned int;    //creating counter
        *m_pnPointersCounter = 1;                  //counter initialization

        //diagnostic
        std::cout<<"SmartPointer(void * p_Pointer) ["<<this<<"] "<<"( for type:"<<sizeof(T)<<" bytes)"<<std::endl;
        std::cout<<" \t this->m_pPointer:"<<this->m_pPointer<<std::endl;
        std::cout<<" \t this->m_pnPointersCounter:"<<this->m_pnPointersCounter<<std::endl;
        std::cout<<" \t counter:"<<*this->m_pnPointersCounter<<std::endl;
    }
    SmartPointer(const SmartPointer & Right):m_pPointer(NULL)    //copy constructor
    {
        if(Right.m_pPointer != NULL)
        {
            this->m_pPointer = Right.m_pPointer;                   //pointers copy
            this->m_pnPointersCounter = Right.m_pnPointersCounter; //counters copy

            (*this->m_pnPointersCounter)++;                        //counter increment

        }

        //diagnostic
        std::cout<<"Copy constr SmartPointer(SmartPointer & Right) ["<<this<<"] ( for type: "<<sizeof(T)<<" bytes) "<<*(this->m_pnPointersCounter)<<" smart pointer is present"<<std::endl;
        std::cout<<" \t this->m_pPointer:"<<this->m_pPointer<<" Right.m_pPointer:"<<Right.m_pPointer<<std::endl;
        std::cout<<" \t this->m_pnPointersCounter:"<<this->m_pnPointersCounter<<" Right.m_pnPointersCounter:"<<Right.m_pnPointersCounter<<std::endl;
        std::cout<<" \t *(this->m_pnPointersCounter):"<<*this->m_pnPointersCounter<<" *(Right.m_pnPointersCounter): "<<*Right.m_pnPointersCounter<<std::endl;
    }

    SmartPointer& operator=(const SmartPointer &Right)
    {
        if(this != &Right)  //if we not to try a=a;
        {

            std::cout<<"----------------------------------------"<<std::endl;
            std::cout<<"This != RIGHT"<<std::endl;

            if(this->m_pPointer != NULL) //if smart pointer is not empty
            {
                std::cout<<"this->m_pPointer != NULL"<<std::endl;

                if(*(this->m_pnPointersCounter) == 1) //smart pointer one for allocated memory
                 {

                    std::cout<<"*(this)->m_pnPointersCounter == 1"<<std::endl;

                     delete this->m_pPointer;          //memory free
                     delete this->m_pnPointersCounter; //counter free
                 }
             }
            else  //need to delete m_pnPointersCouunter
            {
                delete [] this->m_pnPointersCounter;

                std::cout<<"Delete empty m_pnPointersCounter"<<std::endl;

            }

            std::cout<<"Assignment"<<std::endl;

            this->m_pPointer = Right.m_pPointer;                   //pointer handoff
            this->m_pnPointersCounter = Right.m_pnPointersCounter; //counter handoff
            (*this->m_pnPointersCounter)++;                        //counter increment

         }

        //diagnostic
        std::cout<<"SmartPointer& operator= [ "<<this<<" ](const SmartPointer ["<<&Right<<"] ) "<<*(this->m_pnPointersCounter)<<" smart pointers left"<<std::endl;
        std::cout<<" \t this->m_pPointer:"<<this->m_pPointer<<" Right.m_pPointer:"<<Right.m_pPointer<<std::endl;
        std::cout<<" \t this->m_pnPointersCounter:"<<this->m_pnPointersCounter<<" Right.m_pnPointersCounter:"<<Right.m_pnPointersCounter<<std::endl;
        std::cout<<" \t *(this->m_pnPointersCounter):"<<*this->m_pnPointersCounter<<" *(Right.m_pnPointersCounter): "<<*Right.m_pnPointersCounter<<std::endl;

        return *this;
    }

    T * operator->()
    {
        return m_pPointer;
    }


    ~SmartPointer()//destructor
    {
        //diagnostic
        std::cout<<"~SmartPointer() ["<<this<<"] "<<std::endl;

        if((*(this->m_pnPointersCounter)) > 1)        //if pointers greater than 1
            {
                (*this->m_pnPointersCounter)--;     //counter decrement

                //diagnostic
                std::cout<<"\t"<<*this->m_pnPointersCounter<<" smart pointers left"<<std::endl;
            }
        else if(*(this->m_pnPointersCounter) == 1 && m_pPointer != NULL)         //if call destructor of last SmartPointer that store pointer to same memory need delete memory and counter
            {
                delete this->m_pPointer;          //free memory cathed by SmartPointer
                delete this->m_pnPointersCounter; //free memory, allocated for counter

                //diagnostic
                std::cout<<" \t Last smart pointer, memory free"<<std::endl;
            }
    }
};

#endif // SMARTPOINTER_H
