#pragma once

#include <string> // std::string
#include <vector> // std::vector
#include <utility> // std::pair

#include "string_utils.hpp"

namespace se {

class Query {
public:
    Query() = delete;
    explicit Query(const std::string& a_term);
    Query(Query const& a_other) = default;
    Query& operator=(const Query& a_other) = default;
    ~Query() = default;

    const std::vector<std::pair<std::string, bool>>& getQuery() const;
	const std::string& getTerm() const;

private:
    void normalizeQuery(const std::string& a_term);

private:
    std::vector<std::pair<std::string, bool>> m_queryVec;
    const std::string& m_term;
};

} // namespace se

