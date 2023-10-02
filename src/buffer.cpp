#include "buffer.hpp"

VertexBuffer::VertexBuffer() 
    : m_id(0)
{
    glGenBuffers(1, &m_id);
}

VertexBuffer::VertexBuffer(const std::vector<float>& _vertices) 
    : m_vertices(_vertices)
{
    glGenBuffers(1, &m_id);
    bind();
    glBufferData(GL_ARRAY_BUFFER, dataSize(), data(), GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &m_id);
}

void VertexBuffer::setVertices(const std::vector<float>& _vertices) {
    m_vertices = _vertices;
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, dataSize(), data(), GL_STATIC_DRAW);
}

void VertexBuffer::bind() const {
     CORE_ASSERT(m_id != 0, "Cannot bind an ungenerated buffer!");
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

std::ostream& operator<<(std::ostream& stream, const VertexBuffer& vbo) {
    stream << "Vertex Buffer ID: " << vbo.m_id << "\n";
    stream << "Data size: " << vbo.dataSize() << "\n";
    for(const auto& vertex : vbo.m_vertices) {
        stream << vertex << " ";
    }
    stream << std::endl;
    return stream;
}

IndexBuffer::IndexBuffer() 
    : m_id(0)
{
    glGenBuffers(1, &m_id);
}

IndexBuffer::IndexBuffer(const std::vector<uint32_t>& _indices) 
    : m_indices(_indices)
{
    glGenBuffers(1, &m_id);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize(), data(), GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &m_id);
}

void IndexBuffer::setIndices(const std::vector<uint32_t>& _indices) {
    m_indices = _indices;
}

void IndexBuffer::bind() const {
    CORE_ASSERT(m_id != 0, "Cannot bind an ungenerated buffer!");
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

std::ostream& operator<<(std::ostream& stream, const IndexBuffer& ibo) {
    stream << "Index Buffer ID: " << ibo.m_id << "\n";
    stream << "Data size: " << ibo.dataSize() <<  "\n";
    for(const auto& index : ibo.m_indices) {
        stream << index << " ";
    }
    stream << std::endl;
    return stream;
}