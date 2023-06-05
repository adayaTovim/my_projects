#pragma once

#include <SFML/Graphics.hpp>

#include "game_screen.hpp"
#include "menu_screen.hpp"
#include "top10_screen.hpp"
#include "screen.hpp"
#include "input_screen.hpp"

namespace arkanoid {

using brickArray = std::array<std::array<Brick, 5>, 3>;

class Game{
public:
    Game();
    Game(Game const& a_other) = delete;
    Game& operator=(Game const& a_other) = delete;
    ~Game() = default;

    void processEvents();
    void run();

private:
    sf::RenderWindow m_window;
    GameScreen m_gameScreen;
    MenuScreen m_menuScreen;
    Top10Screen m_top10Screen;
    InputScreen m_inputScreen;
};

} // arkanoid
