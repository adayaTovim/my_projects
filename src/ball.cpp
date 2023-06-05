#include "ball.hpp"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

namespace arkanoid {

namespace {

sf::CircleShape initBall() {
    sf::CircleShape circle(12.f);
    circle.setPosition(660, 663);
    circle.setOutlineThickness(2.f);
    circle.setOutlineColor(sf::Color(255, 0, 102));
    circle.setFillColor(sf::Color(205, 153, 255));
    return circle; 
}
}

Ball::Ball(float a_xVelocity, float a_yVelocity) 
: m_ball(initBall())
, m_xVelocity(a_xVelocity)
, m_yVelocity(a_yVelocity) 
{   
}

void Ball::draw(sf::RenderTarget& a_target) const {
    a_target.draw(m_ball);
}

const sf::CircleShape& Ball::getBall() const {
    return m_ball;
}

void Ball::setPosition(float a_xVelocity, float a_yVelocity) {
    m_ball.setPosition(a_xVelocity, a_yVelocity);
}

sf::Vector2f Ball::getPosition() const {
    return m_ball.getPosition();
}

void Ball::setXVelocity(float a_xVelocity) {
    m_xVelocity = a_xVelocity;
}

void Ball::setYVelocity(float a_yVelocity) {
    m_yVelocity = a_yVelocity;
}

float Ball::getXVelocity() const {
    return m_xVelocity;
}

float Ball::getYVelocity() const {
    return m_yVelocity;
}

sf::FloatRect Ball::getBounds() const {
    return m_ball.getGlobalBounds();
}

void Ball::resetPosition() {
    m_ball.setPosition(660, 663);
}

} //arkanoid
