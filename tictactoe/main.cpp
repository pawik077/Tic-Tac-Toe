#include <iostream>
#include "Board.hh"
#include "Display.hh"

int main() {
	int dimension = 5;
	char playerTag = 'x';
	char botTag = playerTag == 'x' ? 'o' : 'x';
	int winCondition = 3;
	int playerScore = 0;
	int botScore = 0;
	Board board(dimension);
	//std::cout << "Dim: ";
	//std::cin >> dimension;
	//std::cout << "Num: ";
	//std::cin >> numberToWin;
	sf::ContextSettings windowSettings;
	windowSettings.antialiasingLevel = 16;
	sf::RenderWindow window(sf::VideoMode(10 + 110 * dimension, 110 * dimension + 40), "Tic-Tac-Toe", sf::Style::Titlebar | sf::Style::Close, windowSettings);
	sf::RectangleShape upperBar(sf::Vector2f(static_cast<float>(10 + 110 * dimension), 30));
	upperBar.setFillColor(sf::Color(200, 200, 200));
	std::unique_ptr<std::unique_ptr<sf::RectangleShape[]>[]> sq = std::make_unique<std::unique_ptr<sf::RectangleShape[]>[]>(dimension);;
	for(int i = 0; i < dimension; ++i) sq[i] = std::make_unique<sf::RectangleShape[]>(dimension);
	std::unique_ptr<std::unique_ptr<sf::CircleShape[]>[]> circles = std::make_unique<std::unique_ptr<sf::CircleShape[]>[]>(dimension);
	for(int i = 0; i < dimension; ++i) circles[i] = std::make_unique<sf::CircleShape[]>(dimension);
	std::unique_ptr<std::unique_ptr<sf::RectangleShape[][2]>[]> crosses = std::make_unique<std::unique_ptr<sf::RectangleShape[][2]>[]>(dimension);
	for(int i = 0; i < dimension; ++i) crosses[i] = std::make_unique<sf::RectangleShape[][2]>(dimension);
	for(int i = 0; i < dimension; ++i) {
		for(int j = 0; j < dimension; ++j) {
			sq[i][j].setSize(sf::Vector2f(100, 100));
			sq[i][j].setFillColor(sf::Color(200, 200, 200));
			sq[i][j].setPosition(sf::Vector2f(10, 40));
			sq[i][j].move(sf::Vector2f(static_cast<float>(110 * j), static_cast<float>(110 * i)));
			circles[i][j].setRadius(40);
			circles[i][j].setPointCount(20);
			circles[i][j].setPosition(sf::Vector2f(20, 50));
			circles[i][j].move(sf::Vector2f(static_cast<float>(110 * j), static_cast<float>(110 * i)));
			circles[i][j].setFillColor(sf::Color(200, 200, 200));
			circles[i][j].setOutlineThickness(-5);
			circles[i][j].setOutlineColor(sf::Color::Black);
			crosses[i][j][0].setSize(sf::Vector2f(113, 5));
			crosses[i][j][0].setFillColor(sf::Color::Black);
			crosses[i][j][0].setOrigin(57, 3);
			crosses[i][j][0].setPosition(sf::Vector2f(60, 91));
			crosses[i][j][0].move(sf::Vector2f(static_cast<float>(110 * j), static_cast<float>(110 * i)));
			crosses[i][j][0].rotate(45);
			crosses[i][j][1].setSize(sf::Vector2f(113, 5));
			crosses[i][j][1].setFillColor(sf::Color::Black);
			crosses[i][j][1].setOrigin(57, 3);
			crosses[i][j][1].setPosition(sf::Vector2f(59, 90));
			crosses[i][j][1].move(sf::Vector2f(static_cast<float>(110 * j), static_cast<float>(110 * i)));
			crosses[i][j][1].rotate(135);
		}
	}
	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed)
				window.close();
			if(event.type == sf::Event::MouseButtonPressed) {
				if(event.mouseButton.button == sf::Mouse::Left)
					if(field(event, dimension, sq) != -1) {
						int but = field(event, dimension, sq);
						if(board(but / dimension, but % dimension) == 0) {
							board(but / dimension, but % dimension) = playerTag;
							if(board.checkWin(winCondition, 'x')) {
								++playerScore;
								if(win(playerScore, botScore))
									board.clear();
								else 
									window.close();
							}
						}
					}
			}
		}
		window.clear(sf::Color::White);
		for(int i = 0; i < dimension; ++i) {
			for(int j = 0; j < dimension; ++j) {
				window.draw(sq[i][j]);
				switch(board(i,j)) {
					case 'x':
						window.draw(crosses[i][j][0]);
						window.draw(crosses[i][j][1]);
						break;
					case 'o':
						window.draw(circles[i][j]);
						break;
				}
			}
		}
		window.draw(upperBar);
		window.display();
	}
	return 0;
}