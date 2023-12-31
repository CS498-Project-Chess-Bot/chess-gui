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
        //CORE_ASSERT(false, "Tile X coordinate not in board!");
        return false;
    }
    if(y < 0 || y > m_rows-1) {
        //CORE_ASSERT(false, "Tile Y coordinate not in board!");
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
    if(isGameOver) {
        return MoveResult::GameOver;
    }

    int startPosX, startPosY, endPosX, endPosY;
    std::tie(startPosX, startPosY) = moveObject.getStartTile();
    std::tie(endPosX, endPosY) = moveObject.getEndTile();
    ChessPieceType piece = moveObject.getPieceType();
    

    MoveResult res;
    if (((res = isMoveValid(moveObject)) != MoveResult::Invalid)) {
        boardState[startPosY][startPosX] = none;
        boardState[endPosY][endPosX] = piece;
        m_turns++;
        m_color = !m_color;
        m_check = isCheck(moveObject);

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

        int saveEnPassantX = epX1;
        int saveEnPassantY = epY1;

        if(isCheckMate(moveObject)) {
            isGameOver = true;
            endState = isWhiteTurn() ? GameOverState::BlackWin : GameOverState::WhiteWin;
            return MoveResult::GameOver;
        }
        else if(isStalemate()) {
            isGameOver = true;
            endState = GameOverState::Draw;
            return MoveResult::GameOver;
        }

        epX1 = saveEnPassantX;
        epY1 = saveEnPassantY;

        return res;
    }

    return MoveResult::Invalid;
}

bool Board::findKnight(Move moveObject, int i, int j, int c)
{
    ChessPieceType searchPiece = none;
    if (c == 1) searchPiece = black_knight;
    else if (c == 2)searchPiece = white_knight;
    else return false;

    int x[] = { 2, 2, -2, -2,
                1, 1, -1, -1 };
    int y[] = { 1, -1, 1, -1,
                2, -2, 2, -2 };
    for (int k = 0; k < 8; k++) {
        int m = i + x[k];
        int n = j + y[k];
        if (checkTileCoordInBounds(m, n) && boardState[m][n] == searchPiece) return true;
    }
    return false;
}

bool Board::findRook(Move moveObject, int i, int j, bool isQueen, int c)
{
    ChessPieceType searchPiece = none;
    int k = 0;
    if (c == 1) {
        if (isQueen) searchPiece = black_queen;
        else searchPiece = black_rook;
    }
    else if (c == 2) {
        if (isQueen) searchPiece = white_queen;
        else searchPiece = white_rook;
    }
    else return false; 

    while (checkTileCoordInBounds(i + ++k, j)) {
        if (boardState[i + k][j] == searchPiece) return true;
        if (boardState[i + k][j] != none) break;
    }

    k = 0;
    while (checkTileCoordInBounds(i + --k, j)) {
        if (boardState[i + k][j] == searchPiece) return true;
        if (boardState[i + k][j] != none) break;
    }

    k = 0;
    while (checkTileCoordInBounds(i, j + ++k)) {
        if (boardState[i][j + k] == searchPiece) return true;
        if (boardState[i][j + k] != none) break;
    }

    k = 0;
    while (checkTileCoordInBounds(i, j + --k)) {
        if (boardState[i][j + k] == searchPiece) return true;
        if (boardState[i][j + k] != none) break;
    }
    return false;
}

bool Board::findBishop(Move moveObject, int i, int j, bool isQueen, int c)
{
    ChessPieceType searchPiece = none;
    int k = 1;
    if (c == 1) {
        if (isQueen) searchPiece = black_queen;
        else searchPiece = black_bishop;
    }
    else if (c == 2) {
        if (isQueen) searchPiece = white_queen;
        else searchPiece = white_bishop;
    }
    else return false;

    while (checkTileCoordInBounds(i + k, j + k)) {
        if (boardState[i + k][j + k] == searchPiece) return true;
        if (boardState[i + k][j + k] != none) break;
        ++k;
    }

    k = 1;
    while (checkTileCoordInBounds(i + k, j - k)) {
        if (boardState[i + k][j - k] == searchPiece) return true;
        if (boardState[i + k][j - k] != none) break;
        ++k;
    }

    k = 1;
    while (checkTileCoordInBounds(i - k, j + k)) {
        if (boardState[i - k][j + k] == searchPiece) return true;
        if (boardState[i - k][j + k] != none) break;
        ++k;
    }

    k = 1;
    while (checkTileCoordInBounds(i - k, j - k)) {
        if (boardState[i - k][j - k] == searchPiece) return true;
        if (boardState[i - k][j - k] != none) break;
        ++k;
    }
    return false;
}

bool Board::findPawn(Move moveObject, int i, int j, int c)
{
    ChessPieceType searchPiece = none;
    if (c == 1) {
        searchPiece = black_pawn;
        if (checkTileCoordInBounds(i + 1, j - 1) && boardState[i + 1][j - 1] == searchPiece) return true;
        if (checkTileCoordInBounds(i + 1, j + 1) && boardState[i + 1][j + 1] == searchPiece) return true;
    }
    else if (c == 2) {
        searchPiece = white_pawn;
        if (checkTileCoordInBounds(i - 1, j - 1) && boardState[i - 1][j - 1] == searchPiece) return true;
        if (checkTileCoordInBounds(i - 1, j + 1) && boardState[i - 1][j + 1] == searchPiece) return true;
    }
    return false;
}

bool Board::findQueen(Move moveObject, int i, int j, int c)
{
    if (findBishop(moveObject, i, j, true, c) || findRook(moveObject, i, j, true, c)) return true;
    return false;
}

bool Board::findKing(Move moveObject, int i, int j, int c)
{
    ChessPieceType searchPiece = none;
    if (c == 1) searchPiece = black_king;
    else if (c == 2) searchPiece = white_king;
    else return false;
    int x[] = { -1, -1, -1, 0,
                 0, 1, 1, 1 };
    int y[] = { -1, 0, 1, -1,
                 1, -1, 0, 1 };
    for (int k = 0; k < 8; k++) {
        int m = i + x[k];
        int n = j + y[k];
        if (checkTileCoordInBounds(m, n) && boardState[m][n] == searchPiece) return true;
    }
    return false;
}

int Board::isCheck(Move moveObject)
{
    int c = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (boardState[i][j] == white_king) { // white king is in check
                c = 1;
                if (findKnight(moveObject, i, j, c)) { 
                    return 1; 
                }
                if (findPawn(moveObject, i, j, c)){
                    return 1;
                } 
                if (findRook(moveObject, i, j, false, c)) return 1;
                if (findBishop(moveObject, i, j, false, c)) return 1;
                if (findQueen(moveObject, i, j, c)) return 1;
                if (findKing(moveObject, i, j, c)) return 1;
            }

            if (boardState[i][j] == black_king) { // black king is in check
                c = 2;
                if (findKnight(moveObject, i, j, c)) return 2;
                if (findPawn(moveObject, i, j, c)) return 2;
                if (findRook(moveObject, i, j, false, c)) return 2;
                if (findBishop(moveObject, i, j, false, c)) return 2;
                if (findQueen(moveObject, i, j, c)) return 2;
                if (findKing(moveObject, i, j, c)) return 2;
            }
        }
    }
    return 0; // no one is in check
}


bool Board::isCheckMate(Move moveObject)
{   
    std::vector<Move>movesVec = possibleMoves();
    int vecSize = movesVec.size();

    if(vecSize > 0) return false;

    if(m_check > 0) return true;
    return false;
}

bool Board::isStalemate()
{
    std::vector<Move>movesVec = possibleMoves();
    int vecSize = movesVec.size();

    if(vecSize > 0) return false;

    if(m_check == 0) return true;
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

    epX1 = -1;
    epX2 = -1;
    epY1 = -1;
    epY2 = -1;
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

    if(!isClear(moveObject)) return MoveResult::Invalid;

    // std::cout << moveObject << std::endl;
    // std::cout << *this << std::endl;

    if(piece != boardState[startPosY][startPosX]) {
        CORE_ASSERT(false, "Move piece is not the same as board state.");
    }
    auto temp_piece_end = boardState[endPosY][endPosX];
    boardState[startPosY][startPosX] = none;
    boardState[endPosY][endPosX] = piece;
    int temp_check = isCheck(moveObject);
    boardState[startPosY][startPosX] = piece;
    boardState[endPosY][endPosX] = temp_piece_end;

    int turn_val = m_color? 1 : 2;
    // std::cout << m_check << ", " << temp_check << ", " << turn_val << std::endl;
    if ((temp_check > 0 && turn_val==temp_check) || m_check > 0) {
        //CORE_ASSERT(false, "Illegal Move: In check!");
        return MoveResult::Invalid;
    }
    

    //get EnPassant coords from last turn and free up more for my turn
    epX2 = epX1; 
    epX1 = -1;
    epY2 = epY1; 
    epY1 = -1;
    if (piece == white_pawn || piece == black_pawn) {

        bool team = (piece == white_pawn);
       
        if (piece == black_pawn && (endPosY - startPosY) > 0) return MoveResult::Invalid; // check for direction
        else if (piece == white_pawn && (endPosY - startPosY) < 0) return MoveResult::Invalid; // check for direction
            
        //advancing
        if(distanceX == 0 && !isOccupied){
            if (distanceY == 2){
                //save coordinates of where the pawn is for a potential en passant
                epX1 = endPosX;
                epY1 = endPosY;
                if(team && startPosY == 1) return MoveResult::Standard;
                else if(!team && startPosY == 6) return MoveResult::Standard;
            }
            if(distanceY == 1) {
                if((team && endPosY == 7) || (!team && endPosY == 0)){ 
                    return MoveResult::Promotion;
                }
                return MoveResult::Standard;
            }
        }else if(distanceX == 1 && distanceY == 1){          //capturing
            if (isOppPiece){ 
                if((team && endPosY == 7) || (!team && endPosY == 0)){ 
                    return MoveResult::Promotion;
                }
                return MoveResult::Standard;
            }
            if (endPosX == epX2){
                if(team && epY2 + 1 == endPosY) 
                    return MoveResult::EnPassant; 
                if(!team && epY2 - 1 == endPosY)
                    return MoveResult::EnPassant;
            }
        }
    }

    if (piece == white_rook || piece == black_rook) {
        if ((startPosX == endPosX) || (startPosY == endPosY)) { 
            if (!isTeamPiece) 
                return MoveResult::Standard;     
        }
    }

    if (piece == black_knight || piece == white_knight) {
        if ((distanceX*distanceX+distanceY*distanceY) == 5){ 
            if(!isTeamPiece) 
                return MoveResult::Standard;
        }
    }

    if (piece == white_queen || piece == black_queen) {
        if (endPosX == startPosX || endPosY == startPosY || distanceX == distanceY) {
            if (!isTeamPiece) 
                return MoveResult::Standard;
        }
    }
    
    if (piece == white_bishop || piece == black_bishop) {
        if (distanceX == distanceY) {
            if (!isTeamPiece) 
                return MoveResult::Standard;
        }
    }

    if (piece == white_king || piece == black_king) {
        //castling
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
        //moving
        if(distanceX <= 1 && distanceY <= 1) {
            if (!isTeamPiece)
                return MoveResult::Standard; 
        }
    }

    return MoveResult::Invalid;
}

void Board::setBoardStateAt(int x, int y, ChessPieceType piece){
    std::cout << "promo" << std::endl;
    boardState[y][x] = piece;
}

std::vector<ChessPieceType> Board::getBoardState() {
    std::vector<ChessPieceType> ret;
    for (auto& row : boardState) {
        for (auto piece : row) {
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

    fen += ' ';

    std::string castleField = "";
    if(whiteCanCastleKing)
        castleField += 'K';
    if(whiteCanCastleQueen)
        castleField += 'Q';
    if(blackCanCastleKing)
        castleField += 'k';
    if(blackCanCastleQueen)
        castleField += 'q';
    if(castleField.empty())
        castleField += '-';
    fen += castleField;
    
    fen += ' ';
    if(epX1 > -1 && epY1 > -1) {
        fen += ('a' + epX1);
        fen += (epY1 >= 4) ? '6' : '3';
    }
    else fen += '-';
    fen += ' ';

    fen += std::to_string(m_turns);
    fen += " " + std::to_string(getTurnCount());

    return fen;

}
std::vector<Move> Board::possibleMoves() {
    Move moveObject;
    std::vector<Move> potentialMoves;

    for (int j = 0; j < 8; j++) {
        for (int i = 0; i < 8; i++) {
            auto piece = boardState[j][i];
            if (piece == white_pawn) {
                moveObject.setStart(i, j);
                moveObject.setEnd(i + 1, j);
                moveObject.setPiece(white_pawn);
                if (isMoveValid(moveObject) == MoveResult::Standard && checkTileCoordInBounds(i + 1, j)) potentialMoves.push_back(moveObject); // normal movement
                else if (i == 1) {
                    moveObject.setEnd(i + 2, j);
                    if (isMoveValid(moveObject) == MoveResult::Standard && checkTileCoordInBounds(i + 2, j)) potentialMoves.push_back(moveObject); // first move
                }
                moveObject.setEnd(i + 1, j + 1);

                if (isMoveValid(moveObject) == MoveResult::Standard && checkTileCoordInBounds(i + 1, j + 1)) potentialMoves.push_back(moveObject); // capture right
                moveObject.setEnd(i + 1, j - 1);
                
                if (isMoveValid(moveObject) == MoveResult::Standard && checkTileCoordInBounds(i + 1, j - 1)) potentialMoves.push_back(moveObject); // capture left
            }


            else if (piece == black_pawn) {
                moveObject.setStart(i, j);
                moveObject.setEnd(i - 1, j);
                moveObject.setPiece(black_pawn);
                
                if (isMoveValid(moveObject) == MoveResult::Standard && checkTileCoordInBounds(i - 1, j)) potentialMoves.push_back(moveObject); // normal movement
                else if (i == 6) {
                    moveObject.setEnd(i - 2, j);
                    
                    if (isMoveValid(moveObject) == MoveResult::Standard && checkTileCoordInBounds(i - 2, j)) potentialMoves.push_back(moveObject); // first move
                }
                moveObject.setEnd(i - 1, j + 1);
                
                if (isMoveValid(moveObject) == MoveResult::Standard && checkTileCoordInBounds(i - 1, j + 1)) potentialMoves.push_back(moveObject); // capture right
                moveObject.setEnd(i - 1, j - 1);
                
                if (isMoveValid(moveObject) == MoveResult::Standard && checkTileCoordInBounds(i - 1, j - 1)) potentialMoves.push_back(moveObject); // capture left
            }

            else if (piece == white_knight || piece == black_knight) {
                moveObject.setStart(i, j);
                if (piece == white_knight) moveObject.setPiece(white_knight);
                else if (piece == black_knight) moveObject.setPiece(black_knight);
                int x[] = { 2, 2, -2, -2,
                            1, 1, -1, -1 };
                int y[] = { 1, -1, 1, -1,
                            2, -2, 2, -2 };
                for (int k = 0; k < 8; k++) {
                    int m = i + x[k];
                    int n = j + y[k];
                    moveObject.setEnd(m, n);
                    
                    if (isMoveValid(moveObject) == MoveResult::Standard && checkTileCoordInBounds(m, n)) potentialMoves.push_back(moveObject);
                }
            }

            else if (piece == white_bishop || piece == black_bishop) {
                moveObject.setStart(i, j);
                if (piece == white_bishop) moveObject.setPiece(white_bishop);
                else if (piece == black_bishop) moveObject.setPiece(black_bishop);
                for (int x = 1; x < 8; x++) {
                    moveObject.setEnd(i + x, j + x);
                    
                    if (isMoveValid(moveObject) == MoveResult::Standard && checkTileCoordInBounds(i + x, j + x)) potentialMoves.push_back(moveObject); // up right
                    moveObject.setEnd(i + x, j - x);
                    
                    if (isMoveValid(moveObject) == MoveResult::Standard && checkTileCoordInBounds(i + x, j - x)) potentialMoves.push_back(moveObject); // up left
                    moveObject.setEnd(i - x, j + x);
                    
                    if (isMoveValid(moveObject) == MoveResult::Standard && checkTileCoordInBounds(i - x, j + x)) potentialMoves.push_back(moveObject); // down right
                    moveObject.setEnd(i - x, j - x);
                    
                    if (isMoveValid(moveObject) == MoveResult::Standard && checkTileCoordInBounds(i - x, j - x)) potentialMoves.push_back(moveObject); // down left
                }
            }

            else if (piece == white_rook || piece == black_rook) {
                moveObject.setStart(i, j);
                if (piece == white_rook) moveObject.setPiece(white_rook);
                else if (piece == black_rook) moveObject.setPiece(black_rook);
                for (int x = 1; x < 8; x++) {
                    moveObject.setEnd(i, j + x);
                    
                    if (isMoveValid(moveObject) == MoveResult::Standard && checkTileCoordInBounds(i, j + x)) potentialMoves.push_back(moveObject); // up 
                    moveObject.setEnd(i, j - x);
                    
                    if (isMoveValid(moveObject) == MoveResult::Standard && checkTileCoordInBounds(i, j - x)) potentialMoves.push_back(moveObject); // down
                    moveObject.setEnd(i - x, j);
                    
                    if (isMoveValid(moveObject) == MoveResult::Standard && checkTileCoordInBounds(i - x, j)) potentialMoves.push_back(moveObject); // left
                    moveObject.setEnd(i + x, j);
                    
                    if (isMoveValid(moveObject) == MoveResult::Standard && checkTileCoordInBounds(i + x, j)) potentialMoves.push_back(moveObject); // right
                }
            }

            else if (piece == white_queen || piece == black_queen) {
                moveObject.setStart(i, j);
                if (piece == white_queen) moveObject.setPiece(white_queen);
                else if (piece == black_queen) moveObject.setPiece(black_queen);
                for (int x = 1; x < 8; x++) {
                    moveObject.setEnd(i + x, j + x);
                    
                    if (isMoveValid(moveObject) == MoveResult::Standard && checkTileCoordInBounds(i + x, j + x)) potentialMoves.push_back(moveObject); // up right
                    moveObject.setEnd(i + x, j - x);
                    
                    if (isMoveValid(moveObject) == MoveResult::Standard && checkTileCoordInBounds(i + x, j - x)) potentialMoves.push_back(moveObject); // up left
                    moveObject.setEnd(i - x, j + x);
                    
                    if (isMoveValid(moveObject) == MoveResult::Standard && checkTileCoordInBounds(i - x, j + x)) potentialMoves.push_back(moveObject); // down right
                    moveObject.setEnd(i - x, j - x);
                    
                    if (isMoveValid(moveObject) == MoveResult::Standard && checkTileCoordInBounds(i - x, j - x)) potentialMoves.push_back(moveObject); // down left
                    moveObject.setEnd(i, j + x);
                    
                    if (isMoveValid(moveObject) == MoveResult::Standard && checkTileCoordInBounds(i, j + x)) potentialMoves.push_back(moveObject); // up 
                    moveObject.setEnd(i, j - x);
                    
                    if (isMoveValid(moveObject) == MoveResult::Standard && checkTileCoordInBounds(i, j - x)) potentialMoves.push_back(moveObject); // down
                    moveObject.setEnd(i - x, j);
                    
                    if (isMoveValid(moveObject) == MoveResult::Standard && checkTileCoordInBounds(i - x, j)) potentialMoves.push_back(moveObject); // left
                    moveObject.setEnd(i + x, j);
                    
                    if (isMoveValid(moveObject) == MoveResult::Standard && checkTileCoordInBounds(i + x, j)) potentialMoves.push_back(moveObject); // right
                }
            }

            else if (piece == white_king || piece == black_king) {
                moveObject.setStart(i, j);
                if (piece == white_king) moveObject.setPiece(white_king);
                else if (piece == black_king) moveObject.setPiece(black_king);
                int x[] = { -1, -1, -1, 0,
                             0, 1, 1, 1 };
                int y[] = { -1, 0, 1, -1,
                             1, -1, 0, 1 };
                for (int k = 0; k < 8; k++) {
                    int m = i + x[k];
                    int n = j + y[k];
                    moveObject.setEnd(m, n);
                    
                    if (isMoveValid(moveObject) == MoveResult::Standard && checkTileCoordInBounds(m, n)) potentialMoves.push_back(moveObject);
                }
            }
        }
    }
    

    return potentialMoves;
}
