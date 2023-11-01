#ifndef MOVE_HPP
#define MOVE_HPP

#include "core.hpp"
#include "chess_piece_2D.hpp"

class Move {
public:
	int moveNumber;
	int m_startPosX, m_startPosY, m_endPosX, m_endPosY;
	ChessPieceType m_piece;

	Move(int startPosX, int startPosY, int endPosX, int endPosY, ChessPieceType piece) {
		m_startPosX = startPosX;
		m_startPosY = startPosY;
		m_endPosX = endPosX;
		m_endPosY = endPosY;
		m_piece = piece;
	};
	Tuple<int, int> getStartTile();
	Tuple<int, int> getEndTile();
	ChessPieceType getPieceType();
};
#endif
