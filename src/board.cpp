#include "board.hpp"

// Reads in FEN string and converts it to 2D array
// TODO: add castling availability, en passant target square, halfmove clock, and fullmove number
Board::Board(std::string FEN)
{
    using enum ChessPieceType;
    int row = 8;
    int col = 0;
    ChessPieceType piece;

    for (char c : FEN) {
        // '/' denotes end of row, subtract from row and reset col
        if (c == '/') {
            row--;
            col = 0;
        }
        // c is digit (for now) only when there are empty tiles
        else if (isdigit(c)) {
            int clearTiles = c - '0';
            for (int i = 0; i < clearTiles; i++) {
                boardState[row][col] = none;
                col++;
                }
        }
        // Active color
        else if (c == 'b' || c == 'w') {
            if (c == 'b')
                m_color = 1;
            else
                m_color = -1;
        }
        // piece case
        else {
            switch (c) {
            case 'p': piece = black_pawn; col++; break;
            case 'r': piece = black_rook; col++; break;
            case 'n': piece = black_knight; col++; break;
            case 'b': piece = black_bishop; col++; break;
            case 'q': piece = black_queen; col++; break;
            case 'k': piece = black_king; col++; break;
            case 'P': piece = white_pawn; col++; break;
            case 'R': piece = white_rook; col++; break;
            case 'N': piece = white_knight; col++; break;
            case 'B': piece = white_bishop; col++; break;
            case 'Q': piece = white_queen; col++; break;
            case 'K': piece = white_king; col++; break;
            default: break;
            }
            boardState[row][col] = piece;
        }
    }
    
   
}

Board::~Board(){}

// Pass in inputs from Move class - how?
void Board::makeMove(Move moveObject)
{
    if (isMoveValid(moveObject)) {
        m_turns++;
        m_color = m_color && -1;
        boardState[moveObject.m_startPosX][moveObject.m_startPosY] = none;
        boardState[moveObject.m_endPosX][moveObject.m_endPosY] = moveObject.m_piece;
    }
}

bool Board::isCheckMate()
{
    return false;
}

bool Board::isStalemate()
{
    return false;
}

void Board::resetBoard()
{
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            boardState[i][j] = defaultBoard[i][j];
        }
    }
}

int Board::getTurnCount()
{
    int turnCount = m_turns % 2;
    return turnCount;
}


bool Board::isMoveValid(Move moveObject)
{
    // if endTile isClear



    //if pawn
//	if newRow < oldRow {return false}
//	if firstMove and move > 2 return false
//	if !firstMove and move > 1 {return false}
//	if oldColumn != newColumn
//		if piece_moving_diagonal
//			if opposingPieceAtDestination {return true} captureCount++
//			else return false
//
//else if rook
//	if (oldRow != newRow) or (oldColumn != newColumn)
//		if oldRow != newRow and oldColumn != newColumn return false (moved diagonal)
//		if pathBlocked return False
//		if noPieceAtDestination return True
//		if ownPieceAtDestination return False
//		if opposingPieceAtDestination return True, captureCount++
//	else return False
//
//else if knight
//	if ((oldRow == newRow + 1 or oldRow == newRow - 1) and (oldColumn == newColumn - 2 or oldColumn == newColumn +2		)) or ((oldRow == newRow - 2 or oldRow == newRow + 2) and (oldColumn == newCOlumn - 1 or oldColumn == newColumn 		+1))
//			if ownPieceAtDestination return False
//			else return True
//	else return false
//
//else if queen
//else if bishop
//	if newRow == oldRow or newColumn == oldColumn {return false}
//	if pathBlocked return false
//	if opposingPieceAtDestination return true
//else (king case)
//	if (oldRow == newRow +- 1) or (oldColumn == newColumn +-1)
//		if ownPieceAtDestination return False
//		else true
//	else true
    return false;
}
