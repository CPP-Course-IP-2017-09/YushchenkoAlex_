#ifndef LINE_H
#define LINE_H
#include "point.h"


class Line
{
    Point m_A;
    Point m_B;

public:
    Line(const int Ax, const int Ay, const int Bx, const int By);           //constructor
    ~Line();  //destructor
    bool isParallelTo(Line & Right);                                        //check if this paralel to Right
    void setParallelTo(Line & Right, const int x_shift=0, const int y_shift=0); //make parallel to Right with shift
};

#endif // LINE_H
