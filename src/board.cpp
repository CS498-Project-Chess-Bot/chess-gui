#include "board.hpp"

Board::Board(std::string FEN)
{
    using enum ChessPieceType;
    int row = 7;
    int col = 0;
    ChessPieceType piece;

    for (char c : FEN) {
        if (c == '')
            break;
        // '/' denotes end of row, subtract from row and reset col
        if (c == '/') 
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
            switch (char c) {
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

void Board::makeMove(Move)
{
    if (isMoveValid()) {
        m_turns++;
        m_color = m_color * -1;
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
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            boardState[i][j] = defaultBoard[i][j];
        }
    }
}

int Board::getTurnCount()
{
    turnCount = m_turns % 2;
    return turnCount;
}


bool Board::isMoveValid(Move)
{
    return false;
}
