#pragma once
#include <memory>
#include <list>

class Board {
private:
	std::unique_ptr<std::unique_ptr<char[]>[]> _board;
	int _dimension;
	int _winCond;
	bool checkColumns(char tag) const;
	bool checkRows(char tag) const;
	bool checkDiagonals(char tag) const;
public:
	Board(int dimension, int winCond);
	const char operator () (int x, int y) const { return _board[x][y]; }
	char& operator () (int x, int y) { return _board[x][y]; }
	const int getDimension() const { return _dimension; };
	const int getWinCond() const { return _winCond; }
	void clear();
	bool checkWin(char tag) const;
	bool checkFull() const;
};