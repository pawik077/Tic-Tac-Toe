#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
	//int dimension;
	//int numberToWin;
	//std::cout << "Dim: ";
	//std::cin >> dimension;
	//std::cout << "Num: ";
	//std::cin >> numberToWin;
	sf::RenderWindow window(sf::VideoMode(340, 370), "Tic-Tac-Toe");
	sf::RectangleShape sq[3][3];
	for(int i = 0; i < 3; ++i) {
		for(int j = 0; j < 3; ++j) {
			sq[i][j].setSize(sf::Vector2f(100, 100));
			sq[i][j].setFillColor(sf::Color::Green);
			sq[i][j].setPosition(sf::Vector2f(10, 40));
			sq[i][j].move(sf::Vector2f(110 * i, 110 * j));
		}
	}
	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::Black);
		for(int i = 0; i < 3; ++i) {
			for(int j = 0; j < 3; ++j)
				window.draw(sq[i][j]);
		}
		window.display();
	}
	return 0;
}