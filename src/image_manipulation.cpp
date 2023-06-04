#include <SFML/Graphics.hpp>
#include <thread>
#include <cmath>

#include "image_manipulation.hpp"

namespace advcpp {

void joinAll(std::vector<std::thread>& a_threads) 
{
    for(auto& t : a_threads) {
        t.join();
    }
}

sf::Color convertGray(sf::Color& a_color)
{
    float avg = (a_color.r + a_color.g + a_color.b)/3;
    a_color.r = avg;
    a_color.g = avg;
    a_color.b = avg;

    return a_color;
}

sf::Color reduceBlue(sf::Color& a_color)
{
    a_color.b /= 2;;
    
    return a_color;
}

sf::Color reduceColor(sf::Color& a_color)
{
    a_color.r /= 2;
    a_color.g /= 2;
    a_color.b /= 2;

    return a_color;
}


sf::Color gaussianBlur(const sf::Image & a_image, unsigned int x, unsigned int y, const std::vector<float>& a_kernel)
{
    unsigned int kernelSize = a_kernel.size();

    float r = 0.f;
    float g = 0.f;
    float b = 0.f;
    float kernelSum = 0.0f;
    unsigned int kernelIndex = 0;
    unsigned int sq = std::sqrt(kernelSize);
    unsigned int offset = (sq - 1) / 2;

    //int halfSize = static_cast<int>(kernelSize / 2);
    for (unsigned int i = 0; i < sq; ++i) {
        for (unsigned int j = 0; j < sq; ++j) {
            int k = x + i - offset;
            int l = y + j - offset;
            if (k >= 0 && k < static_cast<int>(a_image.getSize().x) &&
                l >= 0 && l < static_cast<int>(a_image.getSize().y)) {
                sf::Color color = a_image.getPixel(k, l);
                float kernelValue = a_kernel[kernelIndex];
                r += color.r * kernelValue;
                g += color.g * kernelValue;
                b += color.b * kernelValue;
                kernelSum += kernelValue;
            }
            ++kernelIndex;
        }
    }

    if (kernelSum != 0.0f) {
        r /= kernelSum;
        g /= kernelSum;
        b /= kernelSum;
    }

    return sf::Color(static_cast<sf::Uint8>(r), static_cast<sf::Uint8>(g), static_cast<sf::Uint8>(b));
}


} // advcpp
