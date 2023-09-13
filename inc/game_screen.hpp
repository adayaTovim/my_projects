#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "screen.hpp"
#include "ball.hpp"
#include "player.hpp"
#include "brick.hpp"

namespace arkanoid{

using brickVector = std::vector<Brick>;

class GameScreen : public ScreenState{
public:
    explicit GameScreen(sf::Vector2f a_screenSize, sf::RenderWindow& a_window);
    GameScreen(GameScreen const& a_other) = delete;
    GameScreen& operator=(GameScreen const& a_other) = delete;
    ~GameScreen() = default;

    std::tuple<int, int, bool> run(std::string a_level);

    void draw();
    void drawLevelUp();
    void drawWin();
    sf::RectangleShape const& getScreen() const;
    sf::Vector2f const& getPosition() const;
    sf::Vector2f const& getSize() const;

    void handleEvents(bool& a_gameStarted, bool& a_playButton, bool& a_gameOver);
    void handleBall(bool& a_gameOver, bool& a_playButton, bool& a_playerWin);

    bool bricksAreEmpty() const;

private:
    sf::RenderWindow& m_window;
    sf::RectangleShape m_gameScreen;
    Ball m_ball;
    Player m_player;
    brickVector m_bricks;
};


} // arkanoid
