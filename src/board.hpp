#ifndef BOARD_HPP
#define BOARD_HPP

#include "core.hpp"
#include "move.hpp"

enum MoveResult {
	Castle,
	EnPassant,
	Standard,
	Promotion,
	GameOver,
	Invalid
};

class Board {
public:
	Board(std::string FEN);
	Board();
	~Board();
	MoveResult makeMove(Move moveObject);
	bool isCheckMate(Move moveObject);
	bool isStalemate();
	int isCheck(Move moveObject);
	inline bool isWhiteTurn() const {return m_color;}
	void resetBoard();
	int getTurnCount() const;
	std::vector<ChessPieceType> getBoardState();
	void setBoardStateAt(int x, int y, ChessPieceType piece);
	std::string toFEN() const;
	bool isGameOver = false;
	enum GameOverState {
		WhiteWin,
		BlackWin,
		Draw,
		None
	};
	GameOverState endState = GameOverState::None;

	friend std::ostream& operator<<(std::ostream& os, const Board& other);

	const static int m_rows = 8;
	const static int m_cols = 8;

private:
	MoveResult isMoveValid(Move);
	bool checkTileCoordInBounds(int x, int y) const;
	bool isClear(Move);
	bool isOwnPiece(Move);
	bool isOpposingPiece(Move);
	bool findKnight(Move, int, int, int);
	bool findRook(Move, int, int, bool, int);
	bool findBishop(Move, int, int, bool, int);
	bool findPawn(Move, int, int, int);
	bool findQueen(Move, int, int, int);
	bool findKing(Move, int, int, int);
	std::vector<Move> possibleMoves();
	int m_turns;
	int m_captureCount = 0;
	bool m_color = true; // true when white, false when black
	int m_check = 0;
	
	using enum ChessPieceType;
	static constexpr ChessPieceType defaultBoard[8][8] = {
		{white_rook, white_knight, white_bishop, white_queen, white_king, white_bishop, white_knight, white_rook},
		{white_pawn, white_pawn,   white_pawn,   white_pawn,  white_pawn, white_pawn,   white_pawn,   white_pawn},
		{none,       none,         none,         none,        none,       none,         none,         none},
		{none,       none,         none,         none,        none,       none,         none,         none},
		{none,       none,         none,         none,        none,       none,         none,         none},
		{none,       none,         none,         none,        none,       none,         none,         none},
		{black_pawn, black_pawn,   black_pawn,   black_pawn,  black_pawn, black_pawn,   black_pawn,   black_pawn},
		{black_rook, black_knight, black_bishop, black_queen, black_king, black_bishop, black_knight, black_rook}
	};
	ChessPieceType boardState[8][8] = {};

	bool whiteCanCastleQueen = true;
	bool whiteCanCastleKing = true;
	bool blackCanCastleQueen = true;
	bool blackCanCastleKing = true;

	int epX1 = -1;
	int epX2 = -1;
	int epY1 = -1;
	int epY2 = -1;
};

std::ostream& operator<<(std::ostream& out, Board& other) {
	for(int i = 0; i < other.m_rows; i++) {
		for(int j = 0; j < other.m_cols; j++) {
			std::cout << std::setw(3) << (int)other.getBoardState()[i * 8 + j] << " ";
		}
		std::cout << std::endl;
   	}
	return out;
}

#endif
