#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include "core.hpp"
#include "buffer.hpp"

class VertexArray {
public:

    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;

    void addVertexBuffer(const VertexBuffer& vbo);
    void setIndexBuffer(const IndexBuffer& ibo);

    const std::vector<VertexBuffer>& getVertexBuffers() const {return m_vertexBuffers;}
    const IndexBuffer& getIndexBuffer() const {return m_indexBuffer;}

    friend std::ostream& operator<<(std::ostream& stream, const VertexArray& vao);

private:
    std::vector<VertexBuffer> m_vertexBuffers;
    IndexBuffer m_indexBuffer;
    uint32_t m_id;

};

#endif