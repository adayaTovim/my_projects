#include "mu_test.h"

#include <string> // std::string
#include <sstream> // std::stringstream

#include "curlpp_downloader.hpp" 
#include "gumbo_parser.hpp" 

BEGIN_TEST(test_get_title)
	using namespace se;

	std::string url = "https://harrypotter.fandom.com/wiki/Main_Page";
	CurlppDownloader d;
	GumboParser e(d.downloadPage(url));
	
	TRACER << e.getTitle() << std::endl;

	ASSERT_EQUAL(e.getTitle(),"Harry Potter Wiki | Fandom");
END_TEST

BEGIN_TEST(test_get_links)
	using namespace se;

	std::string url = "https://harrypotter.fandom.com/wiki/Main_Page";
	CurlppDownloader d;
	GumboParser e(d.downloadPage(url));
	
	TRACER << e.getLinks() << std::endl;

	ASSERT_PASS();
END_TEST

BEGIN_TEST(test_get_words)
	using namespace se;

	std::string url = "https://harrypotter.fandom.com/wiki/Main_Page";
	CurlppDownloader d;
	GumboParser e(d.downloadPage(url));
	
	TRACER << e.getParagraphsText() << std::endl;

	ASSERT_PASS();
END_TEST


TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
	TEST(test_get_title)
	TEST(test_get_links)
	TEST(test_get_words)
END_SUITE
