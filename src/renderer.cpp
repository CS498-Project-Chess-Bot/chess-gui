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

Renderer::Renderer() {
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
}

void Renderer::beginScene(const Camera& camera) {
    m_camera = createRef<Camera>(camera);
}

void Renderer::submit(const VertexArray& vao, const Shader& shader, const Texture& texture) {
    vao.bind();
    shader.bind();
    texture.bind();
    glDrawElements(GL_TRIANGLES, vao.getIndexBuffer()->count(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::submit(Ref<Object>& obj) {
    //std::cout << "Submitting " << obj << std::endl;
    CORE_ASSERT(obj != nullptr, "Trying to render a null object!");
    obj->passTransformToChildren();
    //std::cout << "passed to children " << obj << std::endl;
    for(auto& child : obj->getChildren()) {
        //std::cout << child << std::endl;
        if(child)
            submit(child);
    }
    m_objects.push_back(obj);
    
}

void Renderer::endScene(uint32_t screenWidth, uint32_t screenHeight) {
    CORE_ASSERT(m_camera, "Trying to render without beginning scene!");
    CORE_ASSERT(m_objects.size(), "Trying to render without any objects!");

    glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    std::sort(m_objects.begin(), m_objects.end(), [](Ref<Object>& lhs, Ref<Object>& rhs) {
      return lhs->transform().pos().z < rhs->transform().pos().z;
    });
    for(Ref<Object>& obj: m_objects) {
        if(!obj->vertexArray()) 
            CORE_ASSERT(false, "Trying to render without a vertex array!");
        obj->vertexArray()->bind();

        if(obj->texture())
            obj->texture()->bind();

        if(!obj->shader())
            CORE_ASSERT(false, "Trying to render without a shader!");
        obj->shader()->bind();
        obj->shader()->setMat4("view", m_camera->view());
        obj->shader()->setMat4("model", obj->transform().transform());

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);
        obj->shader()->setMat4("projection", projection);

        obj->setExtraUniforms();
        glDrawElements(GL_TRIANGLES, obj->vertexArray()->getIndexBuffer()->count(), GL_UNSIGNED_INT, nullptr);
    }

    m_objects.clear();
}

void Renderer::clear(float r, float g, float b, float a) {
    m_clearColor = glm::vec4(r,g,b,a);
    
}
    
void Renderer::setViewport(uint32_t width, uint32_t height) {
    glViewport(0, 0, width, height);
}

namespace RenderCommand {

    void init() { Renderer::GetInstance(); }

    void beginScene(const Camera& camera) {Renderer::GetInstance()->beginScene(camera);}
    void submit(const VertexArray& vao, const Shader& shader, const Texture& texture) {Renderer::GetInstance()->submit(vao, shader, texture);}
    void submit(Ref<Object>& obj) {Renderer::GetInstance()->submit(obj);}
    void endScene(uint32_t screenWidth, uint32_t screenHeight) { Renderer::GetInstance()-> endScene(screenWidth, screenHeight); }

    

    void clear(float r, float g, float b, float a) {Renderer::GetInstance()->clear(r, g, b, a); }

    void setViewport(uint32_t width, uint32_t height) { Renderer::GetInstance()->setViewport(width, height); }

    void exit() { Renderer::DestroyInstance(); }
}

