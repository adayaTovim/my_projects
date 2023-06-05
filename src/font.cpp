#include "font.hpp"

namespace arkanoid {


Font::Font()
: m_font()
{
	if (!m_font.loadFromFile("arial.ttf")) {
        std::cerr << "Error: Failed to load font 'arial.ttf'" << std::endl;
    }
}

sf::Font const& Font::get() const noexcept {
    return m_font;
}

} //arkanoid