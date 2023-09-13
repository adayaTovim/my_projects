#include "top10_screen.hpp"
#include "screen.hpp"

int main()
{
	using namespace arkanoid;


    sf::RenderWindow window(sf::VideoMode(1280, 720), "My Window");
    Top10Screen top10screen(sf::Vector2f(1280, 720), window);
    top10screen.run(std::nullopt);

    // Test case 1: create a TopScores object, add 10 scores and verify the size and order of the scores

    top10screen.addTop10(200, 120, "Player1");
    top10screen.addTop10(150, 90, "Player2");
    top10screen.addTop10(250, 150, "Player3");
    top10screen.addTop10(300, 180, "Player4");
    top10screen.addTop10(220, 130, "Player5");
    top10screen.addTop10(100, 70, "Player6");
    top10screen.addTop10(180, 110, "Player7");
    top10screen.addTop10(190, 115, "Player8");
    top10screen.addTop10(210, 125, "Player9");
    top10screen.addTop10(230, 135, "Player10");

    const std::vector<Winner>& scores = top10screen.getScores();
    std::cout << "Test case 1: verify the size and order of the scores" << std::endl;
    std::cout << "Expected size: " << NUM_SCORES << std::endl;
    std::cout << "Actual size: " << scores.size() << std::endl;
    std::cout << "Expected order: {300,250,230,220,210,200,190,180,150,100}" << std::endl;
    std::cout << "Actual order: {";
    for (const auto& score : scores) {
        std::cout << score.getScore() << ",";
    }
    std::cout << "}" << std::endl << std::endl;
    top10screen.saveToFile();

	return 0;
 }

