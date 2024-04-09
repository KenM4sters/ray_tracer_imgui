#pragma once
#include "Core.h"

class PerspectiveCamera{
    public:
        PerspectiveCamera(float fov, float near, float far);

        void Update();
        void Resize(const uint32_t width, const uint32_t height);

        const glm::mat4& GetProjection() const { return m_projection; }
        const glm::mat4& GetInverseProjection() const { return m_inverseProjection; }
        const glm::mat4& GetView() const { return m_view; }
        const glm::mat4& GetInverseView() const { return m_inverseView; }
        
        const glm::vec3& GetPosition() const { return m_position; }
        const glm::vec3& GetDirection() const { return m_front; }

        const std::vector<glm::vec3>& GetRayDirections() const { return m_rayDirections; }

        float GetRotationSpeed();
        void SetRotationSpeed(float s) {m_rotationSpeed = s;}
    private:
        void RecalculateProjection();
        void RecalculateView();
        void RecalculateRayDirections();
    private:
        glm::mat4 m_projection{ 1.0f };
        glm::mat4 m_view{ 1.0f };
        glm::mat4 m_inverseProjection{ 1.0f };
        glm::mat4 m_inverseView{ 1.0f };

        float m_fov = 45.0f;
        float m_near = 0.1f;
        float m_far = 100.0f;
        float m_rotationSpeed = 0.03f;
        float m_movementSpeed = 5.0f;

        glm::vec3 m_position{0.0f, 0.0f, 0.0f};
        glm::vec3 m_front{0.0f, 0.0f, -1.0f};
        glm::vec3 m_up{0.0f, 1.0f, 0.0f};
        glm::vec3 m_right{1.0f, 0.0f, 0.0f};

        // Ray directions
        std::vector<glm::vec3> m_rayDirections;

        glm::vec2 m_lastMousePosition{ 0.0f, 0.0f };

        uint32_t m_viewportWidth = 0, m_viewportHeight = 0;
};