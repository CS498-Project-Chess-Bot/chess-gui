#ifndef BOARD_HPP
#define BOARD_HPP

#include "core.hpp"

class Board{
public:
	Board(String FEN);
	~Board();
	void makeMove(Move);
	bool isCheckMate();
	bool isStalemate();
	void resetBoard();
	int getTurnCount();

	using enum ChessPieceType;
	ChessPieceType defaultBoard[8][8] = {
		white_rook, white_knight, white_bishop, white_queen, white_king, white_bishop, white_knight, white_rook,
		white_pawn, white_pawn,   white_pawn,   white_pawn,  white_pawn, white_pawn,   white_pawn,   white_pawn,
		none,       none,         none,         none,        none,       none,         none,         none,
		none,       none,         none,         none,        none,       none,         none,         none,
		none,       none,         none,         none,        none,       none,         none,         none,
		none,       none,         none,         none,        none,       none,         none,         none,
		black_pawn, black_pawn,   black_pawn,   black_pawn,  black_pawn, black_pawn,   black_pawn,   black_pawn,
		black_rook, black_knight, black_bishop, black_queen, black_king, black_bishop, black_knight, black_rook,
	};
	ChessPieceType boardState[m_rows][m_cols] = {};
	

private:
	bool isMoveValid(Move);
	int m_turns;
	bool m_color = 1; // negative when white, positive when black
	static int m_rows = 7;
	static int m_cols = 7;
}
#endif
