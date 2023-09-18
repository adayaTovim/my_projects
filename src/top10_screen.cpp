#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>

#include "top10_screen.hpp"

namespace arkanoid {

namespace {

sf::RectangleShape createReturnButton(sf::Vector2f const& a_screenSize)
{
    sf::RectangleShape button(sf::Vector2f(200, 50));
    button.setFillColor(sf::Color::Black);
    button.setOutlineThickness(2.f);
    button.setOutlineColor(sf::Color::White);
    button.setPosition(540, 620);

    return button;
}

void drawButtonText(sf::RenderTarget& a_target)
{
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Error: Failed to load font 'arial.ttf'" << std::endl;
    }
    sf::Text headerText("Return", font, 30);
    headerText.setFillColor(sf::Color::White);
    headerText.setOutlineColor(sf::Color::Black);
    headerText.setOutlineThickness(2);
    headerText.setStyle(sf::Text::Bold);
    headerText.setPosition(635, 635);
    headerText.setOrigin(headerText.getLocalBounds().width / 2, headerText.getLocalBounds().height / 2);

    a_target.draw(headerText);
}

void drawHeaderText(sf::RenderTarget& a_target)
{
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Error: Failed to load font 'arial.ttf'" << std::endl;
    }
    sf::Text headerText("Top 10 Scores", font, 50);
    headerText.setFillColor(sf::Color::White);
    headerText.setOutlineColor(sf::Color(255, 0, 102));
    headerText.setOutlineThickness(2);
    headerText.setStyle(sf::Text::Bold);
    headerText.setPosition(650, 100);
    headerText.setOrigin(headerText.getLocalBounds().width / 2, headerText.getLocalBounds().height / 2);

    a_target.draw(headerText);
}

std::vector<Winner> readFromFile(){
    std::ifstream file("top10.txt");
    if (!file) {
        std::cerr << "Error opening file1" << std::endl;
    }
    std::vector<Winner> winners;
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream str(line);
        std::string name;
        size_t points;
        float time;
        str >> name >> points >> time;
        int timeInSeconds = static_cast<int>(sf::seconds(time).asSeconds());
        winners.push_back(Winner(points, timeInSeconds, name));
    }
    file.close();
    return winners;
}

void drawScoreTexts(sf::RenderTarget& a_target, sf::Vector2f a_scorePosition)
{
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Error: Failed to load font 'arial.ttf'" << std::endl;
    }

    std::vector<sf::Text> scoreTexts(10, sf::Text("", font, 32));

    std::vector<Winner> scores = readFromFile();

    // Set the position and size of each score text
    for (std::vector<Winner>::size_type i = 0; i < scores.size() && i < 10; i++)
    {
        std::string name = scores[i].getName();
        int score = scores[i].getScore();
        int time = scores[i].getTime() ;

        scoreTexts[i].setPosition(a_scorePosition.x / 2, 150 + i * 40);
        scoreTexts[i].setOrigin(scoreTexts[i].getLocalBounds().width / 2, scoreTexts[i].getLocalBounds().height / 2);
        scoreTexts[i].setString("      " + name + " score: " + std::to_string(score)+ " time: " + std::to_string(time));
        a_target.draw(scoreTexts[i]);
    }
}

} // namespace

Top10Screen::Top10Screen(sf::Vector2f a_screenSize, sf::RenderWindow& a_window)
: m_window(a_window)
, m_font()
, m_top10Screen(a_screenSize)
, m_returnButton(createReturnButton(a_screenSize))
, m_top10(readFromFile())
{
    m_top10Screen.setFillColor(sf::Color(198, 179, 179));
    m_top10Screen.setOutlineThickness(1.f);
    m_top10Screen.setOutlineColor(sf::Color::Black);
    m_top10Screen.setPosition(0, 0);

}

std::optional<std::tuple<int, int, bool>> Top10Screen::run(std::optional<std::string> a_level) {
    while (m_window.isOpen()) {
        if (draw()) {
            return std::make_tuple(0, 0, true);
        }
    }
    return std::make_tuple(0, 0, false);
}

bool Top10Screen::draw()
{
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
                sf::FloatRect returnButton = getBoundReturnButton();
                if (returnButton.contains(mousePos.x, mousePos.y)) {
                    return true;
                }
            }
        }
    }
	m_window.clear();
    m_window.draw(m_top10Screen);

    m_window.draw(m_returnButton);
    drawHeaderText(m_window);
    drawButtonText(m_window);

    sf::Vector2f scorePosition(m_top10Screen.getPosition().x + m_top10Screen.getSize().x / 2, m_top10Screen.getPosition().y + m_top10Screen.getSize().y / 2 - m_returnButton.getSize().y + 20);
    drawScoreTexts(m_window, scorePosition);

    //m_window.clear();
    m_window.display();

    return false;
}

void Top10Screen::saveToFile() const {
    std::ofstream file("top10.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
    }
    for (size_t i = 0; i < m_top10.size(); ++i) {
        file << m_top10[i].getName() << " " << m_top10[i].getScore() << " " << m_top10[i].getTime() << "\n";
    }
    file.close();
}

bool Top10Screen::isTop10(int a_score, int a_time) const
{
    if (m_top10.empty()) {
        return true;
    }

    if (m_top10.size() < NUM_SCORES) {
        return true;
    }

    else {
        // compare the new score with the last element of m_top10
        const Winner last = m_top10.back();

        if (a_score > last.getScore()) {
            return true;
        }

        else if (a_score == last.getScore()) {
            // if the scores are the same, compare the times
            if (a_time < last.getTime()) {
                return true;
            }
        }
    }

    return false;
}


void Top10Screen::addTop10(int a_score, int a_time, const std::string& a_name)
{
    Winner winner(a_score, a_time, a_name);

    if (isTop10(a_score, a_time)) {
        if (m_top10.size() >= NUM_SCORES) {
            m_top10.pop_back();
        }
        m_top10.push_back(winner);
        sortScores();
        saveToFile();
    }
}


void Top10Screen::sortScores()
{
    std::sort(m_top10.rbegin(), m_top10.rend(), [](const auto& a, const auto& b) {
        if (a.getScore() != b.getScore()) {
            return a.getScore() < b.getScore();
        }
        return a.getTime() > b.getTime();
    });
}


const std::vector<Winner>& Top10Screen::getScores() const
{
    return m_top10;
}

sf::FloatRect Top10Screen::getBoundReturnButton() const
{
    return m_returnButton.getGlobalBounds();
}

} //arkanoid
