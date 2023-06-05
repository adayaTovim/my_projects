#pragma once

#include <SFML/Graphics.hpp>
#include <map>

namespace arkanoid {

class Brick {
public:
    enum BrickColor {
        RED,
        BLUE,
        PINK,
        GREEN, 
        LIGHT_ORANGE,
        DARK_ORANGE, 
        LIGHT_BLUE,
        WHITE,
        GRAY,
        YELLOW
    };

    Brick() = default;
    explicit Brick(sf::Vector2f a_position, BrickColor a_color);
    ~Brick() = default;

    virtual void draw(sf::RenderTarget& a_target) const;
    virtual sf::FloatRect getBounds() const;

    sf::RectangleShape getBrick() const;

    sf::Color getColor() const;
    int getPointValue() const;

    bool isUnbreakable() const;
    BrickColor getColorFromString(const std::string& a_colorString);

    sf::Vector2f getBrickSize() const;
private:
    sf::RectangleShape m_brick;
    bool m_isUnbreakable{ false };
};

} // arkanoid