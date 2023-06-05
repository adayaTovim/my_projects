#include <stdexcept>
#include <algorithm>
#include <utility>

#include "search.hpp"

namespace se {

namespace {

void removeNegative(PositiveResults& a_positive, std::unordered_set<std::string>& a_negative)
{
    //leave in positive uncommen urls
    auto itNeg = a_negative.begin();
    while(itNeg != a_negative.end()) {
        auto url = *itNeg;
        if (a_positive.find(url) != a_positive.end()) {
            //found common url in map, delete it
            a_positive.erase(url);
        } else {
            ++itNeg;
        }
    }
}

void removeNonSharedUrls(PositiveResults& a_positive, uint32_t a_numOfwords)
{
    //remove all urls that not equal to the number of words
    auto it = a_positive.begin();
    while(it != a_positive.end()) {
        const auto& tuple = it->second;
        const auto& numWords = std::get<2>(tuple);

        if (numWords != a_numOfwords) {
            it = a_positive.erase(it); // Remove the entry
        } else {
            ++it; // Move to the next entry
        }
    }
}

void sortResults(PositiveResults& a_results, QueryResult& a_finalResults)
{
    //go over the results and insert just the index(url) and tuple value.<0>(title) and tuple value.<1>(wordCounter) to the QueryResult vec sorted by the wordCounter (tuple value.<1>)

    // Iterate over the results map and store the a_finalResults
    for (const auto& entry : a_results)
    {
        const std::string& url = entry.first;
        const auto& tuple = entry.second;
        const std::string& title = std::get<0>(tuple);
        const uint32_t wordCounter = std::get<1>(tuple);

        a_finalResults.emplace_back(std::make_tuple(title, url, wordCounter));
    }

    // Sort the a_finalResults vec based on the word counter (tuple get<2>)in ascending order
    std::sort(a_finalResults.begin(), a_finalResults.end(), [](const auto& tuple1, const auto& tuple2) {
                            return std::get<2>(tuple1) > std::get<2>(tuple2);
                        });
}

} // namespace

Search::Search(ISearch& a_searcher)
: m_searcher(a_searcher)
{
}


uint32_t Search::fillResultsMaps(PositiveResults& a_positive, std::unordered_set<std::string>& a_negative, std::vector<std::pair<std::string, bool>>& a_terms) const
{
    QueryResult resultVecOfTuple;
	uint32_t counterPositive = 0;

    auto it = a_terms.begin();
    while (it != a_terms.end()) {
        std::string& word = it->first;
        bool isPositive = it->second;
        resultVecOfTuple = m_searcher.getWordData(word);
		if(isPositive) {
			++counterPositive;
		}
        for (const auto& resultTuple : resultVecOfTuple) {
            const std::string& title = std::get<0>(resultTuple);
            const std::string& url = std::get<1>(resultTuple);
            const uint32_t counter = std::get<2>(resultTuple);

            if (isPositive) {
                auto urlInMap = a_positive.find(url);
                if (urlInMap != a_positive.end()) {
                    // URL already in the map - update the counter by adding the current counter
                    std::get<1>(urlInMap->second) += counter;
                    ++std::get<2>(urlInMap->second);
                } else {
                     // URL not in the map
                    a_positive.insert({ url, { title, counter, 1 } });
                }
            } else {
                a_negative.insert(url);
            }
        }
        ++it;
    }

	return counterPositive;
}

QueryResult Search::executeSearch(Query const& a_query) const
{
    PositiveResults positive;
    std::unordered_set<std::string> negative;
    QueryResult finalResults;
    std::vector<std::pair<std::string, bool>> terms = a_query.getQuery();
    uint32_t numOfWords = terms.size();

    if (numOfWords > 1) {
        uint32_t numPositiveWords = fillResultsMaps(positive, negative, terms);
        removeNonSharedUrls(positive, numPositiveWords);

		if(negative.size() > 0) {
        	removeNegative(positive, negative);
		}

        sortResults(positive, finalResults);

    } else {
        finalResults = m_searcher.getWordData(terms[0].first);
    }

    return finalResults;
}
} // namespace se


