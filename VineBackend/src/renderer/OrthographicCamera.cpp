#include <vine/renderer/OrthographicCamera.h>

#include <vine/core/Application.h>
#include <vine/renderer/Renderer.h>

#include <glm/gtc/matrix_transform.hpp>

namespace vine
{
    OrthographicCamera::OrthographicCamera()
        : position_(glm::vec3(0.0f, 0.0f, 0.0f)), rotation_(0.0f), zoom_(1.0f)
    {
        updateViewMatrix();
    }

    OrthographicCamera::~OrthographicCamera()
    {
    }

    Vec2 OrthographicCamera::screenToWorld(const Vec2& point) const
    {
        float screenWidth = (float)Application::ref().getWindow()->getWidth();
        float screenHeight = (float)Application::ref().getWindow()->getHeight();

        float ndcX = (2.0f * point.x) / screenWidth - 1.0f;
        float ndcY = 1.0f - (2.0f * point.y) / screenHeight;
        float ndcZ = 0.0f;

        Vec4 ndcPos = { ndcX, ndcY, ndcZ, 1.0f };
        glm::mat4 inverseViewProj = glm::inverse(Renderer::ref().getOrtho() * viewMatrix_);

        Vec4 worldPos = inverseViewProj * ndcPos;

        return Vec2(worldPos.x, worldPos.y);
    }

    void OrthographicCamera::updateViewMatrix()
    {
        glm::mat4 transform = 
            glm::translate(glm::mat4(1.0f), position_) * 
            glm::rotate(glm::mat4(1.0f), rotation_, glm::vec3(0.0f, 0.0f, 1.0f)) *
            glm::scale(glm::mat4(1.0f), glm::vec3(1.0f / zoom_, 1.0f / zoom_, 1.0f));

        viewMatrix_ = glm::inverse(transform);
    }
}