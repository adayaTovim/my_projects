#pragma once

#include <SFML/Graphics.hpp>

#include "screen.hpp"
#include "font.hpp"
#include "winner.hpp"

namespace arkanoid {
    
static const int NUM_SCORES = 10;

class Top10Screen  {
public:
    Top10Screen() = delete;
    explicit Top10Screen(sf::Vector2f a_screenSize, sf::RenderWindow& a_window);
    Top10Screen(Top10Screen const& a_other) = delete;
    Top10Screen& operator=(Top10Screen const& a_other) = delete;
    ~Top10Screen() = default;

    bool run();
    bool draw();

    bool isTop10(int a_score, int a_time) const;
    void addTop10(int a_score, int a_time, const std::string& a_name);
    void sortScores();
    const std::vector<Winner>& getScores() const;

    sf::RectangleShape const& getScreen() const;
    sf::FloatRect getBoundReturnButton() const;
    void saveToFile() const;

private:
    sf::RenderWindow& m_window;
    Font m_font;
    sf::RectangleShape m_top10Screen;
    sf::Text m_headerText;
    sf::RectangleShape m_returnButton;
    std::vector<Winner> m_top10;
};

} //arkanoid