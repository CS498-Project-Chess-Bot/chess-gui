#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 pos, glm::vec3 up, glm::vec3 forward) 
    : m_pos(pos), m_up(up), m_forward(forward)
{
    recalculateView();
}

Camera::~Camera() {

}

void Camera::recalculateView() {
    m_view = glm::lookAt(m_pos, m_pos + m_forward, m_up);
}