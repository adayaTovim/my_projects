#include "mu_test.h"

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <cstddef>
#include <climits>

#include "color_image.hpp"

/*
BEGIN_TEST(LoadSave)
	advcpp::ColorImage newImage = advcpp::LoadImageFromFile("cat.ppm");
	advcpp::SaveImageToFile("mycat.ppm", newImage);
END_TEST
*/

BEGIN_TEST(createImage)
	advcpp::ColorImage newImage{10,10};

	ASSERT_EQUAL(newImage.Row(), 10);
	ASSERT_EQUAL(newImage.Column(), 10);
	ASSERT_EQUAL(newImage.Saturation(), 255);

	size_t rows = newImage.Row();
	size_t columns = newImage.Column();

	for (size_t i = 0; i < rows; ++i){
		for (size_t j = 0; j < columns; ++j){
            ASSERT_EQUAL(newImage.At(i,j).m_red, 255);
        }
    }
END_TEST

BEGIN_TEST(CopyImage)
	advcpp::ColorImage newImage1{10,10};
	advcpp::ColorImage newImage2 = newImage1;

	ASSERT_EQUAL(newImage2.Row(), 10);
	ASSERT_EQUAL(newImage2.Column(), 10);
	ASSERT_EQUAL(newImage2.Saturation(), 255);

	size_t rows = newImage2.Row();
	size_t columns = newImage2.Column();

	for (size_t i = 0; i < rows; ++i){
		for (size_t j = 0; j < columns; ++j){
            ASSERT_EQUAL(newImage2.At(i,j).m_red, 255);
        }
    }
END_TEST

BEGIN_TEST(CopyAssiImage)
	advcpp::ColorImage newImage1{10,10};
	advcpp::ColorImage newImage2 {5,5};

	ASSERT_EQUAL(newImage2.Row(), 5);
	ASSERT_EQUAL(newImage2.Column(), 5);

	newImage2 = newImage1;
	ASSERT_EQUAL(newImage2.Row(), 10);
	ASSERT_EQUAL(newImage2.Column(), 10);

	size_t rows = newImage2.Row();
	size_t columns = newImage2.Column();

	for (size_t i = 0; i < rows; ++i){
		for (size_t j = 0; j < columns; ++j){
            ASSERT_EQUAL(newImage2.At(i,j).m_red, 255);
        }
    }
END_TEST

BEGIN_TEST(ReadWriteImage)
	advcpp::ColorImage newImage{10,10,250};

	size_t rows = newImage.Row();
	size_t columns = newImage.Column();

	for (size_t i = 0; i < rows; ++i){
		for (size_t j = 0; j < columns; ++j){
			newImage.Write(advcpp::Color{i+j, i+j, i+j}, j, i);
			ASSERT_EQUAL(newImage.At(i,j).m_blue, i+j);
			ASSERT_EQUAL(newImage.At(i,j).m_green, i+j);
			ASSERT_EQUAL(newImage.At(i,j).m_red, i+j);
		}
	}
END_TEST


BEGIN_TEST(clearImage)
	advcpp::ColorImage newImage{10,10,250};
	newImage.Clear(advcpp::Color{0, 0, 0});

	size_t rows = newImage.Row();
	size_t columns = newImage.Column();

	for (size_t i = 0; i < rows; ++i){
		for (size_t j = 0; j < columns; ++j){
			ASSERT_EQUAL(newImage.At(i,j).m_red, 0);
			ASSERT_EQUAL(newImage.At(i,j).m_green, 0);
			ASSERT_EQUAL(newImage.At(i,j).m_blue, 0);
		}
	}
END_TEST




TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
	TEST(createImage)
	TEST(CopyImage)
	TEST(CopyAssiImage)
	TEST(ReadWriteImage)
	TEST(clearImage)
END_SUITE