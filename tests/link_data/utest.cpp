#include "mu_test.h"

#include <string>
#include <climits>

#include "link_data.hpp"

BEGIN_TEST(insert_new_url_and_link_data)
    using namespace se;
    LinkData d{};

    std::map<std::string, uint32_t> m1;
    m1.insert({"www.harry1.com", 4});
    m1.insert({"www.harry2.com", 3});
    m1.insert({"www.harry3.com", 2});
    m1.insert({"www.harry4.com", 5});

    d.updateLinkGraph("www.harry.com", m1);
    ASSERT_EQUAL(d.getLinkgraphSize(), 1);
END_TEST

BEGIN_TEST(update_existing_url_with_new_link_data)
    using namespace se;
    LinkData d{};

    std::map<std::string, uint32_t> m1;
    m1.insert({"www.harry1.com", 4});
    m1.insert({"www.harry2.com", 3});
    m1.insert({"www.harry3.com", 2});
    m1.insert({"www.harry4.com", 5});

    d.updateLinkGraph("www.harry.com", m1);

    std::map<std::string, uint32_t> m2;
    m2.insert({"www.hermione1.com", 7});
    m2.insert({"www.hermione2.com", 9});

    d.updateLinkGraph("www.harry.com", m2);
    ASSERT_EQUAL(d.getLinkgraphSize(), 1);
END_TEST

BEGIN_TEST(insert_new_2_urls)
    using namespace se;
    LinkData d{};

    std::map<std::string, uint32_t> m1;
    m1.insert({"www.harry1.com", 4});
    m1.insert({"www.harry2.com", 3});
    m1.insert({"www.harry3.com", 2});
    m1.insert({"www.harry4.com", 5});

    d.updateLinkGraph("www.harry.com", m1);
    ASSERT_EQUAL(d.getLinkgraphSize(), 1);

    std::map<std::string, uint32_t> m2;
    m2.insert({"www.ron1.com", 2});

    d.updateLinkGraph("www.ron.com", m2);
    ASSERT_EQUAL(d.getLinkgraphSize(), 2);
END_TEST

BEGIN_TEST(update_external_links_counter)
    using namespace se;
    LinkData d{};

    d.updateExternalLinksCounter(3);
    ASSERT_EQUAL(d.getExternalLinksCounter(), 3);

    d.updateExternalLinksCounter(3);
    ASSERT_EQUAL(d.getExternalLinksCounter(), 6);
END_TEST


TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
    TEST(insert_new_url_and_link_data)
    TEST(update_existing_url_with_new_link_data)
    TEST(insert_new_2_urls)
    TEST(update_external_links_counter)
END_SUITE
