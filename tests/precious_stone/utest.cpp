#include "mu_test.h"

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <cstddef>
#include <climits>

#include "message.hpp"
#include "black_box.hpp"
#include "console_destination.hpp"
#include "console_source.hpp"
#include "convert_vowel.hpp"
#include "convert_capitalize.hpp"
#include "convert_caesar.hpp"
#include "udp_source.hpp"
#include "udp_destination.hpp"
#include "file_source.hpp"
#include "file_destination.hpp"

// BEGIN_TEST(console_input_convert_vowel)
// 	using namespace precious_stone;
// 	std::cout << "write your message"<< std::endl;
//     ConsoleSource newSource;
// 	ConsoleDestination newDestination(std::cout);
// 	ConvertVowel newEncoder;

// 	BlackBox newBlackBox{newSource, newDestination, newEncoder};
//     newBlackBox.run();

// 	ASSERT_PASS();  
// END_TEST


// BEGIN_TEST(console_input_convert_capitalize)
// using namespace precious_stone;
// 	std::cout << "write your message"<< std::endl;
//     ConsoleSource newSource;
// 	ConsoleDestination newDestination(std::cout);
// 	ConvertCapitalize newEncoder;

// 	BlackBox newBlackBox{newSource, newDestination, newEncoder};
//     newBlackBox.run();

// 	ASSERT_PASS();  
// END_TEST


// BEGIN_TEST(console_input_convert_caesar)
//     using namespace precious_stone;
// 	std::cout << "write your message"<< std::endl;
//     ConsoleSource newSource;
// 	ConsoleDestination newDestination(std::cout);
// 	ConvertCaesar newEncoder;

// 	BlackBox newBlackBox{newSource, newDestination, newEncoder};
//     newBlackBox.run();

// 	ASSERT_PASS();  
// END_TEST


// BEGIN_TEST(file_to_console_convert_capitalize)
//     using namespace precious_stone;
// 	//std::cout << "write your message"<< std::endl;
//     FileSource newSource("myfile.txt");
// 	ConsoleDestination newDestination(std::cout);
// 	ConvertCapitalize newEncoder;

// 	BlackBox newBlackBox{newSource, newDestination, newEncoder};
//     newBlackBox.run();

// 	ASSERT_PASS(); 
// END_TEST


// BEGIN_TEST(console_to_file_convert_vowel)
//     using namespace precious_stone;
// 	//std::cout << "write your message"<< std::endl;
//     ConsoleSource newSource;
// 	FileDestination newDestination("encoderText.txt");
// 	ConvertVowel newEncoder;

// 	BlackBox newBlackBox{newSource, newDestination, newEncoder};
//     newBlackBox.run();

// 	ASSERT_PASS(); 
// END_TEST


// BEGIN_TEST(file_to_file_convert_vowel)
//     using namespace precious_stone;
// 	//std::cout << "write your message"<< std::endl;
//     FileSource newSource("myfile.txt");
// 	FileDestination newDestination("encoderText.txt");
// 	ConvertVowel newEncoder;

// 	BlackBox newBlackBox{newSource, newDestination, newEncoder};
//     newBlackBox.run();

// 	ASSERT_PASS(); 
// END_TEST

// BEGIN_TEST(udp_input_convert_caesar)
//  using namespace precious_stone; 
// 	std::cout << "write your message"<< std::endl;

// 	UdpSource newSource(1234, "10.0.0.16");
// 	ConsoleDestination newDestination(std::cout);
// 	ConvertCaesar newEncoder;

// 	BlackBox newBlackBox{newSource, newDestination, newEncoder};
//     newBlackBox.run();

// END_TEST

BEGIN_TEST(console_to_udp_convert_vowel)
    using namespace precious_stone;
	std::cout << "write your message"<< std::endl;
    ConsoleSource newSource;
	UdpDestination newDestination(123, "10.0.0.16");
	ConvertVowel newEncoder;

	BlackBox newBlackBox{newSource, newDestination, newEncoder};
    newBlackBox.run();

	ASSERT_PASS(); 
END_TEST

// BEGIN_TEST(udp_convert_capitalize)
//  using namespace precious_stone; 
// 	std::cout << "write your message"<< std::endl;
//  	UdpSource newSource(123, "10.0.0.16");
// 	UdpDestination newDestination(123, "10.0.0.16");
// 	ConvertCapitalize newEncoder;

// 	BlackBox newBlackBox{newSource, newDestination, newEncoder};
//     newBlackBox.run();


// END_TEST


TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
	//TEST(console_input_convert_vowel)
	//TEST(console_input_convert_capitalize)
	//TEST(console_input_convert_caesar)
	//TEST(file_to_console_convert_capitalize)
	//TEST(console_to_file_convert_vowel)
	//TEST(file_to_file_convert_vowel)
	//TEST(udp_input_convert_caesar)
	TEST(console_to_udp_convert_vowel)
	//	TEST(udp_convert_capitalize)

END_SUITE
