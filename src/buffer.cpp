#include "buffer.hpp"

VertexBuffer::VertexBuffer() 
    : m_stride(-1), m_id(-1)
{
    glGenBuffers(1, &m_id);
}

VertexBuffer::VertexBuffer(const std::vector<float>& _vertices, uint32_t _stride) 
    : m_vertices(_vertices), m_stride(_stride)
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, dataSize(), data(), GL_STATIC_DRAW);
}

void VertexBuffer::setVertices(const std::vector<float>& _vertices, uint32_t _stride) {
    m_vertices = _vertices;
    m_stride = _stride;
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, dataSize(), data(), GL_STATIC_DRAW);
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

std::ostream& operator<<(std::ostream& stream, const VertexBuffer& vbo) {
    stream << "Vertex Buffer ID: " << vbo.m_id << "\n";
    stream << "Data size: " << vbo.dataSize() << " Stride: " << vbo.stride() << "\n";
    for(const auto& vertex : vbo.m_vertices) {
        stream << vertex << " ";
    }
    stream << std::endl;
    return stream;
}