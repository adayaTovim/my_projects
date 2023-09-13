#pragma once
#include <SFML/Graphics.hpp>
#include <tuple>
#include <optional>

namespace arkanoid {

class ScreenState {
public:
    virtual ~ScreenState() = default;

    virtual std::optional<std::tuple<bool, size_t, double, std::string>> run() = 0;
};

} //arkanoid
