#include <sstream> // std::istringstream

#include "query.hpp" // Current header

namespace se {

Query::Query(const std::string& a_term)
: m_queryVec()
, m_term(a_term)
{
	normalizeQuery(a_term);
}

void Query::normalizeQuery(const std::string& a_term)
{
    if (a_term.empty()) {
        return;
    }

    std::string word = a_term;
    word = toLowercase(a_term);

    // stream class that reads from a string
	bool isPositive = true;
    std::istringstream iss(a_term);
    while (iss >> word) {
        if (word.length() < 3 || (!isalpha(word[0]) && word[0] != '-')) {
            continue;
        }
		else if (word[0] == '-') {
			word = word.substr(1, word.size());
			if(word.size() < 3 ) {
				continue;
			}
			isPositive = false;
		}

        m_queryVec.push_back(std::make_pair(word, isPositive));
		isPositive = true;
    }
}

const std::vector<std::pair<std::string, bool>>& Query::getQuery() const {
    return m_queryVec;
}

const std::string& Query::getTerm() const {
    return m_term;
}

}// namespace se

