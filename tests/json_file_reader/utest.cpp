#include "mu_test.h"

#include <string> // std::string

#include "json_file_reader.hpp"

BEGIN_TEST(test_configuration_reader_one_url)
	using namespace se;

	std::string config_file = "configuration_one_url.json";
	JsonFile conf(config_file);

	auto urlVec = conf.getUrls();

	ASSERT_EQUAL(urlVec.front(), "https://harrypotter.fandom.com/wiki/Main_Page");
	ASSERT_EQUAL(conf.crawlMode(), "DFS");
	ASSERT_EQUAL(conf.depth(), 2);
	ASSERT_EQUAL(conf.maxPages(), 20);
END_TEST

BEGIN_TEST(test_configuration_reader_two_urls)
	using namespace se;

	std::string config_file = "configuration_two_urls.json";
	JsonFile conf(config_file);

	auto urlVec = conf.getUrls();

	ASSERT_EQUAL(urlVec.front(), "https://harrypotter.fandom.com/wiki/Main_Page");
	ASSERT_EQUAL(urlVec.back(), "https://harrypotter.fandom.com/wiki/Dark_wizard");
	ASSERT_EQUAL(conf.crawlMode(), "DFS");
	ASSERT_EQUAL(conf.depth(), 2);
	ASSERT_EQUAL(conf.maxPages(), 20);
END_TEST


BEGIN_TEST(test_empty_configuration_reader)
	using namespace se;

	std::string config_file = "configuration_empty.json";
	JsonFile conf(config_file);

	auto urlVec = conf.getUrls();

	ASSERT_EQUAL(urlVec.front(), "https://harrypotter.fandom.com/wiki/Main_Page");
	ASSERT_EQUAL(conf.crawlMode(), "DFS");
	ASSERT_EQUAL(conf.depth(), 2);
	ASSERT_EQUAL(conf.maxPages(), 20);
	ASSERT_EQUAL(conf.totalSearchList(), 10);
END_TEST


TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
	TEST(test_configuration_reader_one_url)
	TEST(test_configuration_reader_two_urls)
	TEST(test_empty_configuration_reader)
END_SUITE
