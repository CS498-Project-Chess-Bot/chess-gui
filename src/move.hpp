#ifndef MOVE_HPP
#define MOVE_HPP

#include "core.hpp"

class Move{
public:
	int moveNumber;
	Move(startPos, endPos, PieceType);
	Tuple<int, int> getStartTile();
	Tuple<int, int> getEndTile();
	ChessPieceType enum getPieceType();
}
#endif
