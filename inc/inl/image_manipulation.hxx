#include <SFML/Graphics.hpp>
#include <thread>

#include "image_manipulation.hpp"


namespace advcpp {

template<typename UnaryFunc>
void convolutionImage(sf::Image const& a_originalImage, sf::Image& a_newImage, sf::Vector2u a_begin, sf::Vector2u a_end, UnaryFunc a_func, const std::vector<float>& a_kernel)
{
    for (size_t y = a_begin.y; y < a_end.y; ++y){
        for (size_t x = a_begin.x; x < a_end.x; ++x) {
            sf::Color color = a_originalImage.getPixel(x, y);
            color = a_func(a_originalImage, y, x, a_kernel);
            a_newImage.setPixel(x, y, color);
        }
    }
}

template<typename UnaryFunc>
sf::Image convolutionMultyTreads(sf::Image const& a_image, size_t a_numThreads, UnaryFunc a_func, const std::vector<float>& a_kernel)
{
	sf::Vector2u size = a_image.getSize();
    sf::Image newImage;
    newImage.create(size.x, size.y); 
    
    sf::Vector2u dividedSize(size.x / a_numThreads, size.y / a_numThreads);

    std::vector<std::thread> threads;

    for (size_t i = 0; i < a_numThreads; ++i) {
        sf::Vector2u begin(i * dividedSize.x, 0);
        sf::Vector2u end((i + 1) * dividedSize.x, size.y);

        threads.emplace_back([&a_image, &newImage, begin, end, a_func, a_kernel]() {
            convolutionImage(a_image, newImage, begin, end, a_func, a_kernel);
        });
    }

    joinAll(threads);

    return newImage;
}

template<typename UnaryFunc>
void convertImage(sf::Image& a_image, sf::Vector2u a_begin, sf::Vector2u a_end, UnaryFunc a_func)
{
    for (size_t y = a_begin.y; y < a_end.y; ++y){
        for (size_t x = a_begin.x; x < a_end.x; ++x) {
            sf::Color color = a_image.getPixel(x, y);
            color = a_func(color);
            a_image.setPixel(x, y, color);
        }
    }
}


template<typename UnaryFunc>
void convertMultyTreads(sf::Image& a_image, size_t a_numThreads, UnaryFunc a_func)
{
	sf::Vector2u size = a_image.getSize();

    sf::Vector2u dividedSize(size.x / a_numThreads, size.y / a_numThreads);

    std::vector<std::thread> threads;

    for (size_t i = 0; i < a_numThreads; ++i) {
        sf::Vector2u begin(i * dividedSize.x, 0);
        sf::Vector2u end((i + 1) * dividedSize.x, size.y);

        threads.emplace_back([&a_image, begin, end, a_func]() {
            convertImage(a_image, begin, end, a_func);
        });
    }

    joinAll(threads);
}

} // namespace advcpp

