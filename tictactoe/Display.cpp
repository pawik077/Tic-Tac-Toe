#include "Display.hh"

int field(sf::Event event, int dimension, const std::unique_ptr<std::unique_ptr<sf::RectangleShape[]>[]>& sq) {
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

bool gameOver(int playerScore, int botScore, char state) {
	std::string scoreString = "Current score: Player " + std::to_string(playerScore) + ":" + std::to_string(botScore) + " Bot";
	sf::RenderWindow window(sf::VideoMode(580, 224), "", sf::Style::Titlebar);
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
	button2.setPosition(sf::Vector2f(360, 154));
	announ.setFont(font);
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
	b1text.setOrigin(b1text.getLocalBounds().width / 2, b1text.getLocalBounds().height / 2);
	b1text.setPosition(sf::Vector2f(148, 171));
	b2text.setOrigin(b2text.getLocalBounds().width / 2, b2text.getLocalBounds().height / 2);
	b2text.setPosition(sf::Vector2f(429, 171));
	score.setOrigin(score.getLocalBounds().width / 2, score.getLocalBounds().height / 2);
	score.setPosition(290, 119);
	switch(state) {
		case 'w':
			window.setTitle("YOU WIN");
			announ.setString("YOU WIN!");
			announ.setOrigin(announ.getLocalBounds().width / 2, announ.getLocalBounds().height / 2);
			announ.setPosition(sf::Vector2f(290, 30));
			break;
		case 'l':
			window.setTitle("YOU LOSE");
			announ.setString("YOU LOSE!");
			announ.setOrigin(announ.getLocalBounds().width / 2, announ.getLocalBounds().height / 2);
			announ.setPosition(sf::Vector2f(290, 30));
			break;
		case 'd':
			window.setTitle("DRAW");
			announ.setString("DRAW!");
			announ.setOrigin(announ.getLocalBounds().width / 2, announ.getLocalBounds().height / 2);
			announ.setPosition(sf::Vector2f(283, 30));
			break;
	}
	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			switch(event.type) {
				case sf::Event::MouseButtonPressed:
					if(event.mouseButton.button == sf::Mouse::Left) {
						if(event.mouseButton.x >= button1.getPosition().x &&
							 event.mouseButton.x <= button1.getPosition().x + button1.getSize().x &&
							 event.mouseButton.y >= button1.getPosition().y &&
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
					break;
				case sf::Event::MouseMoved:
					if(event.mouseMove.x >= button1.getPosition().x &&
						 event.mouseMove.x <= button1.getPosition().x + button1.getSize().x &&
						 event.mouseMove.y >= button1.getPosition().y &&
						 event.mouseMove.y <= button1.getPosition().y + button1.getSize().y)
						button1.setFillColor(sf::Color(150, 150, 150));
					else if(event.mouseMove.x >= button2.getPosition().x &&
									event.mouseMove.x <= button2.getPosition().x + button2.getSize().x &&
									event.mouseMove.y >= button2.getPosition().y &&
									event.mouseMove.y <= button2.getPosition().y + button2.getSize().y)
						button2.setFillColor(sf::Color(150, 150, 150));
					else {
						button1.setFillColor(sf::Color(200, 200, 200));
						button2.setFillColor(sf::Color(200, 200, 200));
					}
					break;
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
	return false;
}

bool confirm(char state) {
	sf::RenderWindow window(sf::VideoMode(1000, 224), "CONFIRM", sf::Style::Titlebar);
	sf::Font font;
	font.loadFromFile("arial.ttf");
	sf::Text mainText, subText, b1text, b2text;
	sf::RectangleShape button1(sf::Vector2f(100,50)), button2(sf::Vector2f(100,50));
	button1.setFillColor(sf::Color(200, 200, 200));
	button2.setFillColor(sf::Color(200, 200, 200));
	button1.setPosition(sf::Vector2f(250, 148));
	button2.setPosition(sf::Vector2f(650, 148));
	mainText.setFont(font);
	mainText.setCharacterSize(50);
	mainText.setFillColor(sf::Color::White);
	subText.setFont(font);
	subText.setCharacterSize(40);
	subText.setFillColor(sf::Color::White);
	subText.setString("You will lose current game state");
	subText.setOrigin(subText.getLocalBounds().width / 2, subText.getLocalBounds().height / 2);
	subText.setPosition(500, 100);
	b1text.setFont(font);
	b1text.setString("Yes");
	b1text.setCharacterSize(30);
	b1text.setFillColor(sf::Color::White);
	b2text.setFont(font);
	b2text.setString("No");
	b2text.setCharacterSize(30);
	b2text.setFillColor(sf::Color::White);
	b1text.setOrigin(b1text.getLocalBounds().width / 2, b1text.getLocalBounds().height / 2);
	b1text.setPosition(sf::Vector2f(301, 165));
	b2text.setOrigin(b2text.getLocalBounds().width / 2, b2text.getLocalBounds().height / 2);
	b2text.setPosition(sf::Vector2f(698, 165));
	switch(state) {
		case 'c':
			mainText.setString("Are you sure you want to change settings?");
			mainText.setOrigin(mainText.getLocalBounds().width / 2, mainText.getLocalBounds().height / 2);
			mainText.setPosition(sf::Vector2f(500, 30));
			break;
		case 'q':
			mainText.setString("Are you sure you want to quit?");
			mainText.setOrigin(mainText.getLocalBounds().width / 2, mainText.getLocalBounds().height / 2);
			mainText.setPosition(sf::Vector2f(500, 30));
			break;
	}
	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			switch(event.type) {
				case sf::Event::MouseButtonPressed:
					if(event.mouseButton.button == sf::Mouse::Left) {
						if(event.mouseButton.x >= button1.getPosition().x &&
							 event.mouseButton.x <= button1.getPosition().x + button1.getSize().x &&
							 event.mouseButton.y >= button1.getPosition().y &&
							 event.mouseButton.y <= button1.getPosition().y + button1.getSize().y) {
							window.close();
							return true;
						} else if(event.mouseButton.x >= button2.getPosition().x &&
											event.mouseButton.x <= button2.getPosition().x + button2.getSize().x &&
											event.mouseButton.y >= button2.getPosition().y &&
											event.mouseButton.y <= button2.getPosition().y + button2.getSize().y) {
							window.close();
							return false;
						}
					}
					break;
				case sf::Event::MouseMoved:
					if(event.mouseMove.x >= button1.getPosition().x &&
						 event.mouseMove.x <= button1.getPosition().x + button1.getSize().x &&
						 event.mouseMove.y >= button1.getPosition().y &&
						 event.mouseMove.y <= button1.getPosition().y + button1.getSize().y)
						button1.setFillColor(sf::Color(150, 150, 150));
					else if(event.mouseMove.x >= button2.getPosition().x &&
									event.mouseMove.x <= button2.getPosition().x + button2.getSize().x &&
									event.mouseMove.y >= button2.getPosition().y &&
									event.mouseMove.y <= button2.getPosition().y + button2.getSize().y)
						button2.setFillColor(sf::Color(150, 150, 150));
					else {
						button1.setFillColor(sf::Color(200, 200, 200));
						button2.setFillColor(sf::Color(200, 200, 200));
					}
					break;
			}
		}
		window.clear(sf::Color::Black);
		window.draw(mainText);
		window.draw(subText);
		window.draw(button1);
		window.draw(button2);
		window.draw(b1text);
		window.draw(b2text);
		window.display();
	}
	return false;
}