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

bool Board::isPathBlocked(Move moveObject)
{
    int startPosX, startPosY, endPosX, endPosY;
    std::tie(startPosX, startPosY) = moveObject.getStartTile();
    std::tie(endPosX, endPosY) = moveObject.getEndTile();
    ChessPieceType piece = moveObject.getPieceType();

    if (piece == white_pawn || piece == black_pawn) {
        int distanceY = std::abs(endPosY - startPosY);
        if ((startPosY == 1 || startPosY == 6) && (distanceY == 2)) {
            for (int i = startPosY + 1; i < endPosY; i++) {
                if (boardState[endPosY][i] != none) return true;
            }
            return false;
        }
        return false;
    }


    if (piece == white_rook || piece == black_rook) {
        if (startPosY < endPosY) {
            for (int i = startPosY + 1; i < endPosY; i++) {
                if (boardState[i][endPosX] != none) return true;
            }
            return false;
        }
        else if (startPosY > endPosY) {
            for (int i = startPosY - 1; i > endPosY; i--) {
                if (boardState[i][endPosX] != none) return true;
            }
            return false;
        }
        else if (startPosX < endPosX) {
            for (int i = startPosX + 1; i < endPosX; i++) {
                if (boardState[endPosY][i] != none) return true;
            }
            return false;
        }
        else if (startPosX > endPosX) {
            for (int i = startPosX - 1; i > endPosX; i--) {
                if (boardState[endPosY][i] != none) return true;
            }
            return false;
        }
        else return false;
    }

    if (piece == white_bishop || piece == black_bishop) {
        if (startPosY < endPosY && startPosX < endPosX) {
            int j = startPosX;
            for (int i = startPosY + 1; i < endPosY; i++) {
                j++;
                if (boardState[i][j] != none) return true;
            }
            return false;
        }
        else if (startPosY < endPosY && startPosX > endPosX) {
            int j = startPosX;
            for (int i = startPosY + 1; i < endPosY; i++) {
                j--;
                if (boardState[i][j] != none) return true;
            }
            return false;
        }
        else if (startPosY > endPosY && startPosX > endPosX) {
            int j = startPosX;
            for (int i = startPosY - 1; i > endPosY; i--) {
                j--;
                if (boardState[i][j] != none) return true;
            }
            return false;
        }
        else if (startPosY > endPosY && startPosX < endPosX) {
            int j = startPosX;
            for (int i = startPosY - 1; i > endPosY; i--) {
                j++;
                if (boardState[i][j] != none) return true;
            }
            return false;
        }
        else return false;
    }

    if (piece == white_queen || piece == black_queen) {
        if (startPosY < endPosY) {
            for (int i = startPosY + 1; i < endPosY; i++) {
                if (boardState[i][endPosX] != none) return true;
            }
            return false;
        }
        else if (startPosY > endPosY) {
            for (int i = startPosY - 1; i > endPosY; i--) {
                if (boardState[i][endPosX] != none) return true;
            }
            return false;
        }
        else if (startPosX < endPosX) {
            for (int i = startPosX + 1; i < endPosX; i++) {
                if (boardState[endPosY][i] != none) return true;
            }
            return false;
        }
        else if (startPosX > endPosX) {
            for (int i = startPosX - 1; i > endPosX; i--) {
                if (boardState[endPosY][i] != none) return true;
            }
            return false;
        }
        else if (startPosY < endPosY && startPosX < endPosX) {
            int j = startPosX;
            for (int i = startPosY + 1; i < endPosY; i++) {
                j++;
                if (boardState[i][j] != none) return true;
            }
            return false;
        }
        else if (startPosY < endPosY && startPosX > endPosX) {
            int j = startPosX;
            for (int i = startPosY + 1; i < endPosY; i++) {
                j--;
                if (boardState[i][j] != none) return true;
            }
            return false;
        }
        else if (startPosY > endPosY && startPosX > endPosX) {
            int j = startPosX;
            for (int i = startPosY - 1; i > endPosY; i--) {
                j--;
                if (boardState[i][j] != none) return true;
            }
            return false;
        }
        else if (startPosY > endPosY && startPosX < endPosX) {
            int j = startPosX;
            for (int i = startPosY - 1; i > endPosY; i--) {
                j++;
                if (boardState[i][j] != none) return true;
            }
            return false;
        }

        else return false;
    }
    else return false;
}

bool Board::isOwnPiece(Move moveObject)
{
    int startPosX, startPosY, endPosX, endPosY;
    std::tie(startPosX, startPosY) = moveObject.getStartTile();
    std::tie(endPosX, endPosY) = moveObject.getEndTile();
    ChessPieceType piece = moveObject.getPieceType();
    if (((((int)piece) * (int)boardState[endPosY][endPosX]) > 0))
        return true;
    else return false;
}

bool Board::isOpposingPiece(Move moveObject)
{
    int startPosX, startPosY, endPosX, endPosY;
    std::tie(startPosX, startPosY) = moveObject.getStartTile();
    std::tie(endPosX, endPosY) = moveObject.getEndTile();
    ChessPieceType piece = moveObject.getPieceType();
    if ((((int)piece) * (int)boardState[endPosY][endPosX]) < 0) { // opposing piece at destination
        m_captureCount++;
        return true;
    }
    else return false;
}

// Pass in inputs from Move class
bool Board::makeMove(Move moveObject)
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
        return true;
    }

    return false;
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

bool Board::isMoveValid(Move moveObject)
{
    int startPosX, startPosY, endPosX, endPosY;
    std::tie(startPosX, startPosY) = moveObject.getStartTile();
    std::tie(endPosX, endPosY) = moveObject.getEndTile();
    ChessPieceType piece = moveObject.getPieceType();

    if(piece == none) return false;
    if((int)piece > 0 && !isWhiteTurn()) return false;
    if((int)piece < 0 && isWhiteTurn()) return false;

    if (piece == white_pawn || piece == black_pawn) {
        int distanceX = std::abs(endPosX - startPosX);
        int distanceY = std::abs(endPosY - startPosY);
        if (piece == black_pawn && (endPosY - startPosY) > 0) return false; // check for direction
        else if (piece == white_pawn && (endPosY - startPosY) < 0) return false; // check for direction
        else if ((startPosY == 1 || startPosY == 6) && (distanceY == 2) && (distanceX == 0 || distanceX == 1)) { //pawn first move if moving 2
            if (isPathBlocked(moveObject)) return false;
            else if ((distanceX == 1 && distanceY == 1) && isOpposingPiece(moveObject)) return true;
            else if (isOwnPiece(moveObject)) return false; // own piece at destination
            else return true;
        }
        else if (distanceY == 1 && distanceX == 0) { // move straight forward
            if (isPathBlocked(moveObject)) return false;
            if (boardState[endPosY][endPosX] != none) return false;
            else if (isOwnPiece(moveObject)) return false; // own piece at destination
            else return true;
        }
        else if ((distanceX == 1 && distanceY == 1) && isOpposingPiece(moveObject)) { // move diagonal one to capture
            return true;
        }
        else {
            return false;
        }
    }

// if rook
    if (piece == white_rook || piece == black_rook) {
        if ((startPosX == endPosX) || (startPosY == endPosY)) {
            if ((startPosX != endPosX) && (startPosY != endPosY)) return false; // moved diagonal
            else if (isPathBlocked(moveObject)) return false;
            else if (isOwnPiece(moveObject)) return false; // own piece at destination
            else if (isOpposingPiece(moveObject)) return true;
            else return true;
        }
        else
            return false;
    }

// if knight
    if (piece == black_knight || piece == white_knight) {
        int absX = std::abs(endPosX-startPosX);
        int absY = std::abs(endPosY-startPosY);
        if ((absX*absX+absY*absY) == 5) {
            if(isOwnPiece(moveObject)) return false;
            if(boardState[endPosY][endPosX] != none){
                m_captureCount++;
            }
            return true;
        }
        else
            return false;    
    }
//
//else if queen
    if (piece == white_queen || piece == black_queen) {
        if (endPosX == startPosX || endPosY == startPosY || std::abs(endPosX - startPosX) == std::abs(endPosY - startPosY)) {
            if (isPathBlocked(moveObject)) return false;
            else if (isOwnPiece(moveObject)) return false; // own piece at destination
            else if (isOpposingPiece(moveObject)) return true;
            else return true;
        }
        else
            return false;
    }

// if bishop
    if (piece == white_bishop || piece == black_bishop) {
        if (std::abs(endPosX - startPosX) == std::abs(endPosY - startPosY)) {
            if (isPathBlocked(moveObject)) return false;
            else if (isOwnPiece(moveObject)) return false; // own piece at destination
            else if (isOpposingPiece(moveObject)) return true;
            else return true;
        }
        else
            return false;
      }


//else (king case)
    if (piece == white_king || piece == black_king) {
        if(std::abs(endPosX - startPosX) <= 1 && std::abs(endPosY - startPosY) <= 1){
            if (isOwnPiece(moveObject)) return false; // own piece at destination
            else if (isOpposingPiece(moveObject)) return true;
            else return true;
        }
        else
            return false;
    }
    return true;
}

std::vector<ChessPieceType> Board::getBoardState() {
    std::vector<ChessPieceType> ret;
    for (auto& row : boardState) {
        for (auto& piece : row) {
            ret.push_back(piece);
        }
    }
    return ret;
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
