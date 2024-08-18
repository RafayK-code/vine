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

        Renderable* addRenderable(const std::string& name, Renderable* renderable);
        
        template<typename T, typename... Args>
        Renderable* createRenderable(const std::string& name, Args&&... args)
        {
            Renderable* renderable = new T(std::forward<Args>(args)...);
            return addRenderable(name, renderable);
        }

        Renderable* getRenderable(const std::string& name);
        void removeRenderable(const std::string& name);

    private:
        RenderableManager();

    private:
        std::unordered_map<std::string, Renderable*> renderables_;
    };
}