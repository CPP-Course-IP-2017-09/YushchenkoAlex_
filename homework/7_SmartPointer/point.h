#ifndef POINT_H
#define POINT_H


class Point
{
    int m_x;
    int m_y;
public:
    Point(int x, int y);  //constructor
   ~Point(); //destructor


    int get_x();
    int get_y();

    void set_x(const int x);
    void set_y(const int y);
};

#endif // POINT_H
