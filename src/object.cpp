#include "object.hpp"

void Transform::recalculateTransform() {
    m_transform = glm::mat4(1.0f);
    m_transform = glm::scale(m_transform, m_scale);
    m_transform = glm::rotate(m_transform, m_rotation.x, glm::vec3(0.0f, 1.0f, 0.0f));
    m_transform = glm::rotate(m_transform, m_rotation.y, glm::vec3(1.0f, 0.0f, 0.0f));
    m_transform = glm::rotate(m_transform, m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    m_transform = glm::translate(m_transform, m_pos);
}
