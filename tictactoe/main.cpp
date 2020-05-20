#include <SFML/Graphics.hpp>
#include <iostream>

int button(sf::Event event) {
	if(event.mouseButton.x >= 10 && event.mouseButton.x <= 110 && event.mouseButton.y >= 40 && event.mouseButton.y <= 140)
		return 0;
	else if(event.mouseButton.x >= 120 && event.mouseButton.x <= 220 && event.mouseButton.y >= 40 && event.mouseButton.y <= 140)
		return 1;
	else if(event.mouseButton.x >= 230 && event.mouseButton.x <= 330 && event.mouseButton.y >= 40 && event.mouseButton.y <= 140)
		return 2;
	else if(event.mouseButton.x >= 10 && event.mouseButton.x <= 110 && event.mouseButton.y >= 150 && event.mouseButton.y <= 250)
		return 3;
	else if(event.mouseButton.x >= 120 && event.mouseButton.x <= 220 && event.mouseButton.y >= 150 && event.mouseButton.y <= 250)
		return 4;
	else if(event.mouseButton.x >= 230 && event.mouseButton.x <= 330 && event.mouseButton.y >= 150 && event.mouseButton.y <= 250)
		return 5;
	else if(event.mouseButton.x >= 10 && event.mouseButton.x <= 110 && event.mouseButton.y >= 260 && event.mouseButton.y <= 360)
		return 6;
	else if(event.mouseButton.x >= 120 && event.mouseButton.x <= 220 && event.mouseButton.y >= 260 && event.mouseButton.y <= 360)
		return 7;
	else if(event.mouseButton.x >= 230 && event.mouseButton.x <= 330 && event.mouseButton.y >= 260 && event.mouseButton.y <= 360)
		return 8;
	return -1;
	}
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
			if(event.type == sf::Event::MouseButtonPressed) {
				if(event.mouseButton.button == sf::Mouse::Left)
					if(button(event)!=-1)
						std::cout << button(event);
			}
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