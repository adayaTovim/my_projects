#include "mu_test.h"

#include <thread>
#include <optional>
#include <algorithm>
#include <chrono>
#include <thread>
#include <iostream>
#include <ostream>
#include <atomic>

#include "string_utils.hpp"

BEGIN_TEST(test_remove_none_letters)
    using namespace se;
    std::string word = "harry//";
    std::string word2 = "/ha.  rry//";
	ASSERT_EQUAL(removeNoneLetters(word), "harry");
	ASSERT_EQUAL(removeNoneLetters(word2), "harry");
END_TEST

TEST_SUITE(因果応報 [search])
	TEST(test_remove_none_letters)

END_SUITE


