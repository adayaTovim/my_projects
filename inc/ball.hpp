#pragma once

#include <SFML/Graphics.hpp>

namespace arkanoid {

class Ball {
public:
    Ball() = delete;
    explicit Ball(float a_xVelocity, float a_yVelocity);
    Ball(Ball const& a_other) = delete;
    Ball& operator=(Ball const& a_other) = delete;
    ~Ball() = default;

    void draw(sf::RenderTarget& target) const;
    const sf::CircleShape& getBall() const;

    void setXVelocity(float a_xVelocity);
    void setYVelocity(float a_yVelocity);
    float getXVelocity() const;
    float getYVelocity() const;

    void reverseXVelocity();
    void reverseYVelocity();
    sf::Vector2f getPosition() const;
    void setPosition(float a_xVelocity, float a_yVelocity);
    void resetPosition(); 


    sf::FloatRect getBounds() const;

private:
    sf::CircleShape m_ball;
    float m_xVelocity;
    float m_yVelocity;
};

} // arkanoid
