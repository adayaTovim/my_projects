
#include <iostream>
#include <vector>

#include "ui.hpp"
#include "isearch.hpp"

namespace se {

std::string welcomeAndAskInput() {
    std::cout << GREEN_COLOR << "Welcome to SEEK SQUAD!" << RESET_COLOR << "\n";
    std::string query = getInput("Please enter your query: ");
    return query;
}

std::string getInput(const std::string& a_inputReuest) {
    std::string input;
    std::cout << a_inputReuest << "\n";
    std::getline(std::cin, input);
    std::cout << "\n";
    return input;
}

void printSearchResult(const std::string& a_term, const QueryResult& a_vec, uint32_t a_limitResults) 
{
    if(a_vec.empty()) {
        std::cout << RED_COLOR << a_term << " is not found!" << RESET_COLOR << std::endl;
        return;
    }

	if(a_limitResults == 0) {
		a_limitResults = a_vec.size();
    }

    std::cout << GREEN_COLOR << "Search results for: " << RESET_COLOR << a_term << " \n\n";
	for (const auto& tuple : a_vec) {
		if (a_limitResults == 0) {
			break;
        }
		std::cout << "Page title: " << std::get<0>(tuple) << "\nPage Link: " << std::get<1>(tuple) << "\n\n";
		--a_limitResults;
	}
}

void printCrawlResult(const ISearch& a_searcher) 
{
    std::cout << GREEN_COLOR << "Crawl Result:" << RESET_COLOR << " \n\n";
    std::cout << "Count of words indexed: " << a_searcher.getWordsNumber() << " \n\n";
    std::cout << "Count of unique pages visited:" << a_searcher.getVisitedLinksCounter() << " \n\n";
    std::cout << "Total number of links on visited pages which get ignored:" << a_searcher.getExternalLinksCounter() << " \n\n";
}

} // namespace se

