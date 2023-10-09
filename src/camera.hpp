#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "core.hpp"

class Camera {
public:
    Camera(glm::vec3 pos = glm::vec3(0.0f,0.0f,0.0f), glm::vec3 up = glm::vec3(0.0f,1.0f,0.0f), glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f));
    ~Camera();

    inline glm::mat4& view() { return m_view; };

private:
    void recalculateView();

    glm::vec3 m_pos;
    glm::vec3 m_up;
    glm::vec3 m_forward;

    glm::mat4 m_view;
};

#endif