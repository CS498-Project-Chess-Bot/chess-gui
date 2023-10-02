#ifndef BUFFER_HPP
#define BUFFER_HPP

#include "core.hpp"


enum class ShaderDataType {
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t shaderDataTypeSize(ShaderDataType type) {

		switch (type) {
		case ShaderDataType::Float:		return 4;
		case ShaderDataType::Float2:	return 4 * 2;
		case ShaderDataType::Float3:	return 4 * 3;
		case ShaderDataType::Float4:	return 4 * 4;

		case ShaderDataType::Int:		return 4;
		case ShaderDataType::Int2:		return 4 * 2;
		case ShaderDataType::Int3:		return 4 * 3;
		case ShaderDataType::Int4:		return 4 * 4;

		case ShaderDataType::Mat3:		return 4 * 3 * 3;
		case ShaderDataType::Mat4:		return 4 * 4 * 4;
		case ShaderDataType::Bool:		return 1;
		case ShaderDataType::None:		return 0;

		
		}

		CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement {
		std::string name;
		uint32_t offset;
        ShaderDataType type;
		uint32_t size;
		bool normalized;

		BufferElement()
			: name("None"), offset(0), type(ShaderDataType::None), size(shaderDataTypeSize(type)), normalized(false)
		{

		}

		BufferElement(ShaderDataType type, const std::string& name)
			: name(name), offset(0), type(type), size(shaderDataTypeSize(type)),  normalized(false)
		{

		}

		uint32_t getComponentCount() const {

			switch (type) {
			case ShaderDataType::Float:		return 1;
			case ShaderDataType::Float2:	return 2;
			case ShaderDataType::Float3:	return 3;
			case ShaderDataType::Float4:	return 4;

			case ShaderDataType::Int:		return 1;
			case ShaderDataType::Int2:		return 2;
			case ShaderDataType::Int3:		return 3;
			case ShaderDataType::Int4:		return 4;

			case ShaderDataType::Mat3:		return 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4;
			case ShaderDataType::Bool:		return 1;

			case ShaderDataType::None:		return 0;

			
			}

			CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		
		}

		inline void setNormalized(bool flag) { normalized = flag; }


	};

	class BufferLayout {
	public:
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements) 
		{ 
			CalculateOffsetsAndStride();
		}

		inline const std::vector<BufferElement> getElements() const { return m_Elements; }
		inline uint32_t getStride() const { return m_Stride; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }




	private:
		void CalculateOffsetsAndStride() {
			m_Stride = 0;
			for (auto& element : m_Elements) {
				element.offset = m_Stride;
				m_Stride += element.size;
			}
		}

	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;

	};


class VertexBuffer {
public:

    VertexBuffer();
    VertexBuffer(const std::vector<float>& _vertices);
    ~VertexBuffer();

    void setVertices(const std::vector<float>& _vertices);
    inline void setLayout(const BufferLayout& layout) { m_layout = layout; }
    inline const BufferLayout& getLayout() const { return m_layout; }
    void bind() const;

    inline std::vector<float>& vertices() { return m_vertices; }
    inline const float* data() const {return m_vertices.data(); }
    inline const uint32_t dataSize() const { return sizeof(float) * m_vertices.size(); }
    inline const uint32_t id() const { return m_id; }

    friend std::ostream& operator<<(std::ostream& stream, const VertexBuffer& vbo);

private:
    std::vector<float> m_vertices;
    BufferLayout m_layout;
    uint32_t m_id;
};

class IndexBuffer {
public:

    IndexBuffer();
    IndexBuffer(const std::vector<uint32_t>& _indices);
    ~IndexBuffer();

    void setIndices(const std::vector<uint32_t>& _indices);
    void bind() const;

    inline std::vector<uint32_t>& indices() { return m_indices; }
    inline const uint32_t* data() const {return m_indices.data(); }
    inline const uint32_t dataSize() const { return sizeof(float) * m_indices.size(); }
    inline const uint32_t count() const {return m_indices.size(); } 
    inline const uint32_t id() const { return m_id; }

    friend std::ostream& operator<<(std::ostream& stream, const IndexBuffer& ibo);

private:
    std::vector<uint32_t> m_indices;
    uint32_t m_id;
};

#endif