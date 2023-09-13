#include "game_screen.hpp"
#include "screen.hpp"

int main()
{
	using namespace arkanoid;


    sf::RenderWindow window(sf::VideoMode(1280, 720), "My Window");
    GameScreen gameScreen(sf::Vector2f(1280, 720), window);
    gameScreen.run("level1");

    // std::string input = gameScreen.getInput();
    // std::cout << "Input: " << input << std::endl;

	return 0;
 }

