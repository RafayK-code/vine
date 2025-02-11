#include <vine/renderer/OrthographicCamera.h>

#include <glm/gtc/matrix_transform.hpp>

namespace vine
{
    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near, float far)
        : position_(glm::vec3(0.0f, 0.0f, 0.0f)), rotation_(0.0f), zoom_(1.0f), projectionMatrix_(glm::ortho(left, right, bottom, top, near, far))
    {
        updateViewMatrix();
    }

    OrthographicCamera::~OrthographicCamera()
    {
    }

    void OrthographicCamera::setProjection(float left, float right, float bottom, float top, float near, float far)
    {
        projectionMatrix_ = glm::ortho(left, right, bottom, top, near, far);
        updateViewMatrix();
    }

    glm::vec2 OrthographicCamera::screenToWorld(const glm::vec2& screenPos) const
    {
        glm::mat4 inverse = glm::inverse(viewProjectionMatrix_);
        glm::vec4 worldPos = inverse * glm::vec4(screenPos, 0.0f, 1.0f);

        return glm::vec2(worldPos.x, worldPos.y);
    }

    void OrthographicCamera::updateViewMatrix()
    {
        glm::mat4 transform = 
            glm::translate(glm::mat4(1.0f), position_) * 
            glm::rotate(glm::mat4(1.0f), rotation_, glm::vec3(0.0f, 0.0f, 1.0f)) *
            glm::scale(glm::mat4(1.0f), glm::vec3(1.0f / zoom_, 1.0f / zoom_, 1.0f));

        viewMatrix_ = glm::inverse(transform);
        viewProjectionMatrix_ = projectionMatrix_ * viewMatrix_;
    }
}