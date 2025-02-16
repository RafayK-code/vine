#pragma once

#include <vine/renderer/Rect.h>
#include <vine/renderer/renderable/Renderable.h>
#include <vine/core/Layer.h>

namespace vine
{
    class Interactive
    {
    public:
        Interactive();
        virtual ~Interactive();

        virtual void onMouseDown() = 0;
        virtual void onMouseUp() = 0;
        virtual void onHover() = 0;
        virtual void onHoverExit() = 0;

        bool isHit(const Vec2& point) const;

        const Rect& getHitbox() const { return hitbox_; }
        void setHitbox(const Rect& hitbox) { hitbox_ = hitbox; }

        float getPriority() const { return priority_; }
        void setPriority(float priority) { priority_ = priority; }

        bool isEnabled() const { return enabled_; }
        void setEnabled(bool enabled) { enabled_ = enabled; }

        bool isFinal() const { return final_; }
        bool setFinal(bool final) { final_ = final; }

        LayerLevel getLayer() const { return layer_; }
        void setLayer(LayerLevel layer);

    private:
        Rect hitbox_;
        float priority_;
        LayerLevel layer_;

        bool enabled_;
        bool final_;
    };
}