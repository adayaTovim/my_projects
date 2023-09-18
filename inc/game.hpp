#pragma once

#include <SFML/Graphics.hpp>

#include "screen.hpp"
#include "game_screen.hpp"
#include "menu_screen.hpp"
#include "top10_screen.hpp"
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
	void setScreen(ScreenState* a_newScreen);

private:
    sf::RenderWindow m_window;
	ScreenState* m_currentScreen;
};

} // arkanoid
