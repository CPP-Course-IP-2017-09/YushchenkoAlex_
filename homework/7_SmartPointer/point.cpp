#include <iostream>
#include "point.h"


Point::Point(int x, int y):m_x(x),m_y(y)
{
    std::cout<<"Point("<<this<<"):x = "<<m_x<<";y = "<<m_y<<std::endl;
}

Point::~Point()
{
    std::cout<<"~Point("<<this<<"):x = "<<m_x<<";y = "<<m_y<<std::endl;
}

int Point::get_x()
{
    return m_x;
}

int Point::get_y()
{
    return m_y;
}

void Point::set_x(const int x)
{
    m_x = x;
}
void Point::set_y(const int y)
{
    m_y = y;
}
