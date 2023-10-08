#ifndef CHESSTILE_HPP
#define CHESSTILE_HPP
#include "object.hpp"
#include "chess_piece_2D.hpp"

const static std::vector<float> TILE_QUAD_VERTICES = {
         0.5f,  0.5f, 0.0f,    
         0.5f, -0.5f, 0.0f,  
        -0.5f, -0.5f, 0.0f,   
        -0.5f,  0.5f, 0.0f, 
    };

const static std::vector<uint32_t> TILE_QUAD_INDICES = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

class ChessTileModel2D : public Object {
public:
    ChessTileModel2D(bool isWhiteTile = true);
    ~ChessTileModel2D() override;

    void setExtraUniforms() override;  

private:
    bool m_isWhiteTile;

};


#endif