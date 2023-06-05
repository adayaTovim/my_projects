#include <sstream> // std::stringstream

#include "crawler.hpp" // Current header

namespace se {

namespace
{

void insertLinksToPage(const std::string& a_links, WebPage& a_page)
{
    std::string link = "";

    for(auto c : a_links){
        if(c == ' ' || c == '\t' || c == '\n' || c == '\r'){
            if(!link.empty()){
                a_page.insertLink(link);
                link = "";
            }
        }
        else{
            link += c;
        }
    }

	if(!link.empty()){
        a_page.insertLink(link);
	}
}

void insertWordsToPage(const std::string& a_words, WebPage& a_page)
{
    std::string word = "";

    for(auto c : a_words){
        if(c == ' ' || c == '\t' || c == '\n' || c == '\r'){
            if(!word.empty()){
                a_page.insertWord(word);
                word = "";
            }
        }
        else{
            word += c;
        }
    }

	if(!word.empty()){
		a_page.insertWord(word);
	}
}

} // empty namespace for static functions

Crawler::Crawler(IUpdate& a_updater)
: m_downloader()
, m_parser()
, m_updater(a_updater)
, m_failedLinks()
{}

WebPage Crawler::crawlOneUrl(const std::string& a_url)
{
    std::ostringstream os;

    try {
        os = m_downloader.downloadPage(a_url);
    }
    catch(curlpp::RuntimeError &e) {
        ++m_failedLinks;
        return WebPage("<empty_title>", "<empty_url>");
	}
	catch(curlpp::LogicError &e) {
        ++m_failedLinks;
        return WebPage("<empty_title>", "<empty_url>");
	}

    m_parser.parse(os);

    std::string title = m_parser.getTitle();
    WebPage page(title, a_url);

    std::string sumLinks = m_parser.getLinks();
    insertLinksToPage(sumLinks, page);

    std::string sumText = m_parser.getParagraphsText();
    insertWordsToPage(sumText, page);

    m_parser.freeParse();
    m_updater.storeAllData(page);
    return page;
}

uint32_t Crawler::getFailedLinks() const noexcept
{
    return m_failedLinks;
}

} // namespace se
