#include <vine/renderer/renderable/RenderableLayer.h>

#include <vine/renderer/Renderer.h>
#include <vine/renderer/backend/ShaderCache.h>
#include <vine/renderer/renderable/Text.h>

#include <vine/core/Logger.h>

namespace vine
{
    RenderableLayer::RenderableLayer(RenderableLayerLevel layer)
        : layer_(layer)
    {
    }

    RenderableLayer::~RenderableLayer()
    {
    }

    void RenderableLayer::render() const
    {
        std::unordered_map<std::string, std::vector<Renderable*>> quadRenderablesByShader;
        std::unordered_map<std::string, std::vector<Renderable*>> textRenderablesByShader;

        for (Renderable* r : renderables_)
        {
            if (!r)
                continue;

            std::string shaderName = r->getShaderName();
            if (dynamic_cast<Text*>(r))
                textRenderablesByShader[shaderName].push_back(r);
            else
                quadRenderablesByShader[shaderName].push_back(r);
        }

        auto textIt = textRenderablesByShader.begin();
        for (const auto& pair : quadRenderablesByShader)
        {
            ShaderRef shader = ShaderCache::ref().get(pair.first);
            Renderer::ref().setActiveQuadShader(shader);

            for (auto& renderable : pair.second)
            {
                if (renderable->isVisible())
                    renderable->render();
            }

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

    void RenderableLayer::add(Renderable* renderable)
    {
        renderables_.push_back(renderable);
    }

    void RenderableLayer::remove(Renderable* renderable)
    {
        for (RenderableList::const_iterator itr = renderables_.begin(); itr != renderables_.end(); itr++)
        {
            if (*itr == renderable)
            {
                renderables_.erase(itr);
                break;
            }
        }
    }
}