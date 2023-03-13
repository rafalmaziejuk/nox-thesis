#pragma once

#include <glm/glm.hpp>

namespace NOX {

    enum LightType : uint32_t {
        RECTANGLE = 0
    };

    class Light {
      public:
        Light(LightType type, const glm::vec3 &position, const glm::vec3 &emission);
        virtual ~Light() = default;

        virtual LightType getType() const { return m_type; }
        virtual const glm::vec3 &getPosition() const { return m_position; }
        virtual const glm::vec3 &getEmission() const { return m_emission; }

      protected:
        LightType m_type;
        glm::vec3 m_position{0.0f};
        glm::vec3 m_emission{0.0f};
    };

    class RectangleLight : public Light {
      public:
        RectangleLight(const glm::vec3 &position, const float width, const float height, const glm::vec3 &emission);
        ~RectangleLight() override = default;

        const glm::vec3 &getU() const { return m_u; }
        const glm::vec3 &getV() const { return m_v; }
        float getArea() const { return m_area; }

      private:
        glm::vec3 m_u{0.0f};
        glm::vec3 m_v{0.0f};
        float m_width{0.0f};
        float m_height{0.0f};
        float m_area{0.0f};
    };

} // namespace NOX
