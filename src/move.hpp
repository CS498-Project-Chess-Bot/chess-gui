#ifndef MOVE_HPP
#define MOVE_HPP

#include "core.hpp"

enum class ChessPieceType {
    black_king = -6,
    black_queen = -5,
    black_bishop = -4,
    black_knight = -3,
    black_rook = -2,
    black_pawn = -1,
    none = 0,
    white_pawn = 1,
    white_rook = 2,
    white_knight = 3,
    white_bishop = 4,
    white_queen = 5,
    white_king = 6
    
};

class Move {
public:
	Move(int startPosX, int startPosY, int endPosX, int endPosY, ChessPieceType piece);
	std::tuple<int, int> getStartTile();
	std::tuple<int, int> getEndTile();
	ChessPieceType getPieceType();

private:
	int moveNumber;
	int m_startPosX, m_startPosY, m_endPosX, m_endPosY;
	ChessPieceType m_piece;
};
#endif
