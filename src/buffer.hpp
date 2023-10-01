#ifndef BUFFER_HPP
#define BUFFER_HPP

#include "core.hpp"

class VertexBuffer {
public:

    VertexBuffer();
    VertexBuffer(const std::vector<float>& _vertices, uint32_t _stride);

    void setVertices(const std::vector<float>& _vertices, uint32_t _stride);
    void bind() const;

    inline std::vector<float>& vertices() { return m_vertices; }
    inline const float* data() const {return m_vertices.data(); }
    inline const uint32_t dataSize() const { return sizeof(float) * m_vertices.size(); }
    inline const uint32_t stride() const { return m_stride; }
    inline const uint32_t id() const { return m_id; }

    friend std::ostream& operator<<(std::ostream& stream, const VertexBuffer& vbo);

private:
    std::vector<float> m_vertices;
    uint32_t m_stride;
    uint32_t m_id;
};

#endif