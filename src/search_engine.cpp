#include "search_engine.hpp"
#include "data_base.hpp"    // IUpdate header
#include "query.hpp"        // Query header
#include "ui.hpp"        	// UI header
#include "crawler_mannager.hpp"        	// CrawlerManager header

namespace se
{

void SearchEngine::execute(std::string const& a_fileName)
{
	DataBase d;
    JsonFile jsonFile(a_fileName);
    
	CrawlerManager cm(jsonFile, d);
	cm.startCrawling();
	
	std::string quary;
	while (quary != "stop")
	{
		quary = welcomeAndAskInput();
		Query q(quary);
		Search s(d);
		auto res = s.executeSearch(q);

		printCrawlResult(d);
		
		uint32_t limitSearchResult = jsonFile.maxPages();
		printSearchResult(q.getTerm(), res, limitSearchResult);
	}
    
}
    
} // namespace se
