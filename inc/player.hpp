#pragma once

#include <SFML/Graphics.hpp>
#include "paddle.hpp"

namespace arkanoid {

class Player{
public:
    Player();
    explicit Player(sf::Vector2f a_position, int a_live = 3);
    Player(const Player& a_other) = default;
    Player& operator=(const Player& a_other) = default;
    ~Player() = default;

    void move(float x, float y);
    void draw(sf::RenderTarget& a_target) const;
    void drawWin(sf::RenderTarget& a_target);
    void drawLevelUp(sf::RenderTarget& a_target);
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;

    void updateScore(int points);
    void updateLives(int lives);
    void setPaddlePos(float x, float y);
    void resetGame();

    int getScore() const;
    int getLives() const;
    int getTime() const;
    void update();

private:
    Paddle m_paddle;
    int m_score;
    int m_lives;
    sf::Clock m_clock;
    sf::Time m_timeRun;
};

} //arkanoid