#include "menu_screen.hpp"
#include "screen.hpp"

int main()
{
	using namespace arkanoid;


    sf::RenderWindow window(sf::VideoMode(1280, 720), "My Window");
    MenuScreen menuScreen(sf::Vector2f(1280, 720), window);
    menuScreen.run();

    // std::string input = menuScreen.getInput();
    // std::cout << "Input: " << input << std::endl;

	return 0;
 }

