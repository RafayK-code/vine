#include <vine/renderer/renderable/RenderableManager.h>

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

    Handle RenderableManager::addRenderable(Renderable* renderable)
    {
        Handle handle = xg::newGuid();
        renderables_.insert({ handle, renderable });
        return handle;
    }

    Renderable* RenderableManager::getRenderable(const Handle& handle)
    {
        auto it = renderables_.find(handle);
        if (it == renderables_.end())
            return nullptr;

        return it->second;
    }

    void RenderableManager::removeRenderable(const Handle& handle)
    {
        auto it = renderables_.find(handle);
        if (it == renderables_.end())
            return;

        delete it->second;
        renderables_.erase(it);
    }
}