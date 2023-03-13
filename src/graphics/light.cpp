#include <nox/graphics/light.h>

namespace NOX {

    Light::Light(LightType type, const glm::vec3 &position, const glm::vec3 &emission) : m_type(type),
                                                                                         m_position(position),
                                                                                         m_emission(emission) {}

    RectangleLight::RectangleLight(const glm::vec3 &position, const float width, const float height, const glm::vec3 &emission) : Light(LightType::RECTANGLE, position, emission),
                                                                                                                                  m_width(width),
                                                                                                                                  m_height(height) {
        glm::vec3 v1 = {position.x + (m_width / 2.0f), position.y, position.z + (m_height / 2.0f)};
        glm::vec3 v2 = {position.x - (m_width / 2.0f), position.y, position.z - (m_height / 2.0f)};
        m_position = {position.x + (m_width / 2.0f), position.y, position.z - (m_height / 2.0f)};
        m_u = v1 - m_position;
        m_v = v2 - m_position;
        m_area = glm::length(glm::cross(m_u, m_v));
    }

} // namespace NOX
