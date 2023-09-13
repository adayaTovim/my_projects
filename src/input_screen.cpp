#include <iostream>

#include "input_screen.hpp"

namespace arkanoid {

namespace {

void drawTexts(sf::RenderTarget& a_target) {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Error: Failed to load font 'arial.ttf'" << std::endl;
    }
    sf::Text text("Enter Your Name : ", font, 30);
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);
    text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
    text.setPosition(600, 250);

    a_target.draw(text);
}

bool ifDirty(bool& a_flag, std::string const& a_input)
{
	if (!a_input.empty()) {
		a_flag = true;
		return true;
	}
	a_flag = false;
	return false;
}

} // namespace

InputScreen::InputScreen(sf::Vector2f a_screenSize, sf::RenderWindow& a_window)
    : m_window(a_window)
    , m_font()
    , m_inputScreen(a_screenSize)
    , m_text("", m_font.get())
    , m_input()
{
    m_inputScreen.setFillColor(sf::Color(198, 179, 179));
    m_inputScreen.setOutlineThickness(1.f);
    m_inputScreen.setOutlineColor(sf::Color::Black);
    m_inputScreen.setPosition(0, 0);

    m_text.setPosition(750, 242);
	m_text.setFillColor(sf::Color::White);
    m_text.setCharacterSize(25);

}

std::optional<std::tuple<int, int, bool>> InputScreen::run(std::optional<std::string> a_level)
{
    while (m_window.isOpen()) {
        if (draw()) {
            return std::make_tuple(0, 0, true);
        }
    }
	return std::make_tuple(0, 0, false);
}

bool InputScreen::draw()
{
    sf::Event event;

	bool end = false;
	bool inputUpdated = false;

	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			// return a status from this function
			m_window.close();
		}
		if (event.type == sf::Event::TextEntered) {
			if (std::isprint(event.text.unicode) && m_input.length() < 11) {
				m_input += event.text.unicode;
			}
		}
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::BackSpace) {
				if (ifDirty(inputUpdated, m_input)) {
					m_input.pop_back();
				}
			}
			if (event.key.code == sf::Keyboard::Enter && ifDirty(inputUpdated, m_input)) {
				end = true;
			}
		}
	}
	m_window.clear();
	m_window.draw(m_inputScreen);
    drawTexts(m_window);

	ifDirty(inputUpdated, m_input);

	if(inputUpdated) {
		m_text.setString(m_input);
		m_window.draw(m_text);
	}
	m_window.display();

	return end;
}

std::string const& InputScreen::getInput() const {
    return m_input;
}


} // namespace arkanoid
