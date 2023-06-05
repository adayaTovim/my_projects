#include "mu_test.h"

#include <string>
#include <vector>

#include "query.hpp"

BEGIN_TEST(test_query_string)
    using namespace se;

	std::string str1 = "tomer or adaya";
	Query query1(str1);
    std::vector<std::pair<std::string, bool>> res1 = query1.getQuery();

    ASSERT_EQUAL(res1.size(), 2);
	ASSERT_EQUAL(res1[0].first, "tomer");
	ASSERT_EQUAL(res1[1].first, "adaya");
	ASSERT_EQUAL(res1[0].second, true);
	ASSERT_EQUAL(res1[1].second, true);

END_TEST

BEGIN_TEST(test_query_with_negatives_words)
    using namespace se;

	std::string str1 = "tomer -or -adaya";
	Query query1(str1);
    std::vector<std::pair<std::string, bool>> res1 = query1.getQuery();

	std::string str2 = "-tomer or -adaya";
	Query query2(str2);
    std::vector<std::pair<std::string, bool>> res2 = query2.getQuery();

    ASSERT_EQUAL(res1.size(), 2);
	ASSERT_EQUAL(res1[0].first, "tomer");
	ASSERT_EQUAL(res1[1].first, "adaya");
	ASSERT_EQUAL(res1[0].second, true);
	ASSERT_EQUAL(res1[1].second, false);

    ASSERT_EQUAL(res2.size(), 2);
	ASSERT_EQUAL(res2[0].first, "tomer");
	ASSERT_EQUAL(res2[1].first, "adaya");
	ASSERT_EQUAL(res2[0].second, false);
	ASSERT_EQUAL(res2[1].second, false);
END_TEST

BEGIN_TEST(test_one_word)
    using namespace se;

	std::string str1 = "hello";
	std::string str2 = "t";
	std::string str3 = "3tr";
	std::string str4 = "ty";
	std::string str5 = "#ppp";
	std::string str6 = "     ";

	Query query1(str1);
	Query query2(str2);
	Query query3(str3);
	Query query4(str4);
	Query query5(str5);
	Query query6(str6);

    std::vector<std::pair<std::string, bool>> res1 = query1.getQuery();
	std::vector<std::pair<std::string, bool>> res2 = query2.getQuery();
	std::vector<std::pair<std::string, bool>> res3 = query3.getQuery();
	std::vector<std::pair<std::string, bool>> res4 = query4.getQuery();
	std::vector<std::pair<std::string, bool>> res5 = query5.getQuery();
	std::vector<std::pair<std::string, bool>> res6 = query6.getQuery();


    ASSERT_EQUAL(res1[0].first, "hello");
	ASSERT_THAT(res2.empty());
	ASSERT_THAT(res3.empty());
	ASSERT_THAT(res4.empty());
	ASSERT_THAT(res5.empty());
	ASSERT_THAT(res6.empty());

END_TEST

BEGIN_TEST(test_two_words)
    using namespace se;

	std::string str1 = "hello man";
	std::string str2 = "hello 1";
	std::string str3 = "hello 3tr";
	std::string str4 = "hello ty";
	std::string str5 = "hello #ppp";
	std::string str6 = "hello     ";

	Query query1(str1);
	Query query2(str2);
	Query query3(str3);
	Query query4(str4);
	Query query5(str5);
	Query query6(str6);

    std::vector<std::pair<std::string, bool>> res1 = query1.getQuery();
    std::vector<std::pair<std::string, bool>> res2 = query2.getQuery();
	std::vector<std::pair<std::string, bool>> res3 = query3.getQuery();
	std::vector<std::pair<std::string, bool>> res4 = query4.getQuery();
	std::vector<std::pair<std::string, bool>> res5 = query5.getQuery();
	std::vector<std::pair<std::string, bool>> res6 = query6.getQuery();

    ASSERT_EQUAL(res1[0].first, "hello");
	ASSERT_EQUAL(res1[1].first, "man");
	ASSERT_EQUAL(res2[0].first, "hello");
    ASSERT_EQUAL(res3[0].first, "hello");
    ASSERT_EQUAL(res4[0].first, "hello");
    ASSERT_EQUAL(res5[0].first, "hello");
    ASSERT_EQUAL(res6[0].first, "hello");
END_TEST


TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
	TEST(test_query_string)
	TEST(test_query_with_negatives_words)
	TEST(test_one_word)
	TEST(test_two_words)
END_SUITE

