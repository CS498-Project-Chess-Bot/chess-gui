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

    void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vbo);
    void setIndexBuffer(const std::shared_ptr<IndexBuffer>& ibo);

    const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const {return m_vertexBuffers;}
    const std::shared_ptr<IndexBuffer>& getIndexBuffer() const {return m_indexBuffer;}

    friend std::ostream& operator<<(std::ostream& stream, const VertexArray& vao);

private:
    std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
    std::shared_ptr<IndexBuffer> m_indexBuffer;
    uint32_t m_id;

};

#endif