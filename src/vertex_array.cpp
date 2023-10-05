#include "vertex_array.hpp"

static GLenum shaderDataTypeToOpenGLBaseType(ShaderDataType type) {
			switch (type) {
			case ShaderDataType::None:		return 0;
			case ShaderDataType::Float:		return GL_FLOAT;
			case ShaderDataType::Float2:	return GL_FLOAT;
			case ShaderDataType::Float3:	return GL_FLOAT;
			case ShaderDataType::Float4:	return GL_FLOAT;

			case ShaderDataType::Int:		return GL_INT;
			case ShaderDataType::Int2:		return GL_INT;
			case ShaderDataType::Int3:		return GL_INT;
			case ShaderDataType::Int4:		return GL_INT;

			case ShaderDataType::Mat3:		return GL_FLOAT;
			case ShaderDataType::Mat4:		return GL_FLOAT;
			case ShaderDataType::Bool:		return GL_BOOL;

			}

			CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;

		}

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_id);
    glBindVertexArray(m_id);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_id);
}

void VertexArray::bind() const {
    glBindVertexArray(m_id);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}

void VertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vbo) {
    bind();
    vbo->bind();

    CORE_ASSERT(vbo->getLayout().getElements().size(), "Vertex Buffer has no layout!");

    uint32_t index = 0;
    for(const auto& element : vbo->getLayout()) {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, element.getComponentCount(),
            shaderDataTypeToOpenGLBaseType(element.type), element.normalized ? GL_TRUE : GL_FALSE,
            vbo->getLayout().getStride(), reinterpret_cast<void*>(element.offset));
        index++;
    }

    m_vertexBuffers.push_back(vbo);
}

void VertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& ibo) {
    bind();
    ibo->bind();
    m_indexBuffer = ibo;
}

std::ostream& operator<<(std::ostream& stream, const VertexArray& vao) {
    stream << "Vertex Array ID: " << vao.m_id << "\n";

    uint32_t count = 0;
    for(const auto& buffer : vao.m_vertexBuffers) {
        stream << "Buffer #" << count++ << "\n";
        stream << buffer;
        stream << "\n";
    }

    stream << vao.m_indexBuffer;
    stream << std::endl;
    return stream;
}