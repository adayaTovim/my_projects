#ifndef COLOR_IMAGE_H_203
#define COLOR_IMAGE_H_203

#include <memory>

#include "matrix.hpp"
#include "color_rgb.hpp"

namespace advcpp{

class ColorImage{
public:
    explicit ColorImage(size_t a_rows, size_t a_columns, unsigned int a_saturation = 255);
    ColorImage(const ColorImage& a_other);
    ColorImage& operator = (ColorImage const& a_other);
    ~ColorImage() = default;
  
    Color& At(size_t a_row, size_t a_column);
    Color const& At(size_t a_row, size_t a_column) const;
    void Write(Color const& a_color,size_t a_column, size_t a_row);
	
    size_t Row() const;
	size_t Column() const;
	unsigned int Saturation() const;
    
    void Clear(Color const& backgroundColor);
    
private:
    unsigned int m_saturation;   
    Matrix<Color> m_imageMatrix;
};

ColorImage LoadImageFromFile(std::string const& a_filename);
void SaveImageToFile(std::string const& a_filename, ColorImage const& a_image);

} // advcpp

#endif //COLOR_IMAGE_H_203


