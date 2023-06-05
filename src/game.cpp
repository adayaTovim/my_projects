#include <SFML/Graphics.hpp>

#include <iostream>

#include "game.hpp"

namespace arkanoid {


Game::Game() 
: m_window(sf::VideoMode(1280, 720), "Arkanoid!")
, m_gameScreen(sf::Vector2f(1280, 720), m_window)
, m_menuScreen(sf::Vector2f(1280, 720), m_window)
, m_top10Screen(sf::Vector2f(1280, 720), m_window)
, m_inputScreen(sf::Vector2f(1280, 720), m_window)
{   
}

void Game::run() {
    std::vector<std::string> levels = {"level1.json", "level2.json", "level3.json"};
    int levelIndex = 0;

    while (m_window.isOpen()) {
        if (levelIndex == 0) {
            bool gameStarted = m_menuScreen.run();
            if (!gameStarted) {
                m_window.close();
                return;
            }
        }
        auto [time, score, pressEsc] = m_gameScreen.run(levels[levelIndex]);
        if (!pressEsc) {
            if (m_gameScreen.bricksAreEmpty()) {
                if (levelIndex >= 2) {
                    m_gameScreen.drawWin();
                    bool isTop10 = m_top10Screen.isTop10(score, time);
                    if (isTop10) {
                        m_inputScreen.run();
                        std::string WinnerName = m_inputScreen.getInput();
                        m_top10Screen.addTop10(score, time, WinnerName);
                    }
                    levelIndex = 0;
                    bool returnMenu = m_top10Screen.run();
                    if (returnMenu == true) {
                        continue;
                    }
                }
                m_gameScreen.drawLevelUp();
                ++levelIndex;  
            }
        }
        else if (pressEsc) {
            levelIndex = 0;
        }
    }
}

} //arkanoid
