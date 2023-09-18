#pragma once
#include <SFML/Graphics.hpp>
#include <tuple>
#include <optional>

namespace arkanoid {

class ScreenState {
public:
    virtual ~ScreenState() = default;

    virtual std::optional<std::tuple<int, int, bool>> run(std::optional<std::string> a_level) = 0;

    // dummy implementations for other virtual functions
    virtual bool bricksAreEmpty() const { return false; }
    virtual void drawWin() {}
    virtual bool isTop10(int a_score, int a_time) const { return true; }
	virtual std::string getInput() const { return ""; }

    virtual void addTop10(int a_score, int a_time, const std::string& a_name) {}
    virtual void drawLevelUp() {}

};

} //arkanoid

