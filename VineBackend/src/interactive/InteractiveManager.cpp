#include <vine/interactive/InteractiveManager.h>

#include <vine/core/Logger.h>

#include <functional>

namespace vine
{
    InteractiveManager::InteractiveManager()
        : controller_(nullptr), listener_(EventListener())
    {
        interactives_.emplace(Layer::Background, new InteractiveLayer(Layer::Background));
        interactives_.emplace(Layer::CG, new InteractiveLayer(Layer::CG));
        interactives_.emplace(Layer::Game, new InteractiveLayer(Layer::Game));
        interactives_.emplace(Layer::Foreground, new InteractiveLayer(Layer::Foreground));
        interactives_.emplace(Layer::Effects, new InteractiveLayer(Layer::Effects));
        interactives_.emplace(Layer::UI, new InteractiveLayer(Layer::UI));
    }

    InteractiveManager::~InteractiveManager()
    {
        for (const auto& pair : interactives_)
        {
            if (pair.second)
                delete pair.second;
        }
    }

    void InteractiveManager::init()
    {
        createSingleton();
    }

    void InteractiveManager::shutdown()
    {
        destroySingleton();
    }

    InteractiveLayer* InteractiveManager::getLayer(LayerLevel layer)
    {
        DBG_ASSERT(Layer::isValidLayer(layer), "Renderable is not on a valid layer");
        return interactives_.find(layer)->second;
    }

    void InteractiveManager::setController(Controller* controller)
    {
        controller_ = controller;
        setupEventCallbacks();
    }

    void InteractiveManager::setupEventCallbacks()
    {
        listener_.stopListening();

        if (controller_ == nullptr)
            return;

        listener_.listen<MouseButtonDownEvent>(*controller_, std::bind(&InteractiveManager::onMouseButtonDown, this, std::placeholders::_1));
        listener_.listen<MouseButtonUpEvent>(*controller_, std::bind(&InteractiveManager::onMouseButtonUp, this, std::placeholders::_1));
    }

    void InteractiveManager::onMouseButtonDown(const MouseButtonDownEvent& e)
    {
        for (auto const& pair : interactives_)
        {
            bool finalHit = pair.second->onMouseButtonDown(e);
            if (finalHit)
                return;
        }
    }

    void InteractiveManager::onMouseButtonUp(const MouseButtonUpEvent& e)
    {
        for (auto const& pair : interactives_)
        {
            bool finalHit = pair.second->onMouseButtonUp(e);
            if (finalHit)
                return;
        }
    }
}