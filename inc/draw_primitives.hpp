
#ifndef DRAW_PRIMITIVES_H_203
#define DRAW_PRIMITIVES_H_203

#include "color_image.hpp"
#include "matrix.hpp"
#include "color_rgb.hpp"
#include "point.hpp"

namespace advcpp{

void DrawLine(ColorImage& a_image, const Color& a_color, const Point& a_start, const Point& a_end);
void DrawHorizontalLine(ColorImage& a_image, size_t a_startX, size_t a_endX, size_t a_y, Color const& a_color);
void DrawVerticalLine(ColorImage& a_image, size_t a_startY, size_t a_endY, size_t a_x, Color const& a_color);
void DrawLineAlgorithm(ColorImage& a_image, const Color& a_color, const Point& a_start, const Point& a_end);
bool IsPointInImage(ColorImage& a_image, int a_x, int a_y);
void DrawCircle(ColorImage& a_image, const Color& a_color, const Point& a_center, size_t a_radius);

} // advcpp

#endif //DRAW_PRIMITIVES_H_203
