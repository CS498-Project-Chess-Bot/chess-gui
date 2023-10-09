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

    void addVertexBuffer(const Ref<VertexBuffer>& vbo);
    void setIndexBuffer(const Ref<IndexBuffer>& ibo);

    const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const {return m_vertexBuffers;}
    const Ref<IndexBuffer>& getIndexBuffer() const {return m_indexBuffer;}

    friend std::ostream& operator<<(std::ostream& stream, const VertexArray& vao);

private:
    std::vector<Ref<VertexBuffer>> m_vertexBuffers;
    Ref<IndexBuffer> m_indexBuffer;
    uint32_t m_id;

};

#endif