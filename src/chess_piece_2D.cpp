#include "chess_piece_2D.hpp"
#include "buffer.hpp"

static std::string getChessPieceFragShaderLoc(ChessPieceType type) {
    switch(type) {
        case ChessPieceType::white_pawn:
            return "shaders/chess_piece.fs";
            break;
        default:
            CORE_ASSERT(false, "This chess piece doesn't have a fragment shader!");
            return "";
    }
}

static std::string getChessPieceVertShaderLoc(ChessPieceType type) {
    switch(type) {
        case ChessPieceType::white_pawn:
            return "shaders/chess_piece.vs";
            break;
        default:
            CORE_ASSERT(false, "This chess piece doesn't have a fragment shader!");
            return "";
    }
}

static std::string getChessPieceTextureLoc(ChessPieceType type) {
    switch(type) {
        case ChessPieceType::white_pawn:
            return "textures/chess_white_pawn.png";
            break;
        default:
            CORE_ASSERT(false, "This chess piece doesn't have a fragment shader!");
            return "";
    }
}

ChessPieceModel2D::ChessPieceModel2D() 
    :ChessPieceModel2D(ChessPieceType::white_pawn)
{}


ChessPieceModel2D::ChessPieceModel2D(ChessPieceType type) 
    : m_type(type)
{

    std::shared_ptr<VertexBuffer> vbo = std::make_shared<VertexBuffer>(QUAD_VERTICES);
    BufferLayout layout = {
        BufferElement(ShaderDataType::Float3, "Position"),
        BufferElement(ShaderDataType::Float2, "TexCoord")
    };
    vbo->setLayout(layout);

    std::shared_ptr<IndexBuffer> ibo = std::make_shared<IndexBuffer>(QUAD_INDICES);

    m_VAO = std::make_shared<VertexArray>();
    m_VAO->addVertexBuffer(vbo);
    m_VAO->setIndexBuffer(ibo);

    m_shader = std::make_shared<Shader>(getChessPieceVertShaderLoc(type).c_str(), getChessPieceFragShaderLoc(type).c_str());
    
    m_texture = std::make_shared<Texture>(getChessPieceTextureLoc(type).c_str());
    m_shader->setTexture("textureSlot", *m_texture);

}

ChessPieceModel2D::~ChessPieceModel2D() {}

void ChessPieceModel2D::setExtraUniforms() {

}