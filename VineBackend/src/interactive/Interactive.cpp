#include <vine/interactive/Interactive.h>

#include <vine/interactive/InteractiveManager.h>

namespace vine
{
    Interactive::Interactive()
        : hitbox_(Rect()), priority_(0.0f), enabled_(true), final_(true), layer_(Layer::Game)
    {
        InteractiveManager::ref().getLayer(layer_)->add(this);
    }

    Interactive::~Interactive()
    {
        InteractiveManager::ref().getLayer(layer_)->remove(this);
    }

    bool Interactive::isHit(const Vec2& point) const
    {
        return hitbox_.contains(point);
    }

    void Interactive::setLayer(LayerLevel layer)
    {
        if (layer_ != layer)
        {
            InteractiveManager::ref().getLayer(layer_)->remove(this);
            layer_ = layer;
            InteractiveManager::ref().getLayer(layer_)->add(this);
        }
    }
}