#include "mu_test.h"

#include <string> // std::string

#include "web_page.hpp" 

BEGIN_TEST(web_page_init)
	using namespace se;

	std::string title = "Harry Potter Wiki | Fandom";
	std::string url = "https://harrypotter.fandom.com/wiki/Main_Page";

	WebPage w(title, url);

	ASSERT_EQUAL(w.title(), title);
	ASSERT_EQUAL(w.url(), url);
END_TEST

BEGIN_TEST(web_page_one_word_count)
	using namespace se;

	std::string title = "Harry Potter Wiki | Fandom";
	std::string url = "https://harrypotter.fandom.com/wiki/Main_Page";
	std::string word = "Harry";
	std::string notInsertedWord = "Ron";

	WebPage w(title, url);
	w.insertWord(word);

	ASSERT_EQUAL(w.getWordCount(word), 1);
	ASSERT_EQUAL(w.getWordCount(notInsertedWord), 0);

	w.insertWord(word);

	ASSERT_EQUAL(w.getWordCount(word), 2);
	ASSERT_EQUAL(w.uniqueWordsCount(), 1);
	ASSERT_EQUAL(w.totalWordsCount(), 2);
END_TEST

BEGIN_TEST(web_page_one_link_count)
	using namespace se;

	std::string title = "Harry Potter Wiki | Fandom";
	std::string url = "https://harrypotter.fandom.com/wiki/Main_Page";
	std::string link = "https://harrypotter.fandom.com/wiki/Forbidden_Forest";
	std::string notInsertedLink = "https://www.walla.co.il";

	WebPage w(title, url);
	w.insertLink(link);

	ASSERT_EQUAL(w.getLinkCount(link), 1);
	ASSERT_EQUAL(w.getLinkCount(notInsertedLink), 0);
END_TEST

TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
	TEST(web_page_init)
	TEST(web_page_one_word_count)
	TEST(web_page_one_link_count)
END_SUITE
