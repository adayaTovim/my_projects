#include <ostream>
#include <iostream>
#include <fstream>

#include "color_image.hpp"
#include "matrix.hpp"
#include "color_rgb.hpp"

namespace advcpp{

ColorImage::ColorImage(size_t a_rows, size_t a_columns, unsigned int a_saturation)
: m_saturation(a_saturation)
, m_imageMatrix(Matrix<Color>(a_rows, a_columns))
{
}

ColorImage::ColorImage(const ColorImage& a_other)
: m_saturation(a_other.m_saturation)
, m_imageMatrix(a_other.m_imageMatrix)
{
}

ColorImage& ColorImage::operator=(ColorImage const& a_other) {
    if (this != &a_other) {
        m_saturation = a_other.m_saturation;
        m_imageMatrix = a_other.m_imageMatrix;
    }
    return *this;
}


Color& ColorImage::At(size_t a_row, size_t a_column){
    return m_imageMatrix(a_row, a_column);
}

Color const& ColorImage::At(size_t a_row, size_t a_column) const{
    return m_imageMatrix(a_row, a_column);
}

void ColorImage::Write(Color const& a_color,size_t a_column, size_t a_row){
    m_imageMatrix(a_row, a_column) = a_color;
}

size_t ColorImage::Column() const{
    return m_imageMatrix.GetColumns();
}

size_t ColorImage::Row() const{
    return m_imageMatrix.GetRows();
}

unsigned int ColorImage::Saturation() const{
    return m_saturation;
}

void ColorImage::Clear(Color const& backgroundColor){
    for (unsigned int i = 0; i < m_imageMatrix.GetRows(); ++i) {
        for (unsigned int j = 0; j < m_imageMatrix.GetColumns(); ++j) {
	        m_imageMatrix(i,j) = backgroundColor;
        }
    }
}

ColorImage LoadImageFromFile(std::string const& a_filename){
    std::ifstream file(a_filename);
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    // Read image format (first line)
    std::string format;
    file >> format;

    // Read image dimensions (second line)
    size_t columns, rows;
    file >> columns >> rows;

    // Read saturation value (third line)
    unsigned int saturation;
    file >> saturation;

    // Create matrix with appropriate dimensions
    ColorImage image(rows, columns, saturation);

    // Read pixel values from file and store in matrix
    for (size_t i = 0; i < rows; ++i) {  
        for (size_t j = 0; j < columns; ++j) {
            size_t red, green, blue;
            file >> red >> green >> blue;
            image.Write(Color(red, green, blue), j, i);
        }
    }
    file.close();
    return image;
}

void SaveImageToFile(std::string const& a_filename, ColorImage const& a_image){
    std::ofstream file(a_filename);
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    size_t columns = a_image.Column();
    size_t rows = a_image.Row();

    // Write the format, saturation, width, and height to the file
    file << "P3" << std::endl;
    file << columns << " " << rows << std::endl;
    file << a_image.Saturation() << std::endl;

    // Write the Color data to the file
    for (size_t i = 0; i < rows ; ++i){
        for (size_t j = 0; j < columns; ++j){
            file <<  a_image.At(i,j).m_red << " " << a_image.At(i,j).m_green << " " << a_image.At(i,j).m_blue << " ";
        }
        file << "\n"; 
    }
    file.close();
}

} // advcpp