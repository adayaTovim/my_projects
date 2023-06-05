#include "mu_test.h"

#include <string> // std::string
#include <vector> // std::vector
#include <cstdint> // uint32_t

#include "search_engine.hpp"

//file name for us - ../utils/configuration.json
BEGIN_TEST(search_query)
	using namespace se;
	SearchEngine s;
	s.execute("../utils/configuration.json");
	ASSERT_PASS();
END_TEST

// BEGIN_TEST(search_word)
// 	using namespace se;

// 	std::string config_file = "../utils/configuration.json";
// 	DataBase d;

// 	CrawlerManager cm(config_file, d);
// 	cm.startCrawling();
// 	std::string quary = welcomeAndAskInput();

// 	Query q(quary);
// 	Search s(d);
// 	auto res = s.executeSearch(q);

// 	printCrawlResult(d);
// 	printSearchResult(q.getTerm(), res);

// 	ASSERT_PASS();

// END_TEST

// BEGIN_TEST(search_anothe_word)
// 	using namespace se;

// 	std::string config_file = "../utils/configuration.json";
// 	DataBase d;

// 	CrawlerManager cm(config_file, d);
// 	auto sum = cm.startCrawling();

// 	Query q("potter");
// 	Search s(d);
// 	auto res = s.executeSearch(q);

// 	printCrawlResult(d);
// 	printSearchResult(q.getTerm(), res);
// 	TRACER<<"Failed downloads : " << sum << "\n";
// 	ASSERT_THAT(res.size() > 0);

// END_TEST

// BEGIN_TEST(search_word_not_exist)
// 	using namespace se;

// 	std::string config_file = "../utils/configuration.json";
// 	DataBase d;

// 	CrawlerManager cm(config_file, d);
// 	auto sum = cm.startCrawling();

// 	Query q("abcdefghijklmnopqrstuvwxyz");
// 	Search s(d);
// 	auto res = s.executeSearch(q);

// 	printCrawlResult(d);
// 	printSearchResult(q.getTerm(), res);
// 	TRACER<<"Failed downloads : " << sum << "\n";
// 	ASSERT_THAT(res.size() == 0);

// END_TEST

// BEGIN_TEST(search_empty_word)
// 	using namespace se;

// 	std::string config_file = "../utils/configuration.json";
// 	DataBase d;

// 	CrawlerManager cm(config_file, d);
// 	auto sum = cm.startCrawling();

// 	Query q("");
// 	Search s(d);

// 	TRACER<<"Failed downloads : " << sum << "\n";

// 	try {
// 		auto res = s.executeSearch(q);
// 		printCrawlResult(d);
// 		printSearchResult(q.getTerm(), res);
// 		ASSERT_THAT(res.size() == 0);
// 	}
// 	catch (std::exception& e) {
// 		ASSERT_PASS();
// 	}

// END_TEST

TEST_SUITE(因果応報 [m1 search engine])
	TEST(search_query)
	// TEST(search_word)
	// TEST(search_anothe_word)
	// TEST(search_word_not_exist)
	// TEST(search_empty_word)

END_SUITE


