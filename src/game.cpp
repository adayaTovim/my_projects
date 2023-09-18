#include <SFML/Graphics.hpp>

#include <iostream>

#include "game.hpp"

namespace arkanoid {

Game::Game()
: m_window(sf::VideoMode(1280, 720), "Arkanoid!")
, m_currentScreen(nullptr)
{
    m_currentScreen = new MenuScreen(sf::Vector2f(1280, 720), m_window);
}

void Game::setScreen(ScreenState* a_newScreen) {
    m_currentScreen = a_newScreen;
}

void Game::run() {
    std::vector<std::string> levels = {"level1.json", "level2.json", "level3.json"};
    int levelIndex = 0;

	//m_currentScreen = new MenuScreen(sf::Vector2f(1280, 720), m_window);

    while (m_window.isOpen()) {
		setScreen(new MenuScreen(sf::Vector2f(1280, 720), m_window));
        if (levelIndex == 0) {
            auto returnValue = m_currentScreen->run(std::nullopt);
			bool gameStarted = std::get<2>(returnValue.value());
            if (!gameStarted) {
                m_window.close();
                return;
            }
        }
		setScreen(new GameScreen(sf::Vector2f(1280, 720), m_window));
        auto returnValue4 = m_currentScreen->run(levels[levelIndex]);
		int time = std::get<0>(returnValue4.value());
		int score = std::get<1>(returnValue4.value());
		bool pressEsc = std::get<2>(returnValue4.value());

        if (!pressEsc) {
            if (m_currentScreen->bricksAreEmpty()) {
                if (levelIndex >= 2) {
                    m_currentScreen->drawWin();
					setScreen(new Top10Screen(sf::Vector2f(1280, 720), m_window));
                    bool isTop10 = m_currentScreen->isTop10(score, time);
                    if (isTop10) {
						setScreen(new InputScreen(sf::Vector2f(1280, 720), m_window));
                        m_currentScreen->run(std::nullopt);
                        auto WinnerName = m_currentScreen->getInput();

						setScreen(new Top10Screen(sf::Vector2f(1280, 720), m_window));
                        m_currentScreen->addTop10(score, time, WinnerName);
                    }
                    levelIndex = 0;
					setScreen(new Top10Screen(sf::Vector2f(1280, 720), m_window));
                    auto returnValue3 = m_currentScreen->run(std::nullopt);
					bool returnMenu = std::get<2>(returnValue3.value());
                    if (returnMenu == true) {
                        continue;
                    }
                }
				setScreen(new GameScreen(sf::Vector2f(1280, 720), m_window));
                m_currentScreen->drawLevelUp();
                ++levelIndex;
            }
        }
        else if (pressEsc) {
            levelIndex = 0;
        }
    }
}

} //arkanoid
