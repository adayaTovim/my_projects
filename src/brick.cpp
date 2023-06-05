#include "brick.hpp"

namespace arkanoid {

namespace {

const std::map<Brick::BrickColor, std::pair<int, sf::Color>> breakMap = 
{
    { Brick::BrickColor::RED, { 90, sf::Color(191, 63, 63) } },
    { Brick::BrickColor::BLUE, { 100, sf::Color(63, 63, 191) } },
    { Brick::BrickColor::PINK, { 110, sf::Color(191, 144, 191) } },
    { Brick::BrickColor::GREEN, { 80, sf::Color(63, 191, 63) } },
    { Brick::BrickColor::LIGHT_ORANGE, { 120, sf::Color(191, 159, 63) } },
    { Brick::BrickColor::DARK_ORANGE, { 60, sf::Color(191, 95, 0) } },
    { Brick::BrickColor::LIGHT_BLUE, { 70, sf::Color(63, 159, 191) } },
    { Brick::BrickColor::WHITE, { 40, sf::Color(191, 191, 191) } },
    { Brick::BrickColor::GRAY, { 50, sf::Color(96, 96, 96) } },
    { Brick::BrickColor::YELLOW, { 0, sf::Color(191, 191, 63) } }
};

} // namespace

Brick::Brick(sf::Vector2f a_position, BrickColor a_color)
: m_brick(sf::Vector2f(150, 30))
{
    if(a_color == YELLOW) {
        m_isUnbreakable = true;
    }
    m_brick.setPosition(a_position);
    m_brick.setOutlineColor((sf::Color::Black));
    m_brick.setOutlineThickness(1.f);
    m_brick.setFillColor(breakMap.at(a_color).second);
}

void Brick::draw(sf::RenderTarget& a_target) const 
{
    a_target.draw(m_brick);
}

sf::RectangleShape Brick::getBrick() const 
{
    return m_brick;
}

sf::FloatRect Brick::getBounds() const 
{
    return m_brick.getGlobalBounds();
}

sf::Color Brick::getColor() const
{
    return m_brick.getFillColor();
}

int Brick::getPointValue() const
{
    // Get the point value from the breakMap based on the brick's color
    auto it = breakMap.find(static_cast<BrickColor>(0)); // initialize iterator with a default value
    for (const auto& pair : breakMap) {
        if (pair.second.second == getColor()) {
            it = breakMap.find(pair.first);
            break;
        }
    }
    return it->second.first; // return the point value
}

Brick::BrickColor Brick::getColorFromString(const std::string& a_colorString) 
{
    std::map<std::string, BrickColor> colorMap {
        {"red", BrickColor::RED},
        {"blue", BrickColor::BLUE},
        {"pink", BrickColor::PINK},
        {"green", BrickColor::GREEN},
        {"light_orange", BrickColor::LIGHT_ORANGE},
        {"dark_orange", BrickColor::DARK_ORANGE},
        {"light_blue", BrickColor::LIGHT_BLUE},
        {"white", BrickColor::WHITE},
        {"gray", BrickColor::GRAY},
        {"yellow", BrickColor::YELLOW}
    };

    auto it = colorMap.find(a_colorString);
    if (it != colorMap.end()) {
        return it->second;
    }
    // is not found
    return BrickColor::RED;
}

sf::Vector2f Brick::getBrickSize() const {
    return m_brick.getSize();
}

bool Brick::isUnbreakable() const 
{
    return m_isUnbreakable;
}

} // arkanoid