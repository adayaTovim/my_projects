#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <unordered_set>

#include "query.hpp"
#include "isearch.hpp"

namespace se {

//tuple of : title, url , counter
using QueryResult = std::vector<std::tuple<std::string, std::string, uint32_t>> ;
using PositiveResults = std::unordered_map<std::string, std::tuple<std::string, uint32_t, uint32_t>> ;//first counter is wordCounter, second is times to insert to the map

class Search {
public:
    Search() = delete;
    explicit Search(ISearch& a_searcher);

    QueryResult executeSearch(Query const& a_query) const;

private:
    uint32_t fillResultsMaps(PositiveResults& a_positive, std::unordered_set<std::string>& a_negative, std::vector<std::pair<std::string, bool>>& a_terms) const;

private:
    ISearch& m_searcher;
};

} // namespace s

