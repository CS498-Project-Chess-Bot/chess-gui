#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "core.hpp"
#include "vertex_array.hpp"
#include "buffer.hpp"
#include "shader.hpp"
#include "texture.hpp"

class Renderer {

protected:
    Renderer();
    static Renderer* s_renderer;

public:
    Renderer(Renderer &other) = delete;
    void operator=(const Renderer&) = delete;

    void submit(const VertexArray& vao, const Shader& shader, const Texture& texture);
    void clear(float r, float g, float b, float a);
    void setViewport(uint32_t width, uint32_t height);

    static Renderer* GetInstance();
    static void DestroyInstance();

};

namespace RenderCommand {

    void init();

    void submit(const VertexArray& vao, const Shader& shader, const Texture& texture);

    void clear(float r, float g, float b, float a);

    void setViewport(uint32_t width, uint32_t height);

    void exit();
}


#endif