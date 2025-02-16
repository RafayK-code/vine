#pragma once

#include <vine/sys/Ref.h>
#include <vine/util/Math.h>

#include <glm/glm.hpp>

namespace vine
{
    class OrthographicCamera : public RefCounted
    {
    public:
        OrthographicCamera();
        ~OrthographicCamera();

        Vec2 screenToWorld(const Vec2& point) const;

        const glm::vec3& getPosition() const { return position_; }
        void setPosition(const glm::vec3& position) { position_ = position; updateViewMatrix(); }

        float getRotation() const { return rotation_; }
        void setRotation(float rotation) { rotation_ = rotation; updateViewMatrix(); }

        float getZoom() const { return zoom_; }
        void setZoom(float zoom) { zoom_ = zoom; updateViewMatrix(); }

        const glm::mat4& getViewMatrix() const { return viewMatrix_; }

    private:
        void updateViewMatrix();

    private:
        glm::vec3 position_;
        float rotation_;
        float zoom_;

        glm::mat4 viewMatrix_;
    };
}