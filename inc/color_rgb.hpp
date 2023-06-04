#ifndef COLOR_RGB_H_
#define COLOR_RGB_H_

static const int RGB_DEFAULT = 255;

namespace advcpp{
struct Color {
    Color();    
    explicit Color(size_t a_red, size_t a_green, size_t a_blue);
    
    Color(const Color& a_other) = default;
    Color& operator = (const Color& a_other) = default;
    ~Color() = default;

    //void PrintColor() const;

    size_t m_red;
    size_t m_green;
    size_t m_blue;
};


inline Color::Color(size_t a_red, size_t a_green, size_t a_blue)
: m_red(a_red)
, m_green(a_green)
, m_blue(a_blue)
{
}

inline Color::Color()
: m_red(RGB_DEFAULT)
, m_green(RGB_DEFAULT)
, m_blue(RGB_DEFAULT)
{
}

} //sdvcpp

#endif //PIXEL_H_