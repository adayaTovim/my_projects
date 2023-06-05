#include <iostream>

#include "player.hpp"
#include "paddle.hpp"

namespace arkanoid {

namespace {

void drawScoresAndLives(sf::RenderTarget& a_target, int a_score, int a_lives) {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Error: Failed to load font 'arial.ttf'" << std::endl;
    }
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Score: " + std::to_string(a_score));
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setStyle(sf::Text::Bold);
    scoreText.setPosition(1050, 120);
    a_target.draw(scoreText);

    sf::Text livesText;
    livesText.setFont(font);
    livesText.setString("Lives: " + std::to_string(a_lives));
    livesText.setCharacterSize(24);
    livesText.setFillColor(sf::Color::Black);
    livesText.setStyle(sf::Text::Bold);
    livesText.setPosition(1050, 90);
    a_target.draw(livesText);
}

void drawTimeRun(sf::RenderTarget& a_target, const sf::Time& a_timeRun) {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Error: Failed to load font 'arial.ttf'" << std::endl;
    }
    sf::Text timeRun;
    timeRun.setFont(font);
    timeRun.setString("Time: " + std::to_string(a_timeRun.asSeconds()));
    timeRun.setCharacterSize(24);
    timeRun.setFillColor(sf::Color::Black);
    timeRun.setStyle(sf::Text::Bold);
    timeRun.setPosition(1050, 150);
    a_target.draw(timeRun);
}

void drawGameOver(sf::RenderTarget& a_target) {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Error: Failed to load font 'arial.ttf'" << std::endl;
    }
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("Game Over!");
    gameOverText.setCharacterSize(70);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setOutlineColor(sf::Color::Black);
    gameOverText.setOutlineThickness(2);
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setPosition(450, 300);
    a_target.draw(gameOverText);  
}

} // namespace

Player::Player(sf::Vector2f a_position, int a_lives)
: m_paddle(5)
, m_score(0)
, m_lives(3)
, m_timeRun(sf::seconds(0))
{
}

void Player::move(float x, float y) {
    m_paddle.move(x, y);
}

void Player::update() {
    m_timeRun = m_clock.getElapsedTime();
}

void Player::draw(sf::RenderTarget& a_target) const {
    m_paddle.draw(a_target); 

    drawScoresAndLives(a_target, m_score, m_lives);
    drawTimeRun(a_target, m_timeRun);

    if(m_lives == 0) {
        drawGameOver(a_target);
    }

}


void Player::drawWin(sf::RenderTarget& a_target) {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Error: Failed to load font 'arial.ttf'" << std::endl;
    }
    sf::Text winText;
    winText.setFont(font);
    winText.setString("You Win!");
    winText.setCharacterSize(150);
    winText.setFillColor(sf::Color::White);
    winText.setOutlineColor(sf::Color::Black);
    winText.setOutlineThickness(2);
    winText.setStyle(sf::Text::Bold);
    winText.setPosition(380, 230);
    a_target.draw(winText);  
}

void Player::drawLevelUp(sf::RenderTarget& a_target) {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Error: Failed to load font 'arial.ttf'" << std::endl;
    }
    sf::Text levelUpText;
    levelUpText.setFont(font);
    levelUpText.setString("level up!");
    levelUpText.setCharacterSize(70);
    levelUpText.setFillColor(sf::Color::White);
    levelUpText.setOutlineColor(sf::Color::Black);
    levelUpText.setOutlineThickness(2);
    levelUpText.setStyle(sf::Text::Bold);
    levelUpText.setPosition(510, 280);
    a_target.draw(levelUpText);  
}

sf::Vector2f Player:: getPosition() const {
   return m_paddle.getPosition();
}

void Player::updateScore(int points) {
    m_score += points;
}

void Player::updateLives(int lives) {
    m_lives += lives;
}

int Player::getScore() const {
    return m_score;
}

int Player::getLives() const {
    return m_lives;
}

int Player::getTime() const {
    return m_timeRun.asMilliseconds();
}

sf::FloatRect Player::getBounds() const {
    return m_paddle.getBounds();
}

void Player::setPaddlePos(float x, float y) {
    m_paddle.move(x, y);
}

void Player::resetGame() {
    m_score = 0;
    m_lives = 3;
    m_paddle.resetPaddle();
    m_timeRun = sf::Time::Zero;
    m_clock.restart();     
}


} // namespace arkanoid