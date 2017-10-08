#include <iostream>
#include "line.h"

Line::Line(const int Ax, const int Ay, const int Bx, const int By):m_A(Ax,Ay),m_B(Bx,By)   //constructor
{
    std::cout<<"Line("<<this<<"):Ax = "<<m_A.get_x()<<"; Ay = "<<m_A.get_y()<<"; Bx = "<<m_B.get_x()<<"; By = "<<m_B.get_y()<<std::endl;
}
Line::~Line() //destructor
{
    std::cout<<"~Line("<<this<<")"<<std::endl;
}

bool Line::isParallelTo(Line & Right)        //check if this is parallel to Right
{
    //getting cotangens of this line
    double ctg_this  = double(m_B.get_x() - m_A.get_x()) / double(m_B.get_y() - m_A.get_y());

    //getting cotangens of Right line
    double ctg_Right = double(Right.m_B.get_x() - Right.m_A.get_x()) / double(Right.m_B.get_y() - Right.m_A.get_y());

    if(ctg_this == ctg_Right)
        return true;
    else
        return false;
}
void Line::setParallelTo(Line & Right, const int x_shift, const int y_shift) //make parallel to Right with shift
{
    this->m_A.set_x(Right.m_A.get_x()+x_shift);
    this->m_A.set_y(Right.m_A.get_y()+y_shift);
    this->m_B.set_x(Right.m_B.get_x()+x_shift);
    this->m_B.set_y(Right.m_B.get_y()+y_shift);
}
