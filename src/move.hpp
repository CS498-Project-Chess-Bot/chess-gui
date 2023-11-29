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
	Move(int startPosX = -1, int startPosY = -1, int endPosX = -1, int endPosY = -1, ChessPieceType piece = ChessPieceType::none);
	std::tuple<int, int> getStartTile();
	std::tuple<int, int> getEndTile();
	ChessPieceType getPieceType();

    void setStart(int x, int y) {
        m_startPosX = x;
        m_startPosY = y;
    }

    void setEnd(int x, int y) {
        m_endPosX = x;
        m_endPosY = y;
    }

    void setPiece(ChessPieceType piece) {
        m_piece = piece;
    }

private:
	int moveNumber;
	int m_startPosX, m_startPosY, m_endPosX, m_endPosY;
	ChessPieceType m_piece;
};
#endif
