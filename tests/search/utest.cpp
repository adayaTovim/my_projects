#include "mu_test.h"

#include <thread>
#include <optional>
#include <algorithm>
#include <chrono>
#include <thread>
#include <iostream>
#include <ostream>
#include <atomic>
#include <tuple>

#include "search.hpp"
#include "query.hpp"
#include "ui.hpp"
#include "isearch.hpp"
#include "data_base.hpp"

struct Page1 {
	explicit Page1(std::string const& a_word, std::string const& a_url, std::string const& a_title, uint32_t a_counter)
	: m_word(a_word)
	, m_url(a_url)
	, m_title(a_title)
	, m_counter(a_counter)
	{
    }

	std::string m_word;
	std::string m_url;
	std::string m_title;
	uint32_t m_counter;
};

BEGIN_TEST(test_search_one_word)
    using namespace se;

    Page1 p1("harry", "www.harry.com", "Harry", 4);
    Page1 p2("harry", "www.harry1.com", "Tomer", 8);
    Page1 p3("tomer", "www.tomer.com", "adaya", 15);
    Page1 p4("or", "www.or.com", "or", 10);
    Page1 p5("harry", "www.harry3.com", "or", 10);
    Page1 p6("harry", "www.harry2.com", "adaya", 15);
    Page1 p7("or", "www.or2.com", "or", 10);

    DataBase d{};

    d.updateWordIndex(p1.m_word, p1.m_url, p1.m_title, p1.m_counter);
    d.updateWordIndex(p2.m_word, p2.m_url, p2.m_title, p2.m_counter);
    d.updateWordIndex(p3.m_word, p3.m_url, p3.m_title, p3.m_counter);
    d.updateWordIndex(p4.m_word, p4.m_url, p4.m_title, p4.m_counter);
    d.updateWordIndex(p5.m_word, p5.m_url, p5.m_title, p5.m_counter);
    d.updateWordIndex(p6.m_word, p6.m_url, p6.m_title, p6.m_counter);
    d.updateWordIndex(p7.m_word, p7.m_url, p7.m_title, p7.m_counter);

    ASSERT_EQUAL(d.getWordUrlsNumber("harry"), 4);
    ASSERT_EQUAL(d.getWordUrlsNumber("or"), 2);
    ASSERT_EQUAL(d.getWordUrlsNumber("tomer"), 1);
    ASSERT_EQUAL(d.getWordsNumber(), 3);

    Query query1("harry");
    Search search1(d);
    auto result1 = search1.executeSearch(query1);

	auto url1 = std::get<1>(result1[0]);
	ASSERT_EQUAL(url1, "www.harry2.com");

	auto url2 = std::get<1>(result1[1]);
	ASSERT_EQUAL(url2, "www.harry3.com");

	auto url3 = std::get<1>(result1[2]);
	ASSERT_EQUAL(url3, "www.harry1.com");

	auto url4 = std::get<1>(result1[3]);
	ASSERT_EQUAL(url4, "www.harry.com");

	ASSERT_EQUAL(result1.size(), 4);

    Query query2("hArry");
    Search search2(d);
    auto result2 = search2.executeSearch(query2);

	auto url5 = std::get<1>(result2[0]);
	ASSERT_EQUAL(url5, "www.harry2.com");

	auto url6 = std::get<1>(result2[1]);
	ASSERT_EQUAL(url6, "www.harry3.com");

	auto url7 = std::get<1>(result2[2]);
	ASSERT_EQUAL(url7, "www.harry1.com");

	auto url8 = std::get<1>(result2[3]);
	ASSERT_EQUAL(url8, "www.harry.com");

	ASSERT_EQUAL(result2.size(), 4);

END_TEST

BEGIN_TEST(test_search_short_word)
    using namespace se;

    Page1 p1("harry", "www.harry.com", "Harry", 4);
    Page1 p2("harry", "www.harry1.com", "Tomer", 8);
    Page1 p3("tomer", "www.tomer.com", "adaya", 15);
    Page1 p4("or", "www.harry.com", "or", 10);
    Page1 p5("harry", "www.harry3.com", "or", 10);
    Page1 p6("harry", "www.harry2.com", "adaya", 15);
    Page1 p7("or", "www.or2.com", "or", 10);

    DataBase d{};

    d.updateWordIndex(p1.m_word, p1.m_url, p1.m_title, p1.m_counter);
    d.updateWordIndex(p2.m_word, p2.m_url, p2.m_title, p2.m_counter);
    d.updateWordIndex(p3.m_word, p3.m_url, p3.m_title, p3.m_counter);
    d.updateWordIndex(p4.m_word, p4.m_url, p4.m_title, p4.m_counter);
    d.updateWordIndex(p5.m_word, p5.m_url, p5.m_title, p5.m_counter);
    d.updateWordIndex(p6.m_word, p6.m_url, p6.m_title, p6.m_counter);
    d.updateWordIndex(p7.m_word, p7.m_url, p7.m_title, p7.m_counter);

    ASSERT_EQUAL(d.getWordUrlsNumber("harry"), 4);
    ASSERT_EQUAL(d.getWordUrlsNumber("or"), 2);
    ASSERT_EQUAL(d.getWordUrlsNumber("tomer"), 1);
    ASSERT_EQUAL(d.getWordsNumber(), 3);

    Query query1("harry or");
    Search search1(d);
    auto result1 = search1.executeSearch(query1);

	auto url1 = std::get<1>(result1[0]);
	ASSERT_EQUAL(url1, "www.harry2.com");

	auto url2 = std::get<1>(result1[1]);
	ASSERT_EQUAL(url2, "www.harry3.com");

	auto url3 = std::get<1>(result1[2]);
	ASSERT_EQUAL(url3, "www.harry1.com");

	auto url4 = std::get<1>(result1[3]);
	ASSERT_EQUAL(url4, "www.harry.com");

	ASSERT_EQUAL(result1.size(), 4);

END_TEST

BEGIN_TEST(test_search_two_word_without_shared_urls)
    using namespace se;

    Page1 p1("harry", "www.harry.com", "Harry", 4);
    Page1 p2("harry", "www.harry1.com", "Tomer", 8);
    Page1 p3("tomer", "www.tomer.com", "adaya", 15);
    Page1 p4("or", "www.harry.com", "or", 10);
    Page1 p5("harry", "www.harry3.com", "or", 10);
    Page1 p6("harry", "www.harry2.com", "adaya", 15);
    Page1 p7("or", "www.or2.com", "or", 10);

    DataBase d{};

    d.updateWordIndex(p1.m_word, p1.m_url, p1.m_title, p1.m_counter);
    d.updateWordIndex(p2.m_word, p2.m_url, p2.m_title, p2.m_counter);
    d.updateWordIndex(p3.m_word, p3.m_url, p3.m_title, p3.m_counter);
    d.updateWordIndex(p4.m_word, p4.m_url, p4.m_title, p4.m_counter);
    d.updateWordIndex(p5.m_word, p5.m_url, p5.m_title, p5.m_counter);
    d.updateWordIndex(p6.m_word, p6.m_url, p6.m_title, p6.m_counter);
    d.updateWordIndex(p7.m_word, p7.m_url, p7.m_title, p7.m_counter);

    ASSERT_EQUAL(d.getWordUrlsNumber("harry"), 4);
    ASSERT_EQUAL(d.getWordUrlsNumber("or"), 2);
    ASSERT_EQUAL(d.getWordUrlsNumber("tomer"), 1);
    ASSERT_EQUAL(d.getWordsNumber(), 3);

    Query query1("harry tomer");
    Search search1(d);
    auto result1 = search1.executeSearch(query1);

	ASSERT_EQUAL(result1.size(), 0);
	ASSERT_EQUAL(result1.size(), 0);

	printSearchResult("harry tomer", result1);
END_TEST

BEGIN_TEST(test_search_two_word_with_same_url)
    using namespace se;

    Page1 p1("harry", "www.harry.com", "Harry", 4);
    Page1 p2("harry", "www.harry1.com", "Tomer", 8);
    Page1 p3("tomer", "www.harry1.com", "adaya", 15);
    Page1 p4("or", "www.harry.com", "or", 10);
    Page1 p5("harry", "www.harry3.com", "or", 10);
    Page1 p6("harry", "www.harry2.com", "adaya", 15);
    Page1 p7("or", "www.harry2.com", "or", 10);

    DataBase d{};

    d.updateWordIndex(p1.m_word, p1.m_url, p1.m_title, p1.m_counter);
    d.updateWordIndex(p2.m_word, p2.m_url, p2.m_title, p2.m_counter);
    d.updateWordIndex(p3.m_word, p3.m_url, p3.m_title, p3.m_counter);
    d.updateWordIndex(p4.m_word, p4.m_url, p4.m_title, p4.m_counter);
    d.updateWordIndex(p5.m_word, p5.m_url, p5.m_title, p5.m_counter);
    d.updateWordIndex(p6.m_word, p6.m_url, p6.m_title, p6.m_counter);
    d.updateWordIndex(p7.m_word, p7.m_url, p7.m_title, p7.m_counter);

    ASSERT_EQUAL(d.getWordUrlsNumber("harry"), 4);
    ASSERT_EQUAL(d.getWordUrlsNumber("or"), 2);
    ASSERT_EQUAL(d.getWordUrlsNumber("tomer"), 1);
    ASSERT_EQUAL(d.getWordsNumber(), 3);

    Query query1("harry tomer");
    Search search1(d);
    auto result1 = search1.executeSearch(query1);

	auto url1 = std::get<1>(result1[0]);
	ASSERT_EQUAL(url1, "www.harry1.com");

	ASSERT_EQUAL(result1.size(), 1);

	printSearchResult("harry tomer", result1);

END_TEST


TEST_SUITE(因果応報 [search])
	TEST(test_search_one_word)
    TEST(test_search_short_word)
	TEST(test_search_two_word_without_shared_urls)
	TEST(test_search_two_word_with_same_url)


END_SUITE


