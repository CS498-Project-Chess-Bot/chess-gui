#include "chess_piece_2D.hpp"
#include "buffer.hpp"
#include "texture_loader.hpp"

static std::string getChessPieceFragShaderLoc(ChessPieceType type) {
    switch(type) {
        case ChessPieceType::white_king:
        case ChessPieceType::white_queen:
        case ChessPieceType::white_rook:
        case ChessPieceType::white_knight:
        case ChessPieceType::white_bishop:
        case ChessPieceType::white_pawn:
        case ChessPieceType::black_king:
        case ChessPieceType::black_queen:
        case ChessPieceType::black_rook:
        case ChessPieceType::black_knight:
        case ChessPieceType::black_bishop:
        case ChessPieceType::black_pawn:
            return "shaders/chess_piece.fs";
        default:
            CORE_ASSERT(false, "This chess piece doesn't have a fragment shader!");
            return "";
    }
}

static std::string getChessPieceVertShaderLoc(ChessPieceType type) {
    switch(type) {
        case ChessPieceType::white_king:
        case ChessPieceType::white_queen:
        case ChessPieceType::white_rook:
        case ChessPieceType::white_knight:
        case ChessPieceType::white_bishop:
        case ChessPieceType::white_pawn:
        case ChessPieceType::black_king:
        case ChessPieceType::black_queen:
        case ChessPieceType::black_rook:
        case ChessPieceType::black_knight:
        case ChessPieceType::black_bishop:
        case ChessPieceType::black_pawn:
            return "shaders/chess_piece.vs";
        default:
            CORE_ASSERT(false, "This chess piece doesn't have a fragment shader!");
            return "";
    }
}

static std::string getChessPieceTextureLoc(ChessPieceType type) {
    switch(type) {
        case ChessPieceType::white_king:
            return "chess_white_king.png";
        case ChessPieceType::white_queen:
            return "chess_white_queen.png";
        case ChessPieceType::white_rook:
            return "chess_white_rook.png";
        case ChessPieceType::white_knight:
            return "chess_white_knight.png";
        case ChessPieceType::white_bishop:
            return "chess_white_bishop.png";
        case ChessPieceType::white_pawn:
            return "chess_white_pawn.png";
        case ChessPieceType::black_king:
            return "chess_black_king.png";
        case ChessPieceType::black_queen:
            return "chess_black_queen.png";
        case ChessPieceType::black_rook:
            return "chess_black_rook.png";
        case ChessPieceType::black_knight:
            return "chess_black_knight.png";
        case ChessPieceType::black_bishop:
            return "chess_black_bishop.png";
        case ChessPieceType::black_pawn:
            return "chess_black_pawn.png";
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

    Ref<VertexBuffer> vbo = createRef<VertexBuffer>(PIECE_QUAD_VERTICES);
    BufferLayout layout = {
        BufferElement(ShaderDataType::Float3, "Position"),
        BufferElement(ShaderDataType::Float2, "TexCoord")
    };
    vbo->setLayout(layout);

    Ref<IndexBuffer> ibo = createRef<IndexBuffer>(PIECE_QUAD_INDICES);

    m_VAO = createRef<VertexArray>();
    m_VAO->addVertexBuffer(vbo);
    m_VAO->setIndexBuffer(ibo);

    m_shader = createRef<Shader>(getChessPieceVertShaderLoc(type).c_str(), getChessPieceFragShaderLoc(type).c_str());
    
    m_texture = TextureLoader::GetInstance()->retrieveTexture(getChessPieceTextureLoc(type));
    m_shader->setTexture("textureSlot", *m_texture);

}

ChessPieceModel2D::~ChessPieceModel2D() {}

void ChessPieceModel2D::setExtraUniforms() {

}