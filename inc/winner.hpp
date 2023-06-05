#pragma once

#include <string>

namespace arkanoid {

class Winner {
public:
    Winner();
    Winner(int score, int time, std::string name);
    
    int getScore() const;
    int getTime() const;
    std::string getName() const;
    
    void setScore(int score);
    void setTime(int time);
    void setName(std::string name);


private:
    int m_score;
    int m_time;
    std::string m_name;
};

} // namespace arkanoid
