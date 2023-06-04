#include "mu_test.h"

#include <SFML/Graphics.hpp>

#include "image_manipulation.hpp"


BEGIN_TEST(convertToGray)
    using namespace advcpp;
    sf::Image image;
    if (!image.loadFromFile("parrot.jpg")) {
        std::cerr << "failed to load image";
    }

    sf::Vector2u begin(0, 0);
    sf::Vector2u end = image.getSize();
    convertImage(image, begin, end, convertGray);

    if (!image.saveToFile("parrot_gray.jpg")) {
        std::cerr << "failed to save image";
    }

    ASSERT_PASS();

END_TEST


BEGIN_TEST(convertToGray1thread)
    using namespace advcpp;
    sf::Image image;
    if (!image.loadFromFile("parrot.jpg")) {
        std::cerr << "failed to load image";
    }

    convertMultyTreads(image, 1, convertGray);

    if (!image.saveToFile("parrot_gray1thread.jpg")) {
        std::cerr << "failed to save image";
    }

    ASSERT_PASS();

END_TEST

BEGIN_TEST(convertToGray2thread)
    using namespace advcpp;
    sf::Image image;
    if (!image.loadFromFile("parrot.jpg")) {
        std::cerr << "failed to load image";
    }

    convertMultyTreads(image, 2, convertGray);

    if (!image.saveToFile("parrot_gray2thread.jpg")) {
        std::cerr << "failed to save image";
    }

    ASSERT_PASS();

END_TEST


BEGIN_TEST(convertToGray4thread)
    using namespace advcpp;
    sf::Image image;
    if (!image.loadFromFile("parrot.jpg")) {
        std::cerr << "failed to load image";
    }

    convertMultyTreads(image, 4, convertGray);

    if (!image.saveToFile("parrot_gray2thread.jpg")) {
        std::cerr << "failed to save image";
    }

    ASSERT_PASS();

END_TEST

BEGIN_TEST(reduceBlue1thread)
    using namespace advcpp;
    sf::Image image;
    if (!image.loadFromFile("parrot.jpg")) {
        std::cerr << "failed to load image";
    }

    convertMultyTreads(image, 1, reduceBlue);

    if (!image.saveToFile("parrot_blue1thread.jpg")) {
        std::cerr << "failed to save image";
    }

    ASSERT_PASS();

END_TEST

BEGIN_TEST(reduceBlue2thread)
    using namespace advcpp;
    sf::Image image;
    if (!image.loadFromFile("parrot.jpg")) {
        std::cerr << "failed to load image";
    }

    convertMultyTreads(image, 2, reduceBlue);

    if (!image.saveToFile("parrot_blue2thread.jpg")) {
        std::cerr << "failed to save image";
    }

    ASSERT_PASS();

END_TEST

BEGIN_TEST(reduceBlue4thread)
    using namespace advcpp;
    sf::Image image;
    if (!image.loadFromFile("parrot.jpg")) {
        std::cerr << "failed to load image";
    }

    convertMultyTreads(image, 4, reduceBlue);

    if (!image.saveToFile("parrot_gray2thread.jpg")) {
        std::cerr << "failed to save image";
    }

    ASSERT_PASS();

END_TEST

BEGIN_TEST(reduceColor1thread)
    using namespace advcpp;
    sf::Image image;
    if (!image.loadFromFile("parrot.jpg")) {
        std::cerr << "failed to load image";
    }

    convertMultyTreads(image, 1, reduceColor);

    if (!image.saveToFile("parrot_reduceColor1thread.jpg")) {
        std::cerr << "failed to save image";
    }

    ASSERT_PASS();

END_TEST

BEGIN_TEST(reduceColor2thread)
    using namespace advcpp;
    sf::Image image;
    if (!image.loadFromFile("parrot.jpg")) {
        std::cerr << "failed to load image";
    }

    convertMultyTreads(image, 2, reduceColor);

    if (!image.saveToFile("parrot_reduceColor2thread.jpg")) {
        std::cerr << "failed to save image";
    }

    ASSERT_PASS();

END_TEST

BEGIN_TEST(reduceColor4thread)
    using namespace advcpp;
    sf::Image image;
    if (!image.loadFromFile("parrot.jpg")) {
        std::cerr << "failed to load image";
    }

    convertMultyTreads(image, 4, reduceColor);

    if (!image.saveToFile("parrot_reduceColor2thread.jpg")) {
        std::cerr << "failed to save image";
    }

    ASSERT_PASS();

END_TEST

TEST_SUITE(因果応報 [inga ōhō:bad causes bring bad results])
    TEST(convertToGray)
    TEST(convertToGray1thread)
    TEST(convertToGray2thread)
    TEST(convertToGray4thread)
    TEST(reduceBlue1thread)
    TEST(reduceBlue2thread)
    TEST(reduceBlue4thread)
    TEST(reduceColor1thread)
    TEST(reduceColor2thread)
    TEST(reduceColor4thread)

END_SUITE

