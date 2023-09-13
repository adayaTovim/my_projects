#include "input_screen.hpp"
#include "screen.hpp"

int main()
{
	using namespace arkanoid;


    sf::RenderWindow window(sf::VideoMode(1280, 720), "My Window");
    InputScreen inputScreen(sf::Vector2f(1280, 720), window);
    inputScreen.run(std::nullopt);

    std::string input = inputScreen.getInput();
    std::cout << "Input: " << input << std::endl;

	return 0;
 }

