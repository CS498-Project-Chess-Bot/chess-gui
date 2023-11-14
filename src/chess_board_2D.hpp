#ifndef CHESSBOARD2D_HPP
#define CHESSBOARD2D_HPP

#include "chess_tile_2D.hpp"
#include "chess_piece_2D.hpp"
#include "board.hpp"

class ChessBoard2D : public Object {
public:
    ChessBoard2D(bool isPlayerWhite = true);
    ~ChessBoard2D();

    void setExtraUniforms() override;

    inline &Board getGameBoard() { return gameBoard; }
    bool tryMove(Move m);

private:
    Board gameBoard;
    bool isPlayerWhite;

};


#endif

