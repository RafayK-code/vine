#include <vine/interactive/InteractiveLayer.h>

#include <algorithm>

namespace vine
{
    InteractiveLayer::InteractiveLayer(LayerLevel layer)
        : layer_(layer), camera_(nullptr)
    {
    }

    InteractiveLayer::~InteractiveLayer()
    {
    }

    void InteractiveLayer::add(Interactive* interactive)
    {
        interactives_.push_back(interactive);
    }

    void InteractiveLayer::remove(Interactive* interactive)
    {
        for (InteractiveList::const_iterator itr = interactives_.begin(); itr != interactives_.end(); itr++)
        {
            if (*itr == interactive)
            {
                interactives_.erase(itr);
                break;
            }
        }
    }

    bool InteractiveLayer::onMouseButtonDown(const MouseButtonDownEvent& e)
    {
        std::sort(interactives_.begin(), interactives_.end(), [](Interactive* i1, Interactive* i2){
            return i1->getPriority() < i2->getPriority();
        });

        for (auto& interactive : interactives_)
        {
            if (!interactive->isEnabled())
                continue;

            Vec2 point = { e.getX(), e.getY() };
            if (camera_)
                point = camera_->screenToWorld(point);

            if (interactive->isHit(point))
            {
                interactive->onMouseDown();
                if (interactive->isFinal())
                    return true;
            }
        }

        return false;
    }

    bool InteractiveLayer::onMouseButtonUp(const MouseButtonUpEvent& e)
    {
        std::sort(interactives_.begin(), interactives_.end(), [](Interactive* i1, Interactive* i2){
            return i1->getPriority() < i2->getPriority();
        });

        for (auto& interactive : interactives_)
        {
            if (!interactive->isEnabled())
                continue;

            Vec2 point = { e.getX(), e.getY() };
            if (camera_)
                point = camera_->screenToWorld(point);

            if (interactive->isHit(point))
            {
                interactive->onMouseUp();
                if (interactive->isFinal())
                    return true;
            }
        }

        return false;
    }
}