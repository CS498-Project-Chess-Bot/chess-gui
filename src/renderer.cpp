#include "renderer.hpp"

Renderer* Renderer::s_renderer = nullptr;

Renderer *Renderer::GetInstance() {
    if(!s_renderer) {
        s_renderer = new Renderer();
    }

    return s_renderer;
}

void Renderer::DestroyInstance() {
    if(s_renderer) {
        delete s_renderer;
    }
}

void Renderer::submit(const VertexArray& vao) {
    glDrawElements(GL_TRIANGLES, vao.getIndexBuffer().count(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
    
void Renderer::setViewport(uint32_t width, uint32_t height) {
    glViewport(0, 0, width, height);
}

namespace RenderCommand {

    void init() { Renderer::GetInstance(); }

    void submit(const VertexArray& vao) {Renderer::GetInstance()->submit(vao);}

    void clear(float r, float g, float b, float a) {Renderer::GetInstance()->clear(r, g, b, a); }

    void setViewport(uint32_t width, uint32_t height) { Renderer::GetInstance()->setViewport(width, height); }

    void exit() { Renderer::DestroyInstance(); }
}

