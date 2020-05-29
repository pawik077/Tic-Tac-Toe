#include "AI.hh"

int AI::minMax(Board& board, int depth, bool isMax) {
	char playerTag = _botTag == 'o' ? 'x' : 'o';
	if(depth == 0) return 0;
	if(board.checkWin(_botTag)) return 10 + depth;
	if(board.checkWin(playerTag)) return -10 - depth;
	if(board.checkFull()) return 0;
	if(isMax) {
		int best = -1000000;
		std::list<int> moves = board.getEmpty();
		for(int move : moves) {
			board(move / board.getDimension(), move % board.getDimension()) = _botTag;
			std::cout << "bot calc";
			int solution = minMax(board, depth - 1, !isMax);
			best = best > solution ? best : solution;
			board(move / board.getDimension(), move % board.getDimension()) = 0;
		}
		return best;
	} else {
		int best = 1000000;
		std::list<int> moves = board.getEmpty();
		for(int move : moves) {
			board(move / board.getDimension(), move % board.getDimension()) = playerTag;
			std::cout << "player calc";
			int solution = minMax(board, depth - 1, !isMax);
			best = best < solution ? best : solution;
			board(move / board.getDimension(), move % board.getDimension()) = 0;
		}
		return best;
	}
}

void AI::move(Board& board) {
	int bestScore = -1000000;
	int bestMove = -1;
	int depth = static_cast<int>(1.4 * board.getDimension() - board.getWinCond());
	std::list<int> moves = board.getEmpty();
	for(int move : moves) {
		board(move / board.getDimension(), move % board.getDimension()) = _botTag;
		int moveScore = minMax(board, depth, false);
		board(move / board.getDimension(), move % board.getDimension()) = 0;
		if(moveScore > bestScore) {
			bestMove = move;
			bestScore = moveScore;
		}
	}
	board(bestMove / board.getDimension(), bestMove % board.getDimension()) = _botTag;
}