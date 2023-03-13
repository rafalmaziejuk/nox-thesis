#include <nox/maths/bounding_box.h>

#include <limits>

namespace NOX {

    BoundingBox::BoundingBox() : m_minimum(std::numeric_limits<float>::max()),
                                 m_maximum(std::numeric_limits<float>::lowest()) {}

    BoundingBox::BoundingBox(BoundingBox &&other) noexcept : m_minimum(other.m_minimum),
                                                             m_maximum(other.m_maximum) {}

    BoundingBox::BoundingBox(const BoundingBox &other) : m_minimum(other.m_minimum),
                                                         m_maximum(other.m_maximum) {}

    BoundingBox::BoundingBox(const glm::vec3 &minimum, const glm::vec3 &maximum) : m_minimum(minimum),
                                                                                   m_maximum(maximum) {}

    BoundingBox::BoundingBox(const BoundingBox &box1, const BoundingBox &box2) : m_minimum(glm::min(box1.m_minimum, box2.m_minimum)),
                                                                                 m_maximum(glm::max(box1.m_maximum, box2.m_maximum)) {}

    BoundingBox::BoundingBox(const BoundingBox &box, const glm::vec3 &point) : m_minimum(glm::min(box.m_minimum, point)),
                                                                               m_maximum(glm::max(box.m_maximum, point)) {}

    BoundingBox &BoundingBox::operator=(BoundingBox &&other) noexcept {
        if (this == &other) {
            return *this;
        }

        m_maximum = other.m_maximum;
        m_minimum = other.m_minimum;

        return *this;
    }

    BoundingBox &BoundingBox::operator=(const BoundingBox &other) {
        if (this == &other) {
            return *this;
        }

        m_maximum = other.m_maximum;
        m_minimum = other.m_minimum;

        return *this;
    }

    void BoundingBox::grow(const BoundingBox &box) {
        m_minimum = glm::min(m_minimum, box.m_minimum);
        m_maximum = glm::max(m_maximum, box.m_maximum);
    }

    void BoundingBox::grow(const glm::vec3 &point) {
        m_minimum = glm::min(m_minimum, point);
        m_maximum = glm::max(m_maximum, point);
    }

    glm::vec3 BoundingBox::diagonal() const {
        return m_maximum - m_minimum;
    }

    uint8_t BoundingBox::maximumExtentAxis() const {
        auto d = diagonal();
        if (d.x > d.y && d.x > d.z) {
            return 0u;
        } else if (d.y > d.z) {
            return 1u;
        } else {
            return 2u;
        }
    }

    glm::vec3 BoundingBox::offset(const glm::vec3 &point) const {
        auto result = point - m_minimum;
        if (m_maximum.x > m_minimum.x) {
            result.x /= m_maximum.x - m_minimum.x;
        }
        if (m_maximum.y > m_minimum.y) {
            result.y /= m_maximum.y - m_minimum.y;
        }
        if (m_maximum.z > m_minimum.z) {
            result.z /= m_maximum.z - m_minimum.z;
        }
        return result;
    }

    float BoundingBox::surfaceArea() const {
        auto d = diagonal();
        return 2.0f * (d.x * d.y + d.x * d.z + d.y * d.z);
    }

} // namespace NOX
