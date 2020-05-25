#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.hh"

int button(sf::Event event, int dimension, const std::unique_ptr<std::unique_ptr<sf::RectangleShape[]>[]>& sq) {
	int mouseX = event.mouseButton.x;
	int mouseY = event.mouseButton.y;
	for(int i = 0; i < dimension; ++i) {
		for(int j = 0; j < dimension; ++j) {
			int sqX = static_cast<int>(sq[i][j].getPosition().x);
			int sqY = static_cast<int>(sq[i][j].getPosition().y);
			if(mouseX >= sqX && mouseX <= sqX + 100 && mouseY >= sqY && mouseY <= sqY + 100)
				return i * dimension + j;
		}
	}
	return -1;
}

bool win(int playerScore, int botScore) {
	std::string scoreString = "Current score: Player " + std::to_string(playerScore) + "-" + std::to_string(botScore) + " Bot";
	sf::RenderWindow window(sf::VideoMode(500, 224), "YOU WIN");
	sf::Font font;
	font.loadFromFile("arial.ttf");
	sf::Text announ;
	sf::Text b1text;
	sf::Text b2text;
	sf::Text score;
	sf::RectangleShape button1(sf::Vector2f(140, 50));
	sf::RectangleShape button2(sf::Vector2f(140, 50));
	button1.setFillColor(sf::Color(200, 200, 200));
	button2.setFillColor(sf::Color(200, 200, 200));
	button1.setPosition(sf::Vector2f(80, 154));
	button2.setPosition(sf::Vector2f(280, 154));
	announ.setFont(font);
	announ.setString("YOU WIN!");
	announ.setCharacterSize(100);
	announ.setFillColor(sf::Color::Black);
	b1text.setFont(font);
	b1text.setString("Finish");
	b1text.setCharacterSize(30);
	b1text.setFillColor(sf::Color::Black);
	b2text.setFont(font);
	b2text.setString("Continue");
	b2text.setCharacterSize(30);
	b2text.setFillColor(sf::Color::Black);
	score.setFont(font);
	score.setString(scoreString);
	score.setCharacterSize(20);
	score.setFillColor(sf::Color::Black);
	announ.setOrigin(announ.getLocalBounds().width / 2, announ.getLocalBounds().height / 2);
	announ.setPosition(sf::Vector2f(250, 30));
	b1text.setOrigin(b1text.getLocalBounds().width / 2, b1text.getLocalBounds().height / 2);
	b1text.setPosition(sf::Vector2f(148, 171));
	b2text.setOrigin(b2text.getLocalBounds().width / 2, b2text.getLocalBounds().height / 2);
	b2text.setPosition(sf::Vector2f(349, 171));
	score.setOrigin(score.getLocalBounds().width / 2, score.getLocalBounds().height / 2);
	score.setPosition(250, 119);
	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			switch(event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::MouseButtonPressed:
					if(event.mouseButton.button == sf::Mouse::Left) {
						if(event.mouseButton.x >= button1.getPosition().x &&
							 event.mouseButton.x <= button1.getPosition().x + button1.getSize().x &&
							 event.mouseButton.y >= button1.getPosition().x &&
							 event.mouseButton.y <= button1.getPosition().y + button1.getSize().y) {
							window.close();
							return false;
						} else if(event.mouseButton.x >= button2.getPosition().x &&
											event.mouseButton.x <= button2.getPosition().x + button2.getSize().x &&
											event.mouseButton.y >= button2.getPosition().y &&
											event.mouseButton.y <= button2.getPosition().y + button2.getSize().y) {
							window.close();
							return true;
						}
					}
			}
		}
		window.clear(sf::Color::White);
		window.draw(announ);
		window.draw(button1);
		window.draw(button2);
		window.draw(b1text);
		window.draw(b2text);
		window.draw(score);
		window.display();
	}
}

int main() {
	int dimension = 5;
	char playerTag = 'x';
	char botTag = playerTag == 'x' ? 'o' : 'x';
	int winCondition = 3;
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
					if(button(event, dimension, sq) != -1) {
						int but = button(event, dimension, sq);
						if(board(but / dimension, but % dimension) == 0) {
							board(but / dimension, but % dimension) = playerTag;
							if(board.checkWin(winCondition, 'x')) {
								win();
								board.clear();
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