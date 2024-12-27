#include <vine/renderer/renderable/RenderableLayer.h>

#include <vine/renderer/Renderer.h>
#include <vine/renderer/backend/ShaderCache.h>
#include <vine/renderer/renderable/Text.h>

#include <vine/core/Logger.h>

namespace vine
{
    RenderableLayer::RenderableLayer(RenderableLayerType layer)
        : layer_(layer)
    {
    }

    RenderableLayer::~RenderableLayer()
    {
        for (const auto& pair : renderables_)
        {
            if (pair.second)
                delete pair.second;
        }
    }

    void RenderableLayer::render() const
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

    Renderable* RenderableLayer::addRenderable(const std::string& name, Renderable* renderable)
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

    Renderable* RenderableLayer::getRenderable(const std::string& name)
    {
        auto it = renderables_.find(name);
        if (it == renderables_.end())
            return nullptr;

        return it->second;
    }

    bool RenderableLayer::hasRenderable(const std::string& name) const
    {
        return renderables_.find(name) != renderables_.end();
    }

    void RenderableLayer::removeRenderable(const std::string& name)
    {
        auto it = renderables_.find(name);
        if (it == renderables_.end())
            return;

        if (it->second)
            delete it->second;

        renderables_.erase(name);
    }
}