#pragma once

#include <SFML/Graphics.hpp>

#include "screen.hpp"
#include "font.hpp"

namespace arkanoid {

class InputScreen : public ScreenState{
public:
    InputScreen() = delete;
    explicit InputScreen(sf::Vector2f a_screenSize, sf::RenderWindow& a_window);
    InputScreen(InputScreen const& a_other) = delete;
    InputScreen& operator=(InputScreen const& a_other) = delete;
    ~InputScreen() = default;

    std::optional<std::tuple<int, int, bool>> run(std::optional<std::string> a_level);
    std::string getPlayerName(sf::RenderWindow& a_window);
    bool draw();

    std::string getInput() const;

private:
    sf::RenderWindow& m_window;
    Font m_font;
    sf::RectangleShape m_inputScreen;
    sf::Text m_text;
    std::string m_input;
};

} // namespace arkanoid

