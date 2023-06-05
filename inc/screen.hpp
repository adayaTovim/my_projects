#pragma once
#include <SFML/Graphics.hpp>

namespace arkanoid {
    
class Screen {
public:
    virtual ~Screen() = default;

    virtual void run() = 0;
};

} //arkanoid