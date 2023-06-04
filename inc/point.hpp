#ifndef POINT_H_203
#define POINT_H_203

#include <iostream>

static const int DEFAULT_AXIS = 0;

namespace advcpp {
    
struct Point {
    explicit Point();                                                           
    explicit Point(unsigned int a_xAxis, unsigned int a_yAxis) ;

    Point(const Point &a_other) = default ;                                    
    Point& operator=(const Point &a_other) = default ;                          
    ~Point() = default;                                                      

    int m_xAxis;
    int m_yAxis;
};

 inline Point::Point(unsigned int a_xAxis, unsigned int a_yAxis) 
 : m_xAxis(a_xAxis)
 , m_yAxis(a_yAxis)
 {}

inline Point::Point() 
 : m_xAxis(DEFAULT_AXIS)
 , m_yAxis(DEFAULT_AXIS) 
 {}

} //advcpp


#endif //POINT_H_203