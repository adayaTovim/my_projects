#pragma once

#include <thread>
#include <vector>

namespace advcpp {


template<typename UnaryFunc>
void convolutionImage(sf::Image const& a_originalImage, sf::Image& a_newImage, sf::Vector2u a_begin, sf::Vector2u a_end, UnaryFunc a_func, const std::vector<float>& a_kernel);

template<typename UnaryFunc>
sf::Image convolutionMultyTreads(sf::Image const& a_image, size_t a_numThreads, UnaryFunc a_func, const std::vector<float>& a_kernel);

template<typename UnaryFunc>
void convertImage(sf::Image& a_image, sf::Vector2u a_begin, sf::Vector2u a_end, UnaryFunc a_func);

template<typename UnaryFunc>
void convertMultyTreads(sf::Image& a_image, size_t a_numThreads, UnaryFunc a_func);

void joinAll(std::vector<std::thread>& a_threads);

sf::Color convertGray(sf::Color& a_color);

sf::Color reduceBlue(sf::Color& a_color);

sf::Color reduceColor(sf::Color& a_color);

sf::Color gaussianBlur(const sf::Image & a_image, unsigned int x, unsigned int y, const std::vector<float>& a_kernel);

} // advcpp

#include "inl/image_manipulation.hxx"
