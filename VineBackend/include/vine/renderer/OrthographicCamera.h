#pragma once

#include <glm/glm.hpp>

namespace vine
{
    class OrthographicCamera
    {
    public:
        OrthographicCamera(float left, float right, float bottom, float top, float near, float far);
        ~OrthographicCamera();

        void setProjection(float left, float right, float bottom, float top, float near, float far);

        const glm::vec3& getPosition() const { return position_; }
        void setPosition(const glm::vec3& position) { position_ = position; updateViewMatrix(); }

        float getRotation() const { return rotation_; }
        void setRotation(float rotation) { rotation_ = rotation; updateViewMatrix(); }

        const glm::mat4& getProjectionMatrix() const { return projectionMatrix_; }
        const glm::mat4& getViewMatrix() const { return viewMatrix_; }
        const glm::mat4& getViewProjectionMatrix() const { return viewProjectionMatrix_; }

    private:
        void updateViewMatrix();

    private:
        glm::vec3 position_;
        float rotation_;

        glm::mat4 projectionMatrix_;
        glm::mat4 viewMatrix_;
        glm::mat4 viewProjectionMatrix_;
    };
}