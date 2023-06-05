#include "mu_test.h"

#include <vector>

#include "iupdate.hpp"
#include "web_page.hpp"
#include "update_data.hpp"
#include "data_base.hpp"

BEGIN_TEST(storePageDataTest)
    using namespace se;
    WebPage page("Example Page", "http://www.example.com");
    page.insertWord("example");
    page.insertWord("page");
    page.insertWord("example");
    page.insertWord("text");

    DataBase d{};
    UpdateData updateData(d);
    updateData.storePageData(page);

    ASSERT_PASS();
END_TEST

BEGIN_TEST(storeCounterExternalLinksTest)
    using namespace se;
    WebPage page("Example Page", "http://www.example.com");
    page.insertLink("http://www.example.com/page1");
    page.insertLink("http://www.example.com/page2");
    page.insertLink("http://www.example2.com");
    page.insertLink("http://www.example.com/page3");

    DataBase d{};
    UpdateData updateData(d);
    updateData.storeCounterExternalLinks(page);
    //??
    ASSERT_PASS();
END_TEST


TEST_SUITE(因果応報 [update data])
    TEST(storePageDataTest)
    TEST(storeCounterExternalLinksTest)
END_SUITE