#include "mu_test.h"

#include <string>
#include <climits>
#include <algorithm>
#include "validator.hpp"

BEGIN_TEST(test_1_invalid_urls)
	using namespace se;
	std::map<std::string, uint32_t> urlMap;
	uint32_t invalidURLs = 0;
	std::string targetURL = "https://harrypotter.fandom.com/wiki/Main_Page";

	urlMap["https://harrypotter.fandom.com/wiki/page1"] = 1;
    urlMap["https://harrypotter.fandom.com/wiki/page2"] = 2;
    urlMap["https://example.com/page3"] = 3;
    urlMap["https://harrypotter.fandom.com/wiki/page4"] = 4;
	ASSERT_EQUAL(urlMap.size(), 4);

	// Check if "https://example.com/page3" is in the urlMap
    auto it = urlMap.find("https://example.com/page3");
    ASSERT_THAT(it != urlMap.end());

	invalidURLs = validateUrl(urlMap, targetURL);

	ASSERT_EQUAL(invalidURLs, 1);
END_TEST

BEGIN_TEST(test_empty_map)
 	using namespace se;
    std::map<std::string, uint32_t> urlMap;
    uint32_t invalidURLs = validateUrl(urlMap, "https://harrypotter.fandom.com");
    ASSERT_EQUAL(invalidURLs, 0);
END_TEST

BEGIN_TEST(test_single_valid_url)
 	using namespace se;
    std::map<std::string, uint32_t> urlMap = {{"https://harrypotter.fandom.com/page1", 1}};
    uint32_t invalidURLs = validateUrl(urlMap, "https://harrypotter.fandom.com");
    ASSERT_EQUAL(invalidURLs, 0);
END_TEST

BEGIN_TEST(test_single_invalid_url)
 	using namespace se;
    std::map<std::string, uint32_t> urlMap = {{"https://invalidurl.fandom.com", 1}};
    uint32_t invalidURLs = validateUrl(urlMap, "https://harrypotter.fandom.com/wiki/Main_Page");
    ASSERT_EQUAL(invalidURLs, 1);
END_TEST

BEGIN_TEST(test_multiple_valid_urls)
 	using namespace se;
    std::map<std::string, uint32_t> urlMap = {
        {"https://harrypotter.fandom.com/wiki/page2", 4},
        {"https://harrypotter.fandom.com/wiki/page1", 5}
    };
    uint32_t invalidURLs = validateUrl(urlMap, "https://harrypotter.fandom.com/wiki/Main_Page");
    ASSERT_EQUAL(invalidURLs, 0);
    ASSERT_EQUAL(urlMap.size(), 2);
END_TEST

BEGIN_TEST(test_multiple_invalid_urls)
 	using namespace se;
    std::map<std::string, uint32_t> urlMap = {
        {"https://example.com.notvalid/wiki", 6},
        {"https://example.com.notvalid2/wiki", 7}
    };
    uint32_t invalidURLs = validateUrl(urlMap, "https://harrypotter.fandom.com/wiki/Main_Page");
    ASSERT_EQUAL(invalidURLs, 2);
    ASSERT_EQUAL(urlMap.size(), 0);
END_TEST

BEGIN_TEST(test_short_url)
 	using namespace se;
    std::map<std::string, uint32_t> urlMap = {{"https://harry/wiki", 8}};
    uint32_t invalidURLs = validateUrl(urlMap, "https://harrypotter.fandom.com/wiki/Main_Page");
    ASSERT_EQUAL(invalidURLs, 1);
    ASSERT_EQUAL(urlMap.size(), 0);
END_TEST

BEGIN_TEST(test_invalid_domain)
 	using namespace se;
    std::map<std::string, uint32_t> urlMap = {{"harrypotter.fandom.com", 8}};
    uint32_t invalidURLs = validateUrl(urlMap, "harrypotter.fandom.com");
    ASSERT_EQUAL(invalidURLs, 0);
    ASSERT_EQUAL(urlMap.size(), 1);
END_TEST

BEGIN_TEST(test_same_url)
 	using namespace se;
    std::map<std::string, uint32_t> urlMap = {{"https://harrypotter.fandom.com/wiki/Main_Page", 8}};
    uint32_t invalidURLs = validateUrl(urlMap, "https://harrypotter.fandom.com/wiki/Main_Page");
    ASSERT_EQUAL(invalidURLs, 0);
    ASSERT_EQUAL(urlMap.size(), 1);
END_TEST

TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
	TEST(test_1_invalid_urls)
	TEST(test_empty_map)
	TEST(test_single_valid_url)
	TEST(test_single_invalid_url)
	TEST(test_multiple_valid_urls)
	TEST(test_multiple_invalid_urls)
	TEST(test_short_url)
    TEST(test_invalid_domain)
    TEST(test_same_url)

END_SUITE


