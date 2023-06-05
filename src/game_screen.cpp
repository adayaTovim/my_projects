#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <jsoncpp/json/json.h>

#include "game_screen.hpp"

namespace arkanoid {

namespace {

std::map<std::string, Brick::BrickColor> colorMap {
        {"red", Brick::BrickColor::RED},
        {"blue", Brick::BrickColor::BLUE},
        {"pink", Brick::BrickColor::PINK},
        {"green", Brick::BrickColor::GREEN},
        {"light_orange", Brick::BrickColor::LIGHT_ORANGE},
        {"dark_orange", Brick::BrickColor::DARK_ORANGE},
        {"light_blue", Brick::BrickColor::LIGHT_BLUE},
        {"white", Brick::BrickColor::WHITE},
        {"gray", Brick::BrickColor::GRAY},
        {"yellow", Brick::BrickColor::YELLOW}
};

brickVector initializeBricks(const std::string& a_fileName)
{
    brickVector bricks;
    std::ifstream file("json/" + a_fileName);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open file " << a_fileName << std::endl;
        return bricks;
    }

    Json::Value json;
    file >> json;

    const auto& bricksJson = json["bricks"];

    for (const auto& brickJson : bricksJson) {
        const std::string color = brickJson["color"].asString();
        const auto i = brickJson["i"].asInt();
        const auto j = brickJson["j"].asInt();

        // Create a new Brick object and add it to the vector of bricks
        Brick::BrickColor brickColor = colorMap[color];
        const auto brickPos = sf::Vector2f(j * 150 + 250, i * 30 + 200);
        arkanoid::Brick newBrick(brickPos, brickColor);
        bricks.push_back(newBrick);
    }
    return bricks;
}

} // namespace


GameScreen::GameScreen(sf::Vector2f a_screenSize, sf::RenderWindow& a_window) 
: m_window(a_window)
, m_gameScreen(a_screenSize)
, m_ball(0.2,0.7)
, m_player(sf::Vector2f(0,0), 3)
, m_bricks()
{
    m_gameScreen.setFillColor(sf::Color(198, 179, 179));
    m_gameScreen.setOutlineThickness(1.f);
    m_gameScreen.setOutlineColor(sf::Color::Black);
    m_gameScreen.setPosition(0, 0);
}

std::tuple<int, int, bool> GameScreen::run(std::string a_level) {
    bool gameStarted = false; 
    bool gameOver = false;
    bool playButton = true;
    bool playerWin = false;

    m_ball.resetPosition();
    m_player.resetGame();
    m_bricks = initializeBricks(a_level);

    while (m_window.isOpen()) {
        handleEvents(gameStarted, playButton, gameOver);
        if(playButton == false) {
            break;
        }
        if (playButton && !playerWin) {
            if (gameStarted && !gameOver && playButton) { 
                handleBall(gameOver, playButton, playerWin);
                m_player.update(); 
                if (playerWin == true) {
                    break;
                }
            }
            
        }
        draw();
    }
    return std::make_tuple(m_player.getTime(), m_player.getScore(), playButton);
}

void GameScreen::draw() {
    m_window.clear();
    
    m_window.draw(m_gameScreen);
    m_player.draw(m_window);
    m_ball.draw(m_window);
    m_window.draw(m_ball.getBall());
    
    for (auto const& brick : m_bricks) {
        brick.draw(m_window);
    }

    m_window.display();
}

void GameScreen::handleEvents(bool& a_gameStarted, bool& a_playButton, bool& a_gameOver) 
{
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            a_playButton = false;
            a_gameOver = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_player.getPosition().x > 10) {
            m_player.move(-20, 0);
            if (!a_gameStarted) {
                m_ball.setPosition(m_ball.getPosition().x - 20, m_ball.getPosition().y);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_player.getPosition().x < 1145) {
            m_player.move(20, 0);
            if (!a_gameStarted) {
                m_ball.setPosition(m_ball.getPosition().x + 20, m_ball.getPosition().y);
            }
        }

        if (!a_gameStarted && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { 
            a_gameStarted = true;
        }
    }
}

void GameScreen::handleBall(bool& a_gameOver, bool& a_playButton, bool& a_playerWin) 
{
    m_ball.setPosition(m_ball.getPosition().x + m_ball.getXVelocity(), m_ball.getPosition().y + m_ball.getYVelocity());

    // Check for collision with board boundaries
    if(m_ball.getPosition().x < 0 || m_ball.getPosition().x > 1280 -30) {
        m_ball.setXVelocity(m_ball.getXVelocity() * (-1));
    }

    if(m_ball.getPosition().y < 0) {
        m_ball.setYVelocity(m_ball.getYVelocity() * (-1));
    }

    if(m_ball.getPosition().y > 720 - 30) {
        m_ball.setYVelocity(m_ball.getYVelocity() * (-1));
        m_player.updateLives(-1);
        if(m_player.getLives() == 0) {
            m_player.draw(m_window);
            m_window.display(); 
            sf::sleep(sf::seconds(5)); 
            
            a_gameOver = true;
            a_playButton = false;
        }
    }
    
    if(m_ball.getBounds().intersects(m_player.getBounds())) {
        m_ball.setYVelocity(m_ball.getYVelocity() * (-1));
    }

    // Check for collision with bricks
    for (size_t i = 0; i < m_bricks.size(); ++i) {
        if (m_bricks[i].getBounds().intersects(m_ball.getBounds())) {
            m_ball.setYVelocity(m_ball.getYVelocity() * (-1));

            if (!m_bricks[i].isUnbreakable()) { // Check if brick is not unbreakable
                int points = m_bricks[i].getPointValue(); // Pass the color of the brick to get the point value
                m_bricks.erase(m_bricks.begin() + i); // Remove brick
                m_player.updateScore(points);
            }
            if(bricksAreEmpty()) {
                m_player.draw(m_window);
                m_window.display(); 
                m_player.draw(m_window);
                m_window.display(); 
                a_playerWin = true;
                a_playButton = false;
            }
        }
    }
}

bool GameScreen::bricksAreEmpty() const 
{
    for (const auto& brick : m_bricks) {
        if (!brick.isUnbreakable()) {
            return false;
        }
    }
    return true;
}

sf::RectangleShape const& GameScreen::getScreen() const 
{
    return m_gameScreen;
}

sf::Vector2f const& GameScreen::getPosition() const 
{
    return m_gameScreen.getPosition();
}

sf::Vector2f const& GameScreen::getSize() const 
{
    return m_gameScreen.getSize();
}


void GameScreen::drawLevelUp() {
    m_player.drawLevelUp(m_window);
    m_window.display();
    sf::sleep(sf::seconds(5)); 

}

void GameScreen::drawWin() {
    m_player.drawWin(m_window);
    m_window.display();
    sf::sleep(sf::seconds(5)); 

}

} // namespace arkanoid