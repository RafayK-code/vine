#pragma once

#include <vine/renderer/renderable/Renderable.h>
#include <vine/util/Singleton.h>

#include <crossguid/guid.hpp>
#include <vector>

namespace vine
{
    using Handle = xg::Guid;

    class RenderableManager : public Singleton<RenderableManager>
    {
        friend class Singleton<RenderableManager>;
    public:
        ~RenderableManager();

        static void init();
        static void shutdown();

        void render() const;

        Handle addRenderable(Renderable* renderable);
        
        template<typename T, typename... Args>
        Handle createRenderable(Args&&... args)
        {
            Renderable* renderable = new T(std::forward<Args>(args)...);
            return addRenderable(renderable);
        }

        Renderable* getRenderable(const Handle& handle);
        void removeRenderable(const Handle& handle);

    private:
        RenderableManager();

    private:
        std::unordered_map<Handle, Renderable*> renderables_;
    };
}