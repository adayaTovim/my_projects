
#pragma once

#include <SFML/Graphics.hpp>

namespace arkanoid {

class Paddle{
public:
    Paddle() = delete;
    explicit Paddle(float a_xVelocity);
    Paddle(Paddle const& a_other) = delete;
    Paddle& operator=(Paddle const& a_other) = delete;
    ~Paddle() = default;

    void draw(sf::RenderTarget& a_target) const;
    void move(float a_xVelocity, float a_yVelocity);
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
    void resetPaddle();

private:
    sf::RectangleShape m_paddle;
    float m_xVelocity;

};

} // arkanoid

