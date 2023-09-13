#include <iostream>

#include "menu_screen.hpp"

namespace arkanoid {

namespace {

// sf::RectangleShape initscreen(sf::Vector2f a_screenSize) {
//     sf::RectangleShape rectangle(a_screenSize);
//     //sf::Texture texture;
//     // if (!texture.loadFromFile("texture1.png")) {
//     //     std::cerr << "Error: Failed to load 'texture1.png'" << std::endl;
//     // }
//     //rectangle.setTexture(&texture);
//     rectangle.setFillColor(sf::Color(198, 179, 179));
//     rectangle.setOutlineThickness(1.f);
//     rectangle.setOutlineColor(sf::Color::Black);
//     rectangle.setPosition(0, 0);
//     return rectangle;
// }

sf::RectangleShape createPlayButton(sf::Vector2f const& a_screenSize)
{
    sf::RectangleShape button(sf::Vector2f(200, 50));
    button.setFillColor(sf::Color::Black);
    button.setOutlineThickness(2.f);
    button.setOutlineColor(sf::Color::White);
    button.setPosition(a_screenSize.x / 2 - button.getSize().x / 2, a_screenSize.y / 2 - button.getSize().y);

    return button;
}


sf::RectangleShape createExitButton(sf::Vector2f const& a_screenSize)
{
    sf::RectangleShape button(sf::Vector2f(200, 50));
    button.setFillColor(sf::Color::Black);
    button.setOutlineThickness(2.f);
    button.setOutlineColor(sf::Color::White);
    button.setPosition(a_screenSize.x / 2 - button.getSize().x / 2, a_screenSize.y / 2 + 50);

    return button;
}

void drawTexts(sf::RenderTarget& a_target, sf::Vector2f a_playPosition, sf::Vector2f a_exitPosition, sf::Vector2f a_welcomePosition) {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Error: Failed to load font 'arial.ttf'" << std::endl;
    }
    sf::Text playText("PLAY", font, 24);
    playText.setFillColor(sf::Color::White);
    playText.setStyle(sf::Text::Bold);
    playText.setOrigin(playText.getLocalBounds().width / 2, playText.getLocalBounds().height / 2);
    playText.setPosition(a_playPosition);


    sf::Text exitText("EXIT", font, 24);
    exitText.setFillColor(sf::Color::White);
    exitText.setStyle(sf::Text::Bold);
    exitText.setOrigin(exitText.getLocalBounds().width / 2, exitText.getLocalBounds().height / 2);
    exitText.setPosition(a_exitPosition);

    sf::Text welcomeText("ARKANOID GAME!", font, 70);
    welcomeText.setFillColor(sf::Color::Black);
    welcomeText.setStyle(sf::Text::Bold);
    welcomeText.setOrigin(welcomeText.getLocalBounds().width / 2, exitText.getLocalBounds().height / 2);
    welcomeText.setPosition(a_welcomePosition);

    a_target.draw(playText);
    a_target.draw(exitText);
    a_target.draw(welcomeText);
}

} // namespace


MenuScreen::MenuScreen(sf::Vector2f a_screenSize, sf::RenderWindow& a_window)
: m_window(a_window)
, m_font()
, m_menuScreen(a_screenSize)
, m_playButton(createPlayButton(a_screenSize))
, m_exitButton(createExitButton(a_screenSize))
{
    m_menuScreen.setFillColor(sf::Color(198, 179, 179));
    m_menuScreen.setOutlineThickness(1.f);
    m_menuScreen.setOutlineColor(sf::Color::Black);
    m_menuScreen.setPosition(0, 0);
}


std::optional<std::tuple<int, int, bool>> MenuScreen::run() {
    while (m_window.isOpen()) {
        if (draw()) {
            return std::make_tuple(0, 0, true);
        }
    }
    return std::make_tuple(0, 0, false);
}


bool MenuScreen::draw()
{
    sf::Event event;
		while (m_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				m_window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
					sf::FloatRect startButtonBounds = getPlayBounding();
					sf::FloatRect exitButtonBounds = getExitBounding();

					if (startButtonBounds.contains(mousePos.x, mousePos.y)) {
						return true;
					}
					else if (exitButtonBounds.contains(mousePos.x, mousePos.y)) {
						m_window.close();
					}
				}
			}
		}

    sf::Vector2f playPosition(m_menuScreen.getPosition().x + m_menuScreen.getSize().x / 2, m_menuScreen.getPosition().y + m_menuScreen.getSize().y / 2 - m_playButton.getSize().y + 20);
    sf::Vector2f exitPosition(m_menuScreen.getPosition().x + m_menuScreen.getSize().x / 2, m_menuScreen.getPosition().y + m_menuScreen.getSize().y / 2 + 70);
    sf::Vector2f welcomePosition(m_menuScreen.getPosition().x + m_menuScreen.getSize().x / 2, m_menuScreen.getPosition().y + m_menuScreen.getSize().y / 4);

    m_window.clear();
    m_window.draw(m_menuScreen);
    m_window.draw(m_playButton);
    m_window.draw(m_exitButton);
    drawTexts(m_window, playPosition, exitPosition, welcomePosition);
    m_window.display();

    return false;
}


sf::FloatRect MenuScreen::getBoundsPlayButton() const
{
    return m_playButton.getGlobalBounds();
}

sf::FloatRect MenuScreen::getBoundsExitButton() const
{
    return m_exitButton.getGlobalBounds();
}

sf::FloatRect MenuScreen::getPlayBounding() const noexcept
{
    return m_playButton.getGlobalBounds();
}

sf::FloatRect MenuScreen::getExitBounding() const noexcept
{
    return m_exitButton.getGlobalBounds();
}


} // namespace arkanoid
