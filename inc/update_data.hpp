
#pragma once

#include <vector>

#include "iupdate.hpp"
#include "web_page.hpp"

namespace se {

class UpdateData {
public:
    explicit UpdateData(IUpdate& a_updater);
    UpdateData(UpdateData const& a_other) = delete;
    UpdateData& operator=(UpdateData const& a_other) = delete;
    ~UpdateData() = default;

    void storeAllData(WebPage& a_page);

private:
    void storePageData(WebPage& a_page);
    void storeCounterExternalLinks(WebPage& a_page);
    void storeLinkGraph(WebPage& a_page);
    
private:
    IUpdate& m_updater;
};

} // namespace se


