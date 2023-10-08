#include "chess_tile_2D.hpp"

const char* CHESSTILE_FRAG = "shaders/chess_tile.fs";
const char* CHESSTILE_VERT = "shaders/chess_tile.vs";

const glm::vec4 WHITETILE_COLOR = { 1.0f, 0.835f, 0.6f, 1.0f };
const glm::vec4 BLACKTILE_COLOR = { 0.694f, 0.431f, 0.255f, 1.0f };

ChessTileModel2D::ChessTileModel2D(bool isWhiteTile)
    : m_isWhiteTile(isWhiteTile)
{
    Ref<VertexBuffer> vbo = createRef<VertexBuffer>(TILE_QUAD_VERTICES);
    BufferLayout layout = {
        BufferElement(ShaderDataType::Float3, "Position")
    };
    vbo->setLayout(layout);

    Ref<IndexBuffer> ibo = createRef<IndexBuffer>(TILE_QUAD_INDICES);

    m_VAO = createRef<VertexArray>();
    m_VAO->addVertexBuffer(vbo);
    m_VAO->setIndexBuffer(ibo);

    m_shader = createRef<Shader>(CHESSTILE_VERT, CHESSTILE_FRAG);

}

ChessTileModel2D::~ChessTileModel2D() {

}

void ChessTileModel2D::setExtraUniforms() {
    m_shader->bind();
    if(m_isWhiteTile)
        m_shader->setFloat4("u_color", WHITETILE_COLOR);
    else
        m_shader->setFloat4("u_color", BLACKTILE_COLOR);
}