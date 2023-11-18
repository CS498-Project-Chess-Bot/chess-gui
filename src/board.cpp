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

bool Board::isClear(Move moveObject)
{
    int startPosX, startPosY, endPosX, endPosY;
    std::tie(startPosX, startPosY) = moveObject.getStartTile();
    std::tie(endPosX, endPosY) = moveObject.getEndTile();
    ChessPieceType piece = moveObject.getPieceType();

    if (piece == white_knight || piece == black_knight)
        return true;

    int addToCol = 0;
    int addToRow = 0;

    if(startPosX > endPosX)
        addToCol -= 1;
    if(startPosX < endPosX)
        addToCol += 1;
    if(startPosY > endPosY)
        addToRow -= 1;
    if(startPosY < endPosY)
        addToRow += 1;

    int currentCol = startPosX + addToCol;
    int currentRow = startPosY + addToRow;

    //std::cout << startPosX << ", " << startPosY << " " << currentCol << ", " << currentRow << " " << endPosX << ", " << endPosY << std::endl;

    while((endPosX != currentCol) || (endPosY != currentRow)){
        if(boardState[currentRow][currentCol] != none) return false;
        currentCol += addToCol;
        currentRow += addToRow;
    }   return true;

}

bool Board::isOwnPiece(Move moveObject)
{
    int startPosX, startPosY, endPosX, endPosY;
    std::tie(startPosX, startPosY) = moveObject.getStartTile();
    std::tie(endPosX, endPosY) = moveObject.getEndTile();
    ChessPieceType piece = moveObject.getPieceType();
    if (((((int)piece) * (int)boardState[endPosY][endPosX]) > 0)) return true;
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
MoveResult Board::makeMove(Move moveObject)
{
    int startPosX, startPosY, endPosX, endPosY;
    std::tie(startPosX, startPosY) = moveObject.getStartTile();
    std::tie(endPosX, endPosY) = moveObject.getEndTile();
    ChessPieceType piece = moveObject.getPieceType();

    MoveResult res;
    if (((res = isMoveValid(moveObject)) != MoveResult::Invalid) && isClear(moveObject)) {
        m_turns++;
        m_color = !m_color;
        boardState[startPosY][startPosX] = none;
        boardState[endPosY][endPosX] = piece;
        if (isCheck(moveObject) > 0) {
            m_check = true;
            isCheckMate(moveObject);
        }
        else m_check = false;

        if(piece == white_king) {
            whiteCanCastleKing = false;
            whiteCanCastleQueen = false;
        }
        else if(piece == black_king) {
            blackCanCastleKing = false;
            blackCanCastleQueen = false;
        }
        else if(piece == white_rook) {
            if(startPosX == 0) {
                whiteCanCastleQueen = false;
            }
            else if(startPosX == 7) {
                whiteCanCastleKing = false;
            }
        }
        else if(piece == black_rook) {
            if(startPosX == 0) {
                blackCanCastleQueen = false;
            }
            else if(startPosX == 7) {
                blackCanCastleKing = false;
            }
        }

        return res;
    }

    return MoveResult::Invalid;
}

bool Board::findKnight(Move moveObject)
{
    int startPosX, startPosY;
    std::tie(startPosX, startPosY) = moveObject.getStartTile();
    ChessPieceType piece = moveObject.getPieceType();
    ChessPieceType searchPiece = none;
    if ((int)piece > 0) searchPiece = black_knight;
    else searchPiece = white_knight;

    int x[] = { 2, 2, -2, -2,
                1, 1, -1, -1 };
    int y[] = { 1, -1, 1, -1,
                2, -2, 2, -2 };
    for (int k = 0; k < 8; k++) {
        int m = startPosY + x[k];
        int n = startPosX + y[k];
        if (checkTileCoordInBounds(m, n) && boardState[m][n] == searchPiece) return true;
    }
    return false;
}

bool Board::findRook(Move moveObject, bool isQueen)
{
    int startPosX, startPosY;
    std::tie(startPosX, startPosY) = moveObject.getStartTile();
    ChessPieceType piece = moveObject.getPieceType();
    ChessPieceType searchPiece = none;
    int k = 0;
    if ((int)piece > 0) {
        if (isQueen) searchPiece = black_queen;
        else searchPiece = black_rook;
    }
    else {
        if (isQueen) searchPiece = white_queen;
        else searchPiece = white_rook;
    }

    while (checkTileCoordInBounds(startPosY + ++k, startPosX)) {
        if (boardState[startPosY + k][startPosX] == searchPiece) return true;
        if (boardState[startPosY + k][startPosX] != none) break;
    }

    k = 0;
    while (checkTileCoordInBounds(startPosY + --k, startPosX)) {
        if (boardState[startPosY + k][startPosX] == searchPiece) return true;
        if (boardState[startPosY + k][startPosX] != none) break;
    }

    k = 0;
    while (checkTileCoordInBounds(startPosY, startPosX + ++k)) {
        if (boardState[startPosY][startPosX + k] == searchPiece) return true;
        if (boardState[startPosY][startPosX + k] != none) break;
    }

    k = 0;
    while (checkTileCoordInBounds(startPosY, startPosX + --k)) {
        if (boardState[startPosY][startPosX + k] == searchPiece) return true;
        if (boardState[startPosY][startPosX + k] != none) break;
    }
    return false;
}

bool Board::findBishop(Move moveObject, bool isQueen)
{
    int startPosX, startPosY;
    std::tie(startPosX, startPosY) = moveObject.getStartTile();
    ChessPieceType piece = moveObject.getPieceType();
    ChessPieceType searchPiece = none;
    int k = 0;
    if ((int)piece > 0) {
        if (isQueen) searchPiece = black_queen;
        else searchPiece = black_bishop;
    }
    else {
        if (isQueen) searchPiece = white_queen;
        else searchPiece = white_bishop;
    }

    while (checkTileCoordInBounds(startPosY + k, startPosX + k)) {
        if (boardState[startPosY + k][startPosX + k] == searchPiece) return true;
        if (boardState[startPosY + k][startPosX + k] != none) break;
        k++;
    }

    k = 0;
    while (checkTileCoordInBounds(startPosY + k, startPosX - k)) {
        if (boardState[startPosY + k][startPosX - k] == searchPiece) return true;
        if (boardState[startPosY + k][startPosX - k] != none) break;
        k++;
    }

    k = 0;
    while (checkTileCoordInBounds(startPosY - k, startPosX + k)) {
        if (boardState[startPosY - k][startPosX + k] == searchPiece) return true;
        if (boardState[startPosY - k][startPosX + k] != none) break;
        k++;
    }

    k = 0;
    while (checkTileCoordInBounds(startPosY - k, startPosX - k)) {
        if (boardState[startPosY - k][startPosX - k] == searchPiece) return true;
        if (boardState[startPosY - k][startPosX - k] != none) break;
        k++;
    }
    return false;
}

bool Board::findPawn(Move moveObject)
{
    int startPosX, startPosY;
    std::tie(startPosX, startPosY) = moveObject.getStartTile();
    ChessPieceType piece = moveObject.getPieceType();
    ChessPieceType searchPiece = none;
    if ((int)piece > 0) {
        searchPiece = black_pawn;
        if (checkTileCoordInBounds(startPosY + 1, startPosX - 1) && boardState[startPosY + 1][startPosX - 1] == searchPiece) return true;
        if (checkTileCoordInBounds(startPosY + 1, startPosX + 1) && boardState[startPosY + 1][startPosX + 1] == searchPiece) return true;
    }
    else {
        searchPiece = white_pawn;
        if (checkTileCoordInBounds(startPosY - 1, startPosX - 1) && boardState[startPosY - 1][startPosX - 1] == searchPiece) return true;
        if (checkTileCoordInBounds(startPosY - 1, startPosX + 1) && boardState[startPosY - 1][startPosX + 1] == searchPiece) return true;
    }
    return false;
}

bool Board::findQueen(Move moveObject)
{
    if (findBishop(moveObject, true) || findRook(moveObject, true)) return true;
    return false;
}

bool Board::findKing(Move moveObject)
{
    int startPosX, startPosY;
    std::tie(startPosX, startPosY) = moveObject.getStartTile();
    ChessPieceType piece = moveObject.getPieceType();
    ChessPieceType searchPiece = none;
    if ((int)piece > 0) searchPiece = black_king;
    else searchPiece = white_king;
    int x[] = { -1, -1, -1, 0,
                 0, 1, 1, 1 };
    int y[] = { -1, 0, 1, -1,
                 1, -1, 0, 1 };
    for (int k = 0; k < 8; k++) {
        int m = startPosY + x[k];
        int n = startPosX + y[k];
        if (checkTileCoordInBounds(m, n) && boardState[m][n] == searchPiece) return true;
    }
    return false;
}

int Board::isCheck(Move moveObject)
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (boardState[i][j] == white_king) { // white king is in check
                if (findKnight(moveObject)) return 1;
                if (findPawn(moveObject)) return 1;
                if (findRook(moveObject, false)) return 1;
                if (findBishop(moveObject, false)) return 1;
                if (findQueen(moveObject)) return 1;
                if (findKing(moveObject)) return 1;
            }

            if (boardState[i][j] == black_king) { // black king is in check
                if (findKnight(moveObject)) return 2;
                if (findPawn(moveObject)) return 2;
                if (findRook(moveObject, false)) return 2;
                if (findBishop(moveObject, false)) return 2;
                if (findQueen(moveObject)) return 2;
                if (findKing(moveObject)) return 2;
            }
        }
    }
    return 0; // no one is in check
}


bool Board::isCheckMate(Move moveObject)
{
    int endPosX, endPosY;
    std::tie(endPosX, endPosY) = moveObject.getEndTile();
    if (isMoveValid(moveObject) && m_check) {
        if (boardState[endPosY][endPosX] == white_king && isCheck(moveObject) == 1) {
            gameEnd = true;
            return true;
        }
        else if (boardState[endPosY][endPosX] == black_king && isCheck(moveObject) == 2) {
            gameEnd = true;
            return true;
        }
    }
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

    m_turns = 0;
    m_captureCount = 0;
    whiteCanCastleKing = true;
    whiteCanCastleQueen = true;
    blackCanCastleKing = true;
    blackCanCastleQueen = true;
}

int Board::getTurnCount() const
{
    int turnCount = (m_turns / 2)+1;
    return turnCount;
}

MoveResult Board::isMoveValid(Move moveObject)
{
    int startPosX, startPosY, endPosX, endPosY;
    std::tie(startPosX, startPosY) = moveObject.getStartTile();
    std::tie(endPosX, endPosY) = moveObject.getEndTile();
    ChessPieceType piece = moveObject.getPieceType();
    bool isOppPiece = isOpposingPiece(moveObject);
    bool isTeamPiece = isOwnPiece(moveObject);
    bool isOccupied = isOppPiece || isTeamPiece;
    int distanceX = std::abs(endPosX - startPosX);
    int distanceY = std::abs(endPosY - startPosY);

    if(piece == none) return MoveResult::Invalid;
    if((int)piece > 0 && !isWhiteTurn()) return MoveResult::Invalid;
    if((int)piece < 0 && isWhiteTurn()) return MoveResult::Invalid;

    if (piece == white_pawn || piece == black_pawn) {

        bool team = (piece == white_pawn);
       
        if (piece == black_pawn && (endPosY - startPosY) > 0) return MoveResult::Invalid; // check for direction
        else if (piece == white_pawn && (endPosY - startPosY) < 0) return MoveResult::Invalid; // check for direction
            
        if(distanceX == 0 && !isOccupied){
            if (distanceY == 2){
                if(team && startPosY == 1) return MoveResult::Standard;
                else if(!team && startPosY == 6) return MoveResult::Standard;
                //save coordinates of where the pawn is for a potential enpessant
                //turn on boolean value to erase coords in the next turn
            }
            if(distanceY == 1) 
                return MoveResult::Standard;
        }
        else if(distanceX == 1 && distanceY == 1 && isOppPiece)
            return MoveResult::Standard;

    }

    // if rook
    if (piece == white_rook || piece == black_rook) {
        if ((startPosX == endPosX) || (startPosY == endPosY)) { //if on same rank or file
            //if the coords are in the right spot in relation to en pessant, 
            //adjust boardstate respectively
            //return unique en pessant value for app to facilitate movement
            if (!isTeamPiece) 
                return MoveResult::Standard;      //and not blocked
        }
    }


    // if knight
    if (piece == black_knight || piece == white_knight) {
        if ((distanceX*distanceX+distanceY*distanceY) == 5){ 
            if(!isTeamPiece) 
                return MoveResult::Standard;
        }
    }

    //else if queen
    if (piece == white_queen || piece == black_queen) {
        if (endPosX == startPosX || endPosY == startPosY || distanceX == distanceY) {
            if (!isTeamPiece) 
                return MoveResult::Standard; 
        }
    }
    

    // if bishop
    if (piece == white_bishop || piece == black_bishop) {
        if (distanceX == distanceY) {
            if (!isTeamPiece) 
                return MoveResult::Standard;
        }
    }

    //else (king case)
    if (piece == white_king || piece == black_king) {
        //if castling
        if(distanceX == 2 && piece == white_king) {
            if((whiteCanCastleKing && startPosX < endPosX) || (whiteCanCastleQueen && startPosX > endPosX)) {
                std::cout << "valid castle\n";
                return MoveResult::Castle;
            }
        }
        else if(distanceX == 2 && piece == black_king) {
            if((blackCanCastleKing && startPosX < endPosX) || (blackCanCastleQueen && startPosX > endPosX)) {
                return MoveResult::Castle;
            }
        }
            //if king hasn't moved and rook in the corner haven't moved
            //if king can pass to new square without seeing check
            //if castling is initiated
            //move king and rook -> return different value to trigger piece movement in app
        if(distanceX <= 1 && distanceY <= 1) {
            if (!isTeamPiece)
                return MoveResult::Standard; 
        }
    }

    return MoveResult::Invalid;
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
