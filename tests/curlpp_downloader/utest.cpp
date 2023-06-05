#include "mu_test.h"

#include <string> // std::string
#include <sstream> // std::stringstream

#include "curlpp_downloader.hpp" 

BEGIN_TEST(test_existing_url)
	using namespace se;

	std::string url = "https://harrypotter.fandom.com/wiki/Main_Page";
	CurlppDownloader d;
    std::ostringstream os;

	os = d.downloadPage(url);
	// TRACER << os.str();

	ASSERT_PASS();
END_TEST

BEGIN_TEST(test_not_existing_url)
	using namespace se;

	std::string url = "https://ygate.co.il";
	CurlppDownloader d;
    std::ostringstream os;

	//will throw exception
	os = d.downloadPage(url);

	ASSERT_PASS();
END_TEST


TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
	TEST(test_existing_url)
	TEST(test_not_existing_url)
END_SUITE
