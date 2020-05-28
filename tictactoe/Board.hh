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
	const int getDimension() const { return _dimension; };
	void clear();
	bool checkColumns(int winCond, char tag) const;
	bool checkRows(int winCond, char tag) const;
	bool checkDiagonals(int winCond, char tag) const;
	bool checkWin(int winCond, char tag) const;
	bool checkFull() const;
};