#pragma once
class AI {
	char _botTag;
public:
	AI(char botTag) { _botTag = botTag; }
	const char getTag() { return _botTag; }
};

