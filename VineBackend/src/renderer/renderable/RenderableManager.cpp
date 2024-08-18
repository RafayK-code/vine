#include <vine/renderer/renderable/RenderableManager.h>

#include <vine/core/Logger.h>

namespace vine
{
    RenderableManager::RenderableManager()
    {
    }

    RenderableManager::~RenderableManager()
    {
        for (const auto& pair : renderables_)
            delete pair.second;
    }

    void RenderableManager::init()
    {
        createSingleton();
    }

    void RenderableManager::shutdown()
    {
        destroySingleton();
    }

    void RenderableManager::render() const
    {
        for (const auto& pair : renderables_)
            pair.second->render();
    }

    Renderable* RenderableManager::addRenderable(const std::string& name, Renderable* renderable)
    {
        auto it = renderables_.find(name);
        if (it != renderables_.end())
        {
            DBG_WARN("Renderable with name: {0} already exists! Freeing renderable passed in, returning existing renderable", name);
            delete renderable;
            return it->second;
        }

        renderables_.insert({ name, renderable });
        return renderable;
    }

    Renderable* RenderableManager::getRenderable(const std::string& name)
    {
        auto it = renderables_.find(name);
        if (it == renderables_.end())
            return nullptr;

        return it->second;
    }

    void RenderableManager::removeRenderable(const std::string& name)
    {
        auto it = renderables_.find(name);
        if (it == renderables_.end())
            return;

        delete it->second;
        renderables_.erase(it);
    }
}