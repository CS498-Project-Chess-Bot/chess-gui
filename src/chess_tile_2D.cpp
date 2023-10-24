#include "chess_tile_2D.hpp"

const char* CHESSTILE_FRAG = "shaders/chess_tile.fs";
const char* CHESSTILE_VERT = "shaders/chess_tile.vs";

const glm::vec4 WHITETILE_COLOR = { 1.0f, 0.835f, 0.6f, 1.0f };
const glm::vec4 BLACKTILE_COLOR = { 0.694f, 0.431f, 0.255f, 1.0f };
const glm::vec4 TINT_COLOR = {0.5f, 0.5f, 1.0f, 0.5f};

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

    glm::vec4 color = m_isWhiteTile ? WHITETILE_COLOR : BLACKTILE_COLOR;
    if(m_highlighted) {
        color.r = glm::mix(color.r, TINT_COLOR.r, TINT_COLOR.a);
        color.g = glm::mix(color.g, TINT_COLOR.g, TINT_COLOR.a);
        color.b = glm::mix(color.b, TINT_COLOR.b, TINT_COLOR.a);
    }

    m_shader->setFloat4("u_color", color);
}

bool ChessTileModel2D::checkRayIntersectsTile(glm::vec3 rayOrigin, glm::vec3 rayDir) {
    const float EPSILON = 0.00000001;

    for(uint32_t idxStart = 0; idxStart < TILE_QUAD_INDICES.size(); idxStart += 3) {
        int v1Start = TILE_QUAD_INDICES[idxStart] * 3;
        glm::vec4 v1w = {TILE_QUAD_VERTICES[v1Start], TILE_QUAD_VERTICES[v1Start+1], TILE_QUAD_VERTICES[v1Start+2], 1};
        v1w = m_transform.transform() * v1w;
        int v2Start = TILE_QUAD_INDICES[idxStart+1] * 3;
        glm::vec4 v2w = {TILE_QUAD_VERTICES[v2Start], TILE_QUAD_VERTICES[v2Start+1], TILE_QUAD_VERTICES[v2Start+2], 1};
        v2w = m_transform.transform() * v2w;
        int v3Start = TILE_QUAD_INDICES[idxStart+2] * 3;
        glm::vec4 v3w = {TILE_QUAD_VERTICES[v3Start], TILE_QUAD_VERTICES[v3Start+1], TILE_QUAD_VERTICES[v3Start+2], 1};
        v3w = m_transform.transform() * v3w;

        glm::vec3 v1(v1w), v2(v2w), v3(v3w);

        glm::vec3 edge1 = v2-v1;
        glm::vec3 edge2 = v3-v1;
        glm::vec3 h = glm::cross(rayDir, edge2);
        float a = glm::dot(edge1, h);

        if(a > -EPSILON && a < EPSILON) {
            continue;
        }

        float f = 1.0f / a;
        glm::vec3 s = rayOrigin - v1;
        float u = f * glm::dot(s, h);

        if( u < 0.0f || u > 1.0f) {
            continue;
        }

        glm::vec3 q = glm::cross(s, edge1);
        float v = f * glm::dot(rayDir, q);

        if(v < 0.0f || (u+v) > 1.0f) {
            continue;
        }

        float t = f * glm::dot(edge2, q);
        if(t > EPSILON) {
            return true;
        }
        else {
            continue;
        }

    }
    return false;
}