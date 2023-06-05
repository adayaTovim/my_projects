#include "mu_test.h"

#include <string> // std::string

#include "crawler.hpp" 
#include "web_page.hpp" 

#include "update_data.hpp"      // UpdateData header
#include "iupdate.hpp"          // IUpdate header
#include "data_base.hpp"        // IUpdate header

BEGIN_TEST(crawler_init)
	using namespace se;

	DataBase d;
	Crawler c(d);

	WebPage p = c.crawlOneUrl("https://harrypotter.fandom.com/wiki/Main_Page");
	auto v = d.getWordData("Harry");
	
	ASSERT_EQUAL(p.getWordCount("Harry"), 4);
END_TEST

BEGIN_TEST(crawler_check_exception)
	using namespace se;

	DataBase d;
	Crawler c(d);

	WebPage p = c.crawlOneUrl("https://harrypottersdfw.com/wiki/Main_Page");
	
	ASSERT_EQUAL(p.title(), "<empty_title>");
	ASSERT_EQUAL(c.getExternalLinks(), 1);
END_TEST

TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
	TEST(crawler_init)
	TEST(crawler_check_exception)
END_SUITE
