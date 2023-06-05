#include <SFML/Graphics.hpp>

#include "paddle.hpp"

namespace arkanoid {

namespace {
    sf::RectangleShape initPaddle() {
        sf::RectangleShape rectangle(sf::Vector2f(125, 20));
        rectangle.setFillColor(sf::Color::Black);
        rectangle.setPosition(630, 690);
        return rectangle;
    }
}

Paddle::Paddle(float a_xVelocity) 
: m_paddle(initPaddle())
, m_xVelocity(a_xVelocity) 
{
}

void Paddle::draw(sf::RenderTarget& a_target) const {
    a_target.draw(m_paddle);
}

void Paddle::move(float a_xVelocity, float a_yVelocity) {
    m_paddle.move(a_xVelocity, a_yVelocity);
}

sf::Vector2f Paddle::getPosition() const {
    return m_paddle.getPosition();
}

sf::FloatRect Paddle::getBounds() const {
    return m_paddle.getGlobalBounds();
}

void Paddle::resetPaddle() {
    m_paddle.setPosition(630.f, 690.f);
}

} // namespace arkanoid
