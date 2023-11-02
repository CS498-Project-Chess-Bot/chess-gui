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

Board::Board(){
    m_turns = 0;
    m_captureCount = 0;
    resetBoard();
}

Board::~Board() {

}

bool Board::checkTileCoordInBounds(int x, int y) const {
    if(x < 0 || x > m_cols-1){
        CORE_ASSERT(false, "Tile X coordinate not in board!");
        return false;
    }
    if(y < 0 || y > m_rows-1) {
        CORE_ASSERT(false, "Tile Y coordinate not in board!");
        return false;
    }
    return true;
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
        boardState[startPosY][startPosX] = none;
        boardState[endPosY][endPosX] = piece;
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

int Board::getTurnCount() const
{
    int turnCount = (m_turns / 2)+1;
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

    if(piece == none) return false;
    if((int)piece > 0 && !isWhiteTurn()) return false;
    if((int)piece < 0 && isWhiteTurn()) return false;

    //if pawn
    if (piece == white_pawn || piece == black_pawn) {
        if (endPosY < startPosY) {
            return false;
        }
        else if (getTurnCount() == 1 && (endPosY > (startPosY + 2))) {
            return false;
        }
        else if (getTurnCount() > 1 && (endPosY > (startPosY + 1))) {
            return false;
        }
        else if (endPosX != startPosX) {
            if(std::abs(endPosX - startPosX) > 1)return false;
            if((endPosY - startPosY) != 1) return false;
            if((((int)piece) * (int)boardState[endPosY][endPosY]) > 0) return false;
            return true;
        }
        else
            return true;
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
        int absX = std::abs(endPosX-startPosX);
        int absY = std::abs(endPosY-startPosY);
        if ((absX*absX+absY*absY) == 5) {
            if((((int)piece) * (int)boardState[endPosY][endPosY]) > 0) return false;
            if(boardState[endPosY][endPosX] == none){
                m_captureCount++;
            }
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
    return true;
}

std::string Board::toFEN() const {
    std::string fen = "";

    for(int row = m_rows-1; row >= 0; --row) { 
        int emptyTileCount = 0; 
        for(int col = 0; col < m_cols; ++col) {
            ChessPieceType piece = boardState[row][col];

            char fenChar = 0;
            switch(piece) {
                case white_pawn: fenChar = 'P'; break;
                case white_rook: fenChar = 'R'; break;
                case white_bishop: fenChar = 'B'; break;
                case white_knight: fenChar = 'N'; break;
                case white_king: fenChar = 'K'; break;
                case white_queen: fenChar = 'Q'; break;
                case black_pawn: fenChar = 'p'; break;
                case black_rook: fenChar = 'r'; break;
                case black_bishop: fenChar = 'b'; break;
                case black_knight: fenChar = 'n'; break;
                case black_king: fenChar = 'k'; break;
                case black_queen: fenChar = 'q'; break;
                case none: emptyTileCount++; break;
                default: CORE_ASSERT(false, "We have a serious problem!");
            }
            
            if(fenChar != 0) {
                if(emptyTileCount > 0){
                    fen += '0' + (char)emptyTileCount; 
                    emptyTileCount = 0;
                }
                
                fen += fenChar;
                
            }
            
        }
        if(emptyTileCount > 0){
            fen += '0' + (char)emptyTileCount; 
            emptyTileCount = 0;
        }
        fen += '/';
    }
    fen.pop_back();

    fen += ' ';
    fen += isWhiteTurn()? 'w' : 'b';
    fen += " - - ";
    fen += std::to_string(m_turns);
    fen += " " + std::to_string(getTurnCount());

    return fen;

}
