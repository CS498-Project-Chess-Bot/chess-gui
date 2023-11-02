#include "board.hpp"
using enum ChessPieceType;

// Reads in FEN string and converts it to 2D array
// TODO: add castling availability, en passant target square, halfmove clock, and fullmove number
Board::Board(std::string FEN)
{
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
                m_color = false;
            else
                m_color = true;
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
            CORE_ASSERT(false, "Piece is not yet initialized!");
        }
    }
}

Board::~Board(){
    m_turns = 0;
    m_captureCount = 0;
    resetBoard();
}

// Pass in inputs from Move class
void Board::makeMove(Move moveObject)
{
    int startPosX, startPosY, endPosX, endPosY;
    std::tie(startPosX, startPosY) = moveObject.getStartTile();
    std::tie(endPosX, endPosY) = moveObject.getEndTile();
    ChessPieceType piece = moveObject.getPieceType();
    
    if (isMoveValid(moveObject)) {
        m_turns++;
        m_color = !m_color;
        boardState[startPosX][startPosY] = none;
        boardState[endPosX][endPosY] = piece;
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
    int turnCount = m_turns / 2;
    return turnCount;
}

// TODO: make helper function isClear, figure out how to check piece at endPos
//       implement rook, king, queen, bishop
bool Board::isMoveValid(Move moveObject)
{
    int startPosX, startPosY, endPosX, endPosY;
    std::tie(startPosX, startPosY) = moveObject.getStartTile();
    std::tie(endPosX, endPosY) = moveObject.getEndTile();
    ChessPieceType piece = moveObject.getPieceType();

    //if pawn
    if (piece == white_pawn || piece == black_pawn) {
        if (endPosX < startPosX) {
            return false;
        }
        else if (m_turns == 1 && (endPosX > (startPosX + 2))) {
            return false;
        }
        else if (m_turns > 1 && (endPosX > (startPosX + 1))) {
            return false;
        }
        else if (endPosY != startPosY) {
            //check piece at endPos, if != m_color{m_captureCount++ / return true};
            return false;
        }
        else
            return false;
    }

// if rook
//	if (oldRow != newRow) or (oldColumn != newColumn)
//		if oldRow != newRow and oldColumn != newColumn return false (moved diagonal)
//		if pathBlocked return False
//		if noPieceAtDestination return True
//		if ownPieceAtDestination return False
//		if opposingPieceAtDestination return True, captureCount++
//	else return False
//
// if knight
    if (piece == black_knight || piece == white_knight) {
        if (((startPosX == endPosX + 1 || startPosX == endPosX - 1) && (startPosY == endPosY + 2 || startPosY == endPosY - 2)) || ((startPosX == endPosX + 2 || startPosX == endPosX - 2) && (startPosY == endPosY + 1 || startPosY == endPosY - 1))) {
            //check piece at endPos, if ownPiece return False
            m_captureCount++;
            return true;
        }
        else
            return false;    
    }
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
