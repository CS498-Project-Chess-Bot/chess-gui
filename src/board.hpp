#ifndef BOARD_HPP
#define BOARD_HPP

#include "core.hpp"
#include "chess_piece_2D.hpp"
#include "move.hpp"

class Board {
public:
	Board(std::string FEN);
	~Board();
	void makeMove(Move moveObject);
	bool isCheckMate();
	bool isStalemate();
	void resetBoard();
	int getTurnCount();


private:
	bool isMoveValid(Move);
	int m_turns;
	int m_captureCount = 0;
	bool m_color = true; // true when white, false when black
	const static int m_rows = 8;
	const static int m_cols = 8;
	using enum ChessPieceType;
	ChessPieceType defaultBoard[8][8] = {
		white_rook, white_knight, white_bishop, white_queen, white_king, white_bishop, white_knight, white_rook,
		white_pawn, white_pawn,   white_pawn,   white_pawn,  white_pawn, white_pawn,   white_pawn,   white_pawn,
		none,       none,         none,         none,        none,       none,         none,         none,
		none,       none,         none,         none,        none,       none,         none,         none,
		none,       none,         none,         none,        none,       none,         none,         none,
		none,       none,         none,         none,        none,       none,         none,         none,
		black_pawn, black_pawn,   black_pawn,   black_pawn,  black_pawn, black_pawn,   black_pawn,   black_pawn,
		black_rook, black_knight, black_bishop, black_queen, black_king, black_bishop, black_knight, black_rook
	};
	ChessPieceType boardState[8][8] = {};
};
#endif
