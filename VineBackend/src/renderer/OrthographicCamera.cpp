#include <vine/renderer/OrthographicCamera.h>

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

    void OrthographicCamera::updateViewMatrix()
    {
        glm::mat4 transform = 
            glm::translate(glm::mat4(1.0f), position_) * 
            glm::rotate(glm::mat4(1.0f), rotation_, glm::vec3(0.0f, 0.0f, 1.0f)) *
            glm::scale(glm::mat4(1.0f), glm::vec3(1.0f / zoom_, 1.0f / zoom_, 1.0f));

        viewMatrix_ = glm::inverse(transform);
    }
}