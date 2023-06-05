#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

namespace arkanoid {

class Font {
public:
    Font();
    Font(Font const& a_other) = delete;
    Font& operator=(Font const& a_other) = delete;
    ~Font() = default;

    sf::Font const& get() const noexcept;

private:
	sf::Font m_font;
};

} //arkanoid