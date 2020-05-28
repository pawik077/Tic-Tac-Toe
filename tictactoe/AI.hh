#pragma once
#include "Board.hh"
#include <iostream>

class AI {
	char _botTag;
	int minMax(Board& board, int depth, bool isMax);
public:
	AI(char botTag) { _botTag = botTag; }
	const char getTag() { return _botTag; }
	void move(Board& board);
};

