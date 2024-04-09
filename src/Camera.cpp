#include "Camera.h"
#include "Window.h"


PerspectiveCamera::PerspectiveCamera(float fov, float near, float far)
    : m_fov(fov), m_near(near), m_far(far)
{
    m_position = glm::vec3(0.0f, 0.0f, 5.0f);
    m_front = glm::vec3(0.0f, 0.0f, -1.0f);
}

void PerspectiveCamera::Update()
{	
	if(KEY_W == ACTIVE) m_position += m_front * m_movementSpeed * WR::Core::Time::GetDeltaTime(); 
	if(KEY_A == ACTIVE) m_position -= m_right * m_movementSpeed * WR::Core::Time::GetDeltaTime(); 
	if(KEY_S == ACTIVE) m_position -= m_front * m_movementSpeed * WR::Core::Time::GetDeltaTime(); 
	if(KEY_D == ACTIVE) m_position += m_right * m_movementSpeed * WR::Core::Time::GetDeltaTime(); 
	if(KEY_Q == ACTIVE) m_position += m_up * m_movementSpeed * WR::Core::Time::GetDeltaTime(); 
	if(KEY_E == ACTIVE) m_position -= m_up * m_movementSpeed * WR::Core::Time::GetDeltaTime(); 
}

void PerspectiveCamera::Resize(const uint32_t width, const uint32_t height)
{
	if (width == m_viewportWidth && height == m_viewportHeight)
		return;

	m_viewportWidth = width;
	m_viewportHeight = height;

	RecalculateProjection();
	RecalculateRayDirections();
}

float PerspectiveCamera::GetRotationSpeed()
{
    return m_rotationSpeed;
}

void PerspectiveCamera::RecalculateProjection()
{
    m_projection = glm::perspective(glm::radians(m_fov),  (float)m_viewportWidth / m_viewportHeight, m_near, m_far);
	m_inverseProjection = glm::inverse(m_projection);
}

void PerspectiveCamera::RecalculateView()
{
    m_view = glm::lookAt(m_position, m_position + m_front, m_up);
    m_inverseView = glm::inverse(m_view);
}

void PerspectiveCamera::RecalculateRayDirections()
{
	m_rayDirections.resize(m_viewportWidth * m_viewportHeight);

	for (uint32_t y = 0; y < m_viewportHeight; y++)
	{
		for (uint32_t x = 0; x < m_viewportWidth; x++)
		{
			glm::vec2 uv = { (float)x / (float)m_viewportWidth, (float)y / (float)m_viewportHeight };
			uv = uv * 2.0f - 1.0f; 

			glm::vec4 target = glm::vec4(uv.x, uv.y, -1, 1);
			glm::vec3 rayDirection = glm::vec3(m_inverseView * glm::vec4(glm::normalize(glm::vec3(target) / target.w), 0)); // World space
			m_rayDirections[x + y * m_viewportWidth] = target;
		}
	}
}
