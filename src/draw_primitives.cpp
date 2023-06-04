
#include <algorithm> // swap

#include "draw_primitives.hpp"


namespace advcpp {

void DrawLine(ColorImage& a_image, const Color& a_color, const Point& a_start, const Point& a_end){

    // horizontal line
    if (a_start.m_yAxis == a_end.m_yAxis){
        DrawHorizontalLine(a_image, a_start.m_xAxis, a_end.m_xAxis, a_start.m_yAxis, a_color);
    }
    // vertical line
    else if (a_start.m_xAxis == a_end.m_xAxis){
        DrawVerticalLine(a_image, a_start.m_yAxis, a_end.m_yAxis, a_start.m_xAxis, a_color);
    }
    else{
        DrawLineAlgorithm(a_image, a_color, a_start, a_end);
    }
}

void DrawHorizontalLine(ColorImage& a_image, size_t a_startX, size_t a_endX, size_t a_y, Color const& a_color){
    if (a_startX > a_endX) {
        std::swap(a_startX, a_endX);
    }
    for (size_t x = a_startX; x <= a_endX; ++x){
        if(IsPointInImage(a_image, x, a_y)){
        a_image.Write(a_color, x, a_y);
        }
    }
}

void DrawVerticalLine(ColorImage& a_image, size_t a_startY, size_t a_endY, size_t a_x, Color const& a_color){
    if (a_startY > a_endY) {
        std::swap(a_startY, a_endY);
    }
    for (size_t y = a_startY; y <= a_endY; ++y){
        if(IsPointInImage(a_image, a_x, y)){
        a_image.Write(a_color, a_x, y);
        }
    }
}

void DrawLineAlgorithm(ColorImage& a_image, const Color& a_color, const Point& a_start, const Point& a_end){

    int x0 = a_start.m_xAxis;
    int x1 = a_end.m_xAxis;
    int y0 = a_start.m_yAxis;
    int y1 = a_end.m_yAxis;

    int dx = x1 - x0;
    int dy = y1 - y0;

    // Check if the points are the same
    if (x0 == x1 && y0 == y1) {
        a_image.Write(a_color, x0, y0);
        return;
    }

    if (x1 < x0) {
        std::swap(x0, x1);
    }

    //diff - the difference between points
    int diff = 2 * dy - dx;
    int y = y0;

    for(int x = x0; x < x1; x++){
        if(IsPointInImage(a_image, x, y)){
            a_image.Write(a_color, x, y);
            if(diff > 0){
                y = y + 1;
                diff = diff - 2 * dx;
            }
            else{
                diff = diff + 2 * dy;
            }
        }
    }
}

void DrawCircle(ColorImage& a_image, const Color& a_color, const Point& a_center, size_t a_radius) {

    int xLocation = a_radius;
    int radiusError = 1 - xLocation;
    
    size_t x = a_center.m_xAxis;
    size_t y = a_center.m_yAxis;

    for(int yLocation = 0;  xLocation >= yLocation; ++yLocation) {
        if(IsPointInImage(a_image, y + yLocation, x - xLocation)){
            a_image.Write(a_color, y + yLocation, x - xLocation);
        }
        if(IsPointInImage(a_image, y - yLocation, x - xLocation)){
            a_image.Write(a_color, y - yLocation, x - xLocation);
        }
        if(IsPointInImage(a_image, y + xLocation, x - yLocation)){
            a_image.Write(a_color, y + xLocation, x - yLocation);
        }
        if(IsPointInImage(a_image, y - xLocation, x - yLocation)){
            a_image.Write(a_color, y - xLocation, x - yLocation);
        }
        if(IsPointInImage(a_image, y + yLocation, x + xLocation)){
            a_image.Write(a_color, y + yLocation, x + xLocation);
        }
        if(IsPointInImage(a_image, y - yLocation, x + xLocation)){
            a_image.Write(a_color, y - yLocation, x + xLocation);
        }
        if(IsPointInImage(a_image, y + xLocation, x + yLocation)){
            a_image.Write(a_color, y + xLocation, x + yLocation);
        }
        if(IsPointInImage(a_image, y - xLocation, x + yLocation)){
            a_image.Write(a_color, y - xLocation, x + yLocation);
        }
        if (radiusError < 0){
            radiusError += 2 * yLocation + 1;
        }
        else{
            --xLocation;
            radiusError += 2 * (yLocation - xLocation) + 1;
        }
    }
}

bool IsPointInImage(ColorImage& a_image, int a_x, int a_y){
    if(a_x < 0 || a_y < 0){
        return false;
    }
    if(a_x >= static_cast<int>(a_image.Column()) && a_y >= static_cast<int>(a_image.Row())){
        return false;
    }
    return true;
}


} // namespace advcpp
