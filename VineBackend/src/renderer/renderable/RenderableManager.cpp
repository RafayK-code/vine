#include <vine/renderer/renderable/RenderableManager.h>

#include <vine/renderer/Renderer.h>
#include <vine/renderer/backend/ShaderCache.h>
#include <vine/renderer/renderable/Sprite.h>
#include <vine/renderer/renderable/Quad.h>
#include <vine/renderer/renderable/Text.h>
#include <vine/core/Logger.h>

#include <vector>

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
        std::unordered_map<std::string, std::vector<Renderable*>> quadRenderablesByShader;
        std::unordered_map<std::string, std::vector<Renderable*>> textRenderablesByShader;

        for (const auto& pair : renderables_)
        {
            if (!pair.second)
                continue;

            std::string shaderName = pair.second->getShaderName();
            if (dynamic_cast<Text*>(pair.second))
                textRenderablesByShader[shaderName].push_back(pair.second);
            else
                quadRenderablesByShader[shaderName].push_back(pair.second);
        }

        auto textIt = textRenderablesByShader.begin();
        for (const auto& pair : quadRenderablesByShader)
        {
            ShaderRef shader = ShaderCache::ref().get(pair.first);
            Renderer::ref().setActiveQuadShader(shader);

            for (auto& renderable : pair.second)
                renderable->render();

            if (textIt != textRenderablesByShader.end())
            {
                ShaderRef shader = ShaderCache::ref().get(textIt->first);
                Renderer::ref().setActiveTextShader(shader);

                for (auto& renderable : textIt->second)
                    renderable->render();

                textIt++;
            }

            Renderer::ref().nextBatch();
        }

        while (textIt != textRenderablesByShader.end())
        {
            ShaderRef shader = ShaderCache::ref().get(textIt->first);
            Renderer::ref().setActiveTextShader(shader);

            for (auto& renderable : textIt->second)
                renderable->render();

            Renderer::ref().nextBatch();
            textIt++;
        }
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