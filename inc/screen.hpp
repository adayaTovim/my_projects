#pragma once
#include <SFML/Graphics.hpp>
#include <tuple>
#include <optional>

namespace arkanoid {

class ScreenState {
public:
    virtual ~ScreenState() = default;

    virtual std::optional<std::tuple<int, int, bool>> run(std::optional<std::string> a_level) = 0;
};

} //arkanoid
