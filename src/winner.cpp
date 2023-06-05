#include "winner.hpp"

namespace arkanoid {

Winner::Winner() 
: m_score(0)
, m_time(0)
, m_name("") 
{
}

Winner::Winner(int a_score, int a_time, std::string a_name) 
: m_score(a_score)
, m_time(a_time)
, m_name(a_name) 
{
}

int Winner::getScore() const 
{
    return m_score;
}

int Winner::getTime() const 
{
    return m_time;
}

std::string Winner::getName() const 
{
    return m_name;
}

void Winner::setScore(int a_score) 
{
    m_score = a_score;
}

void Winner::setTime(int a_time) 
{
    m_time = a_time;
}

void Winner::setName(std::string a_name) 
{
    m_name = a_name;
}



} // namespace arkanoid
