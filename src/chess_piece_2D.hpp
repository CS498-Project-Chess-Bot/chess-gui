#ifndef CHESSPIECE2D_HPP
#define CHESSPIECE2D_HPP

#include "core.hpp"
#include "object.hpp"
#include "move.hpp"

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