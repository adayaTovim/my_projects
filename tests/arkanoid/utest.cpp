#include "game.hpp"
#include "ball.hpp"
#include "paddle.hpp"
#include "game_screen.hpp"
#include "player.hpp"
#include "brick.hpp"
#include "menu_screen.hpp"
#include "top10_screen.hpp"
#include "input_screen.hpp"
#include "screen.hpp"

int main()
{
	using namespace arkanoid;

	Game game{};
	game.run();

	// //test transition between the input screen to  top10 screen
    // sf::RenderWindow window(sf::VideoMode(1280, 720), "My Window");
    // Top10Screen top10screen(sf::Vector2f(1280, 720), window);
	// int score = 600;
    // if (score == 600) {
	// 	bool isTop10 = top10screen.isTop10(600, 150);
	// 	if (isTop10) {
	// 		InputScreen InputScreen(sf::Vector2f(1280, 720), window);
	// 		InputScreen.run();
	// 		std::string WinnerName = InputScreen.getInput();
	// 		top10screen.addTop10(600, 50, WinnerName);

	// 		bool returnMenu = top10screen.run();
	// 		if (returnMenu == true) {
	// 			window.close();
	// 		}
	// 	}
	// }

	return 0;
 }

