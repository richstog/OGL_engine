#include "r_engine_core/Camera.hpp"

namespace r_engine
{
    Camera::Camera(
        const glm::vec3& position,
        const glm::vec3& rotation,
        const ProjectionMode projectionMode
    )
    {
        update_view_matrix();
        update_projection_matrix();
    }

    void Camera::update_view_matrix()
    {
        
    }

    void Camera::update_projection_matrix()
    {

    }

    void Camera::set_position(const glm::vec3& position)
    {
        m_position = position;
        update_view_matrix();
    }

    void Camera::set_rotation(const glm::vec3& rotation)
    {
        m_rotation = rotation;
        update_view_matrix();
    }

    void Camera::set_position_rotation(const glm::vec3& position, const glm::vec3& rotation)
    {
        m_position = position;
        m_rotation = rotation;
        update_view_matrix();
    }

    void Camera::set_projection_mode(const ProjectionMode projection_mode)
    {
        m_projection_mode = projection_mode;
        update_projection_matrix();
    }
}