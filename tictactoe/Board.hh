#pragma once
#include <memory>
#include <list>

class Board {
private:
	std::unique_ptr<std::unique_ptr<char[]>[]> _board;
	int _dimension;
public:
	Board(int dimension);
	const char operator () (int x, int y) const { return _board[x][y]; }
	char& operator () (int x, int y) { return _board[x][y]; }
	void clear();
	bool checkColumns(int winCond, char tag);
	bool checkRows(int winCond, char tag);
	bool checkDiagonals(int winCond, char tag) { return false; };
	bool checkWin(int winCond, char tag);
};

