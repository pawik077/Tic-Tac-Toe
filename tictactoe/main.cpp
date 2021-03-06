#include <iostream>
#include "Board.hh"
#include "Display.hh"
#include "AI.hh"

int main() {
	int dimension;
	int winCondition;
	char playerTag;
	bool changeSettings;
	bool playerTurn;
	bool cancel;
	std::cout << "Welcome to Tic-Tac-Toe!\n";
	do {
		cancel = false;
		do {
			std::cout << "Enter board dimensions (3 or more): ";
			std::cin >> dimension;
			while(std::cin.fail() || dimension < 3 || dimension > 10) {
				std::cerr << "Incorrect board dimensions!" << std::endl;
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				std::cout << "Enter board dimensions (3 or more): ";
				std::cin >> dimension;
			}
			if(dimension > 6) {
				std::string choice = "";
				std::cout << "WARNING!\n";
				std::cout << "Using large board dimensions may cause the bot to take a long to make the move.\n";
				std::cout << "Furthermore, large boards may not fit on low-to-medium resolution screens\n";
				std::cout << "Are you sure you want to continue (y/N): ";
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				getline(std::cin, choice);
				if(std::cin.fail() || choice[0] != 'y' && choice[0] != 'Y' && choice[0] != 'n' && choice[0] != 'N' && choice != "") {
					std::cerr << "Unknown option!" << std::endl;
					std::cin.clear();
					std::cin.ignore(10000, '\n');
					std::cout << "Are you sure you want to continue (y/N): ";
					choice = "";
					getline(std::cin, choice);
				}
				switch(choice[0]) {
					case 'n':
					case 'N':
					case '\0':
						cancel = true;
						break;
					case 'y':
					case 'Y':
					case 't':
					case 'T':
						std::cout << "Consider yourself warned\n";
						cancel = false;
						break;
				}
			}
		} while(cancel);
		if(dimension != 3) {
			std::cout << "Enter win condition (between 3 and " << dimension << "): ";
			std::cin >> winCondition;
			while(std::cin.fail() || winCondition > dimension || winCondition < 3) {
				std::cerr << "Incorrect win condition!" << std::endl;
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				std::cout << "Enter win condition (between 3 and " << dimension << "): ";
				std::cin >> winCondition;
			}
		} else winCondition = 3;
		std::cout << "Choose your tag (X or O, X always starts): ";
		std::cin >> playerTag;
		while(std::cin.fail() || playerTag != 'x' && playerTag != 'X' && playerTag != 'o' && playerTag != 'O') {
			std::cerr << "Incorrect tag!" << std::endl;
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::cout << "Choose your tag (X or O, X always starts): ";
			std::cin >> playerTag;
		}
		std::cout << "Generating GUI...\n";
		std::cout << "Click on the upper bar to change settings\n";
		playerTurn = playerTag == 'x';
		char winner = 0;
		int playerScore = 0;
		int botScore = 0;
		changeSettings = false;
		Board board(dimension, winCondition);
		AI bot(playerTag == 'x' ? 'o' : 'x');
		sf::Font font;
		font.loadFromFile("C:/Windows/Fonts/arial.ttf");
		sf::Text scoreBanner;
		sf::Text currentTurn;
		scoreBanner.setFont(font);
		scoreBanner.setCharacterSize(25);
		scoreBanner.setFillColor(sf::Color::Black);
		currentTurn.setFont(font);
		currentTurn.setCharacterSize(25);
		currentTurn.setFillColor(sf::Color::Black);
		std::string scoreText;
		std::string turnText;
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
			scoreText = "Player " + std::to_string(playerScore) + ":" + std::to_string(botScore) + " Bot";
			turnText = playerTurn ? "P" : "B";
			scoreBanner.setString(scoreText);
			scoreBanner.setOrigin(scoreBanner.getLocalBounds().width / 2, scoreBanner.getLocalBounds().height / 2);
			scoreBanner.setPosition(static_cast<float>(55 * dimension - 12), 10);
			currentTurn.setString(turnText);
			currentTurn.setOrigin(currentTurn.getLocalBounds().width, 0);
			currentTurn.setPosition(upperBar.getSize().x - 5, 0);
			sf::Event event;
			int but = -1;
			while(window.pollEvent(event)) {
				if(event.type == sf::Event::Closed)
					if(confirm('q')) {
						window.close();
					}
				if(event.type == sf::Event::MouseButtonPressed) {
					if(event.mouseButton.button == sf::Mouse::Left) {
						if(event.mouseButton.x >= upperBar.getPosition().x &&
							 event.mouseButton.x <= upperBar.getPosition().x + upperBar.getSize().x &&
							 event.mouseButton.y >= upperBar.getPosition().y &&
							 event.mouseButton.y <= upperBar.getPosition().y + upperBar.getSize().y) {
							if(confirm('c')) {
								window.close();
								changeSettings = true;
							}
						}
						if(field(event, dimension, sq) != -1 && playerTurn) {
							but = field(event, dimension, sq);
						}
					}
				}
			}
			window.clear(sf::Color::White);
			for(int i = 0; i < dimension; ++i) {
				for(int j = 0; j < dimension; ++j) {
					window.draw(sq[i][j]);
					switch(board(i, j)) {
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
			window.draw(scoreBanner);
			window.draw(currentTurn);
			window.display();
			if(winner == 'p') {
				++playerScore;
				winner = 0;
				if(gameOver(playerScore, botScore, 'w')) {
					board.clear();
					playerTurn = playerTag == 'x';
				} else
					window.close();
			} else if(winner == 'b') {
				++botScore;
				winner = 0;
				if(gameOver(playerScore, botScore, 'l')) {
					board.clear();
					playerTurn = playerTag == 'x';
				} else
					window.close();
			} else if(board.checkFull()) {
				if(gameOver(playerScore, botScore, 'd')) {
					board.clear();
					playerTurn = playerTag == 'x';
				} else
					window.close();
			}
			if(playerTurn) {
				if(board(but / dimension, but % dimension) == 0) {
					board(but / dimension, but % dimension) = playerTag;
					playerTurn = false;
					if(board.checkWin(playerTag)) {
						winner = 'p';
					}
				} else {
					but = -1;
				}
			} else {
				std::cout << "Bot thinking...  ";
				bot.move(board);
				std::cout << "Done\n";
				playerTurn = true;
				if(board.checkWin(bot.getTag())) {
					winner = 'b';
				}
			}
		}
	} while(changeSettings);
	return 0;
}