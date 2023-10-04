#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "core.hpp"
#include "buffer.hpp"
#include "vertex_array.hpp"
#include "shader.hpp"
#include "texture.hpp"

#include <memory>

class Transform {
public:
    Transform(glm::vec3 _pos = {0.0f,0.0f,0.0f}, glm::vec3 _scale = {1.0f,1.0f,1.0f}, glm::vec3 _rotation = {0.0f, 0.0f, 0.0f})
    : m_pos(_pos), m_scale(_scale), m_rotation(_rotation) { recalculateTransform(); }

    inline glm::mat4& transform() { return m_transform; }

    inline void changePos(glm::vec3 _pos) { m_pos = _pos; recalculateTransform(); }
    inline void changeScale(glm::vec3 _scale) { m_scale = _scale; recalculateTransform(); }
    inline void changeRotation(glm::vec3 _rotation) { m_rotation = _rotation; recalculateTransform(); }

private:
    void recalculateTransform();

    glm::vec3 m_pos, m_scale, m_rotation;
    glm::mat4 m_transform;

};


class Object {
public:
    Object() {}
    virtual ~Object() {}
    
    inline Transform& transform() { return m_transform; }

    void setExtraUniforms();

    inline std::shared_ptr<VertexArray>& vertexArray() { return m_VAO; }
    inline std::shared_ptr<Shader>& shader() { return m_shader; }
    inline std::shared_ptr<Texture>& texture() { return m_texture; }


protected:
    std::shared_ptr<VertexArray> m_VAO;
    std::shared_ptr<Shader> m_shader;
    std::shared_ptr<Texture> m_texture;

    Transform m_transform;

};


#endif 