#pragma once

#include <SFML/Graphics.hpp>

#include "screen.hpp"
#include "font.hpp"

namespace arkanoid{

class MenuScreen : public ScreenState{
public:
    MenuScreen() = delete;
    explicit MenuScreen(sf::Vector2f a_screenSize, sf::RenderWindow& a_window);
    MenuScreen(MenuScreen const& a_other) = delete;
    MenuScreen& operator=(MenuScreen const& a_other) = delete;
    ~MenuScreen() = default;


    std::optional<std::tuple<int, int, bool>>  run(std::optional<std::string> a_level);
    bool draw();

    sf::FloatRect getBoundsPlayButton() const;
    sf::FloatRect getBoundsExitButton() const;
    sf::FloatRect getPlayBounding() const noexcept;
    sf::FloatRect getExitBounding() const noexcept;

private:
    sf::RenderWindow& m_window;
    Font m_font;
    sf::RectangleShape  m_menuScreen;
    sf::RectangleShape m_playButton;
    sf::RectangleShape m_exitButton;
};

} // arkanoid

