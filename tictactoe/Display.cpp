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

bool win(int playerScore, int botScore) {
	std::string scoreString = "Current score: Player " + std::to_string(playerScore) + ":" + std::to_string(botScore) + " Bot";
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
	return false;
}

bool lose(int playerScore, int botScore) {
	std::string scoreString = "Current score: Player " + std::to_string(playerScore) + ":" + std::to_string(botScore) + " Bot";
	sf::RenderWindow window(sf::VideoMode(580, 224), "YOU LOSE");
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
	announ.setString("YOU LOSE!");
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
	announ.setPosition(sf::Vector2f(290, 30));
	b1text.setOrigin(b1text.getLocalBounds().width / 2, b1text.getLocalBounds().height / 2);
	b1text.setPosition(sf::Vector2f(148, 171));
	b2text.setOrigin(b2text.getLocalBounds().width / 2, b2text.getLocalBounds().height / 2);
	b2text.setPosition(sf::Vector2f(429, 171));
	score.setOrigin(score.getLocalBounds().width / 2, score.getLocalBounds().height / 2);
	score.setPosition(290, 119);
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
	return false;
}
