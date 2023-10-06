#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <memory>

#include "core.hpp"
#include "vertex_array.hpp"
#include "buffer.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "camera.hpp"
#include "object.hpp"

class Renderer {

protected:
    Renderer();
    static Renderer* s_renderer;

public:
    Renderer(Renderer &other) = delete;
    void operator=(const Renderer&) = delete;

    void beginScene(const Camera& camera);
    void submit(const VertexArray& vao, const Shader& shader, const Texture& texture);
    void submit(Ref<Object>& obj);
    void endScene(uint32_t screenWidth, uint32_t screenHeight);

    void clear(float r, float g, float b, float a);
    void setViewport(uint32_t width, uint32_t height);

    static Renderer* GetInstance();
    static void DestroyInstance();

private:
    std::vector<Ref<Object>> m_objects;
    std::shared_ptr<Camera> m_camera;
    glm::vec4 m_clearColor;

};

namespace RenderCommand {

    void init();

    void beginScene(const Camera& camera);
    void submit(const VertexArray& vao, const Shader& shader, const Texture& texture);
    void submit(Ref<Object>& obj);
    void endScene(uint32_t screenWidth, uint32_t screenHeight);

    void clear(float r, float g, float b, float a);

    void setViewport(uint32_t width, uint32_t height);

    void exit();
}


#endif