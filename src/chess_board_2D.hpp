#ifndef CHESSBOARD2D_HPP
#define CHESSBOARD2D_HPP

#include "chess_tile_2D.hpp"
#include "chess_piece_2D.hpp"
#include "board.hpp"
#include "camera.hpp"

#define CHESS_ROWS 8
#define CHESS_COLS 8

class ChessBoardModel2D : public Object {
public:
    ChessBoardModel2D(bool isPlayerWhite = true);
    ~ChessBoardModel2D();

    inline Board& getGameBoard() { return m_gameBoard; }
    bool tryMove(Move m);
    bool getHitTile(Camera& cam, glm::vec3 rayDir, int* x, int* y);
    void setTileHightlight(int x, int y, bool b);
    inline void clearHightlighting() {
        for(auto& tile : m_children) {
            std::dynamic_pointer_cast<ChessTileModel2D>(tile)->setHighlight(false);
        }
    }

private:
    Board m_gameBoard;
    bool m_isPlayerWhite;

};


#endif

