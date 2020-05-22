#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

int button(sf::Event event, int dimension, const std::unique_ptr<std::unique_ptr<sf::RectangleShape[]>[]>& sq) {
	int mouseX = event.mouseButton.x;
	int mouseY = event.mouseButton.y;
	for(int i = 0; i < dimension; ++i) {
		for(int j = 0; j < dimension; ++j) {
			int sqX = sq[i][j].getPosition().x;
			int sqY = sq[i][j].getPosition().y;
			if(mouseX >= sqX && mouseX <= sqX + 100 && mouseY >= sqY && mouseY <= sqY + 100)
				return i + j * dimension;
		}
	}
	return -1;
}

bool checkColumns(std::unique_ptr<std::unique_ptr<char[]>[]>& board, int dim, int winCond) {
	for(int col = 0; col < dim; ++col) {
		bool win = true;
		for(int row = 0; row < dim; ++row) {
			if(board[row][col] == 0 || board[row][col] == 'o')
				win = false;
			std::cout << "";
		}
		if(win) return win;
	}
	for(int col = 0; col < dim; ++col) {
		bool win = true;
		for(int row = 0; row < dim; ++row) {
			if(board[row][col] == 0 || board[row][col] == 'x') win = false;
			std::cout << "";
		}
		if(win) return win;
	}
	return false;
}

bool checkRows(std::unique_ptr<std::unique_ptr<char[]>[]>& board, int dimension, int winCond, char tag) {
	for(int row = 0; row < dimension; ++row) {
		std::list<char> win;
		for(int col = 0; col < dimension; ++col) {
			if(board[row][col] == tag) win.push_back(board[row][col]);
			std::cout << win.size();
			if(win.size() == winCond) return true;
			if(board[row][col] != tag) win.clear();
		}
	}
	return false;
}

int main() {
	int dimension = 4;
	char playerTag = 'x';
	int winCondition = 3;
	//std::cout << "Dim: ";
	//std::cin >> dimension;
	//std::cout << "Num: ";
	//std::cin >> numberToWin;
	sf::RenderWindow window(sf::VideoMode(10 + 110 * dimension, 110 * dimension + 40), "Tic-Tac-Toe");
	sf::RectangleShape upperBar(sf::Vector2f(10 + 110 * dimension, 30));
	upperBar.setFillColor(sf::Color(200, 200, 200));
	std::unique_ptr<std::unique_ptr<sf::RectangleShape[]>[]> sq;
	sq = std::make_unique<std::unique_ptr<sf::RectangleShape[]>[]>(dimension);
	for(int i = 0; i < dimension; ++i) sq[i] = std::make_unique<sf::RectangleShape[]>(dimension);
	std::unique_ptr<std::unique_ptr<char[]>[]> board;
	board = std::make_unique<std::unique_ptr<char[]>[]>(dimension);
	for(int i = 0; i < dimension; ++i) board[i] = std::make_unique<char[]>(dimension);
	for(int i = 0; i < dimension; ++i)
		for(int j = 0; j < dimension; ++j)
			board[i][j] = 0;
	for(int i = 0; i < dimension; ++i) {
		for(int j = 0; j < dimension; ++j) {
			sq[i][j].setSize(sf::Vector2f(100, 100));
			sq[i][j].setFillColor(sf::Color(200, 200, 200));
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
					if(button(event, dimension, sq) != -1) {
						int but = button(event, dimension, sq);
						if(board[but / dimension][but % dimension] == 0) {
							board[but / dimension][but % dimension] = playerTag;
							if(checkRows(board, dimension, winCondition, 'x')) std::cout << "win";
						}
					}
			}
		}
		window.clear(sf::Color::White);
		for(int i = 0; i < dimension; ++i) {
			for(int j = 0; j < dimension; ++j)
				window.draw(sq[i][j]);
		}
		window.draw(upperBar);
		window.display();
	}
	return 0;
}