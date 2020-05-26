#pragma once
#include <SFML/Graphics.hpp>

int field(sf::Event event, int dimension, const std::unique_ptr<std::unique_ptr<sf::RectangleShape[]>[]>& sq);
bool gameOver(int playerScore, int botScore, char state);
bool confirm(char state);