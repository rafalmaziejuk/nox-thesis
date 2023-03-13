#pragma once

#include <glm/glm.hpp>

namespace NOX {

    class BoundingBox {
      public:
        BoundingBox();
        BoundingBox(BoundingBox &&other) noexcept;
        BoundingBox(const BoundingBox &other);
        BoundingBox(const glm::vec3 &minimum, const glm::vec3 &maximum);
        BoundingBox(const BoundingBox &box1, const BoundingBox &box2);
        BoundingBox(const BoundingBox &box, const glm::vec3 &point);

        BoundingBox &operator=(BoundingBox &&other) noexcept;
        BoundingBox &operator=(const BoundingBox &other);

        const glm::vec3 &minimum() const { return m_minimum; }
        const glm::vec3 &maximum() const { return m_maximum; }
        glm::vec3 centroid() const { return {0.5f * m_minimum + 0.5f * m_maximum}; }

        void grow(const BoundingBox &box);
        void grow(const glm::vec3 &point);
        uint8_t maximumExtentAxis() const;
        glm::vec3 offset(const glm::vec3 &point) const;
        float surfaceArea() const;

      private:
        glm::vec3 diagonal() const;

      private:
        glm::vec3 m_minimum;
        glm::vec3 m_maximum;
    };

} // namespace NOX
