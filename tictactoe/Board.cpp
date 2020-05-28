#include "Board.hh"

Board::Board(int dimension, int winCond) {
	_board = std::make_unique<std::unique_ptr<char[]>[]>(dimension);
	for(int i = 0; i < dimension; ++i) _board[i] = std::make_unique<char[]>(dimension);
	_dimension = dimension;
	_winCond = winCond;
	this->clear();
}

void Board::clear() {
	for(int i = 0; i < _dimension; ++i)
		for(int j = 0; j < _dimension; ++j)
			_board[i][j] = 0;
}

bool Board::checkColumns(char tag) const {
	for(int col = 0; col < _dimension; ++col) {
		std::list<char> win;
		for(int row = 0; row < _dimension; ++row) {
			if(_board[row][col] == tag) win.push_back(_board[row][col]);
			if(win.size() == _winCond) return true;
			if(_board[row][col] != tag) win.clear();
		}
	}
	return false;
}

bool Board::checkRows(char tag) const {
	for(int row = 0; row < _dimension; ++row) {
		std::list<char> win;
		for(int col = 0; col < _dimension; ++col) {
			if(_board[row][col] == tag) win.push_back(_board[row][col]);
			if(win.size() == _winCond) return true;
			if(_board[row][col] != tag) win.clear();
		}
	}
	return false;
}

bool Board::checkDiagonals(char tag) const {
	int x, y;
	for(int i = 0; i < _dimension - _winCond + 1; ++i) {
		std::list<char> win;
		x = i; y = 0;
		for(int j = 0; j < _dimension - i; ++j) {
			if(_board[x][y] == tag) win.push_back(_board[x][y]);
			if(win.size() == _winCond) return true;
			if(_board[x][y] != tag) win.clear();
			++x; ++y;
		}
		win.clear();
		x = 0; y = i;
		for(int j = 0; j < _dimension - i; ++j) {
			if(_board[x][y] == tag) win.push_back(_board[x][y]);
			if(win.size() == _winCond) return true;
			if(_board[x][y] != tag) win.clear();
			++x; ++y;
		}
		win.clear();
		x = _dimension - 1 - i; y = 0;
		for(int j = 0; j < _dimension - i; ++j) {
			if(_board[x][y] == tag) win.push_back(_board[x][y]);
			if(win.size() == _winCond) return true;
			if(_board[x][y] != tag) win.clear();
			--x; ++y;
		}
		win.clear();
		x = _dimension - 1; y = i;
		for(int j = 0; j < _dimension - i; ++j) {
			if(_board[x][y] == tag) win.push_back(_board[x][y]);
			if(win.size() == _winCond) return true;
			if(_board[x][y] != tag) win.clear();
			--x; ++y;
		}
	}
	return false;
}

bool Board::checkWin(char tag) const {
	return this->checkRows(tag) || this->checkColumns(tag) || this->checkDiagonals(tag);
}

bool Board::checkFull() const {
	for(int i = 0; i < _dimension; ++i) {
		for(int j = 0; j < _dimension; ++j) {
			if(_board[i][j] == 0) return false;
		}
	}
	return true;
}