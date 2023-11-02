#ifndef MOVE_HPP
#define MOVE_HPP

#include "core.hpp"
#include "chess_piece_2D.hpp"

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
