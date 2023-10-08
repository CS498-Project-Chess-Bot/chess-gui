#ifndef CHESSPIECE2D_HPP
#define CHESSPIECE2D_HPP

#include "core.hpp"
#include "object.hpp"

const static std::vector<float> PIECE_QUAD_VERTICES = {
         0.5f,  0.5f, 0.0f,     1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,     1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,     0.0f, 1.0f  // top left 
    };

const static std::vector<uint32_t> PIECE_QUAD_INDICES = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

enum class ChessPieceType {
    black_king = -6,
    black_queen = -5,
    black_bishop = -4,
    black_knight = -3,
    black_rook = -2,
    black_pawn = -1,
    white_pawn = 1,
    white_rook = 2,
    white_knight = 3,
    white_bishop = 4,
    white_queen = 5,
    white_king = 6
};


class ChessPieceModel2D : public Object {
public:
    ChessPieceModel2D();
    ChessPieceModel2D(ChessPieceType type);
    ~ChessPieceModel2D() override;

    void setExtraUniforms() override;    

private:
    ChessPieceType m_type;
};

#endif