#include "mu_test.h"

#include <string>
#include <climits>

#include "word_index.hpp"

struct Page1 {
	explicit Page1(std::string const& a_word, std::string const& a_url, std::string const& a_title, uint32_t a_counter) 
	: m_word(a_word) 
	, m_url(a_url) 
	, m_title(a_title) 
	, m_counter(a_counter)
	{}

	std::string m_word;
	std::string m_url;
	std::string m_title;
	uint32_t m_counter;
};

BEGIN_TEST(update_2_words)
	using namespace se;
	Page1 p1("harry", "www.harry.com", "Harry", 4);
	Page1 p2("tomer", "www.harry.com", "Tomer", 8);
	WordIndex w{};

	w.setWordIndex(p1.m_word, p1.m_url, p1.m_title, p1.m_counter);
	w.setWordIndex(p2.m_word, p2.m_url, p2.m_title, p2.m_counter);

	ASSERT_EQUAL(w.getNumWordOfUrls("harry"), 1);
	ASSERT_EQUAL(w.getNumOfWords(), 2);
END_TEST

BEGIN_TEST(update_1_word_many_times)
	using namespace se;
	Page1 p1("harry", "www.harry.com", "Harry", 4);
	Page1 p2("harry", "www.harry1.com", "Tomer", 8);
	Page1 p3("harry", "www.harry2.com", "adaya", 15);
	Page1 p4("harry", "www.harry3.com", "or", 10);
	WordIndex w{};

	w.setWordIndex(p1.m_word, p1.m_url, p1.m_title, p1.m_counter);
	w.setWordIndex(p2.m_word, p2.m_url, p2.m_title, p2.m_counter);
	w.setWordIndex(p3.m_word, p3.m_url, p3.m_title, p3.m_counter);
	w.setWordIndex(p4.m_word, p4.m_url, p4.m_title, p4.m_counter);

	ASSERT_EQUAL(w.getNumWordOfUrls("harry"), 4);
	ASSERT_EQUAL(w.getNumOfWords(), 1);
END_TEST

BEGIN_TEST(update_3_words_many_urls)
	using namespace se;
	Page1 p1("harry", "www.harry.com", "Harry", 4);
	Page1 p2("harry", "www.harry1.com", "Tomer", 8);
	Page1 p3("tomer", "www.tomer.com", "adaya", 15);
	Page1 p4("or", "www.or.com", "or", 10);
	Page1 p5("harry", "www.harry3.com", "or", 10);
	Page1 p6("harry", "www.harry2.com", "adaya", 15);
	Page1 p7("or", "www.or2.com", "or", 10);
	
	WordIndex w{};

	w.setWordIndex(p1.m_word, p1.m_url, p1.m_title, p1.m_counter);
	w.setWordIndex(p2.m_word, p2.m_url, p2.m_title, p2.m_counter);
	w.setWordIndex(p3.m_word, p3.m_url, p3.m_title, p3.m_counter);
	w.setWordIndex(p4.m_word, p4.m_url, p4.m_title, p4.m_counter);
	w.setWordIndex(p5.m_word, p5.m_url, p5.m_title, p5.m_counter);
	w.setWordIndex(p6.m_word, p6.m_url, p6.m_title, p6.m_counter);
	w.setWordIndex(p7.m_word, p7.m_url, p7.m_title, p7.m_counter);


	ASSERT_EQUAL(w.getNumWordOfUrls("harry"), 4);
	ASSERT_EQUAL(w.getNumWordOfUrls("or"), 2);
	ASSERT_EQUAL(w.getNumWordOfUrls("tomer"), 1);
	ASSERT_EQUAL(w.getNumOfWords(), 3);
END_TEST

BEGIN_TEST(lower_upper_case_words)
	using namespace se;
	Page1 p1("harry", "www.harry.com", "Harry", 4);
	Page1 p2("Harry", "www.harry1.com", "Tomer", 8);
	Page1 p3("tomer", "www.tomer.com", "adaya", 15);
	Page1 p4("or", "www.or.com", "or", 10);
	Page1 p5("harry", "www.harry3.com", "or", 10);
	Page1 p6("haRry", "www.harry2.com", "adaya", 15);
	Page1 p7("Or", "www.or2.com", "or", 10);
	
	WordIndex w{};

	w.setWordIndex(p1.m_word, p1.m_url, p1.m_title, p1.m_counter);
	w.setWordIndex(p2.m_word, p2.m_url, p2.m_title, p2.m_counter);
	w.setWordIndex(p3.m_word, p3.m_url, p3.m_title, p3.m_counter);
	w.setWordIndex(p4.m_word, p4.m_url, p4.m_title, p4.m_counter);
	w.setWordIndex(p5.m_word, p5.m_url, p5.m_title, p5.m_counter);
	w.setWordIndex(p6.m_word, p6.m_url, p6.m_title, p6.m_counter);
	w.setWordIndex(p7.m_word, p7.m_url, p7.m_title, p7.m_counter);

	auto v = w.getIndexedWordData("harry");
	ASSERT_EQUAL(v.size(), 4);
	v = w.getIndexedWordData("haRry");
	ASSERT_EQUAL(v.size(), 4);

	ASSERT_EQUAL(w.getNumWordOfUrls("harry"), 4);
	ASSERT_EQUAL(w.getNumWordOfUrls("haRry"), 4);
	ASSERT_EQUAL(w.getNumWordOfUrls("Harry"), 4);
	ASSERT_EQUAL(w.getNumOfWords(), 3);
END_TEST

BEGIN_TEST(empty_map)
	using namespace se;
	WordIndex w{};
	ASSERT_EQUAL(w.getNumOfWords(), 0);
END_TEST

BEGIN_TEST(get_url_word_not_found)
	using namespace se;
	Page1 p1("harry", "www.harry.com", "Harry", 4);
	Page1 p2("harry", "www.harry1.com", "Tomer", 8);
	Page1 p3("tomer", "www.tomer.com", "adaya", 15);
	Page1 p4("or", "www.or.com", "or", 10);
	WordIndex w{};

	w.setWordIndex(p1.m_word, p1.m_url, p1.m_title, p1.m_counter);
	w.setWordIndex(p2.m_word, p2.m_url, p2.m_title, p2.m_counter);
	w.setWordIndex(p3.m_word, p3.m_url, p3.m_title, p3.m_counter);
	w.setWordIndex(p4.m_word, p4.m_url, p4.m_title, p4.m_counter);
	ASSERT_EQUAL(w.getNumWordOfUrls("adaya"), 0);
END_TEST

BEGIN_TEST(get_word_urls_vec_size)
	using namespace se;
	Page1 p1("harry", "www.harry.com", "Harry", 4);
	Page1 p2("harry", "www.harry1.com", "Tomer", 8);
	Page1 p3("tomer", "www.tomer.com", "adaya", 15);
	Page1 p4("or", "www.or.com", "or", 10);
	Page1 p5("harry", "www.harry3.com", "or", 10);
	Page1 p6("harry", "www.harry2.com", "adaya", 15);
	Page1 p7("or", "www.or2.com", "or", 10);
	
	WordIndex w{};

	w.setWordIndex(p1.m_word, p1.m_url, p1.m_title, p1.m_counter);
	w.setWordIndex(p2.m_word, p2.m_url, p2.m_title, p2.m_counter);
	w.setWordIndex(p3.m_word, p3.m_url, p3.m_title, p3.m_counter);
	w.setWordIndex(p4.m_word, p4.m_url, p4.m_title, p4.m_counter);
	w.setWordIndex(p5.m_word, p5.m_url, p5.m_title, p5.m_counter);
	w.setWordIndex(p6.m_word, p6.m_url, p6.m_title, p6.m_counter);
	w.setWordIndex(p7.m_word, p7.m_url, p7.m_title, p7.m_counter);

	auto v = w.getIndexedWordData("harry");
	ASSERT_EQUAL(v.size(), 4);
	v = w.getIndexedWordData("tomer");
	ASSERT_EQUAL(v.size(), 1);
	v = w.getIndexedWordData("or");
	ASSERT_EQUAL(v.size(), 2);
	
END_TEST

BEGIN_TEST(get_word_urls_word_not_found)
	using namespace se;
	Page1 p1("harry", "www.harry.com", "Harry", 4);
	Page1 p2("harry", "www.harry1.com", "Tomer", 8);
	Page1 p3("tomer", "www.tomer.com", "adaya", 15);
	Page1 p4("or", "www.or.com", "or", 10);
	Page1 p5("harry", "www.harry3.com", "or", 10);
	Page1 p6("harry", "www.harry2.com", "adaya", 15);
	Page1 p7("or", "www.or2.com", "or", 10);
	
	WordIndex w{};

	w.setWordIndex(p1.m_word, p1.m_url, p1.m_title, p1.m_counter);
	w.setWordIndex(p2.m_word, p2.m_url, p2.m_title, p2.m_counter);
	w.setWordIndex(p3.m_word, p3.m_url, p3.m_title, p3.m_counter);
	w.setWordIndex(p4.m_word, p4.m_url, p4.m_title, p4.m_counter);
	w.setWordIndex(p5.m_word, p5.m_url, p5.m_title, p5.m_counter);
	w.setWordIndex(p6.m_word, p6.m_url, p6.m_title, p6.m_counter);
	w.setWordIndex(p7.m_word, p7.m_url, p7.m_title, p7.m_counter);

	auto v = w.getIndexedWordData("miri");
	ASSERT_EQUAL(v.size(), 0);
	
END_TEST

BEGIN_TEST(get_word_urls_vec_sort)
	using namespace se;
	Page1 p1("harry", "www.fiveth.com", "title1", 4);
	Page1 p2("harry", "www.third.com", "title2", 8);
	Page1 p3("tomer", "www.tomer.com", "title3", 15);
	Page1 p4("or", "www.or.com", "title4", 10);
	Page1 p5("harry", "www.second.com", "title5", 10);
	Page1 p6("harry", "www.first.com", "title6", 15);
	Page1 p7("harry", "www.forth.com", "title7", 7);
	
	WordIndex w{};

	w.setWordIndex(p1.m_word, p1.m_url, p1.m_title, p1.m_counter);
	w.setWordIndex(p2.m_word, p2.m_url, p2.m_title, p2.m_counter);
	w.setWordIndex(p3.m_word, p3.m_url, p3.m_title, p3.m_counter);
	w.setWordIndex(p4.m_word, p4.m_url, p4.m_title, p4.m_counter);
	w.setWordIndex(p5.m_word, p5.m_url, p5.m_title, p5.m_counter);
	w.setWordIndex(p6.m_word, p6.m_url, p6.m_title, p6.m_counter);
	w.setWordIndex(p7.m_word, p7.m_url, p7.m_title, p7.m_counter);

	auto v = w.getIndexedWordData("harry");
	ASSERT_EQUAL(v.size(), 5);
	ASSERT_EQUAL(std::get<0>(v[0]), "title6");
	ASSERT_EQUAL(std::get<1>(v[0]), "www.first.com");
	ASSERT_EQUAL(std::get<2>(v[0]), 15);
	ASSERT_EQUAL(std::get<0>(v[1]), "title5");
	ASSERT_EQUAL(std::get<1>(v[1]), "www.second.com");
	ASSERT_EQUAL(std::get<2>(v[1]), 10);
	ASSERT_EQUAL(std::get<0>(v[2]), "title2");
	ASSERT_EQUAL(std::get<1>(v[2]), "www.third.com");
	ASSERT_EQUAL(std::get<2>(v[2]), 8);
	ASSERT_EQUAL(std::get<0>(v[3]), "title7");
	ASSERT_EQUAL(std::get<1>(v[3]), "www.forth.com");
	ASSERT_EQUAL(std::get<2>(v[3]), 7);
	ASSERT_EQUAL(std::get<0>(v[4]), "title1");
	ASSERT_EQUAL(std::get<1>(v[4]), "www.fiveth.com");
	ASSERT_EQUAL(std::get<2>(v[4]), 4);
	
END_TEST

TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
	TEST(update_2_words)
	TEST(update_1_word_many_times)
	TEST(lower_upper_case_words)
	TEST(update_3_words_many_urls)
	TEST(empty_map)
	TEST(get_url_word_not_found)
	TEST(get_word_urls_vec_size)
	TEST(get_word_urls_word_not_found)
	TEST(get_word_urls_vec_sort)
END_SUITE
