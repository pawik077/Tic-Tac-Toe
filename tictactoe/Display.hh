#pragma once
#include <SFML/Graphics.hpp>

int field(sf::Event event, int dimension, const std::unique_ptr<std::unique_ptr<sf::RectangleShape[]>[]>& sq);
bool win(int playerScore, int botScore);
bool lose(int playerScore, int botScore);
bool draw(int playerScore, int botScore);