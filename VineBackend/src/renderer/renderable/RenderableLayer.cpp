#include <vine/renderer/renderable/RenderableLayer.h>

#include <vine/renderer/Renderer.h>
#include <vine/renderer/backend/ShaderCache.h>
#include <vine/renderer/renderable/Text.h>

#include <vine/core/Logger.h>

namespace vine
{
    RenderableLayer::RenderableLayer(RenderableLayerLevel layer)
        : layer_(layer), camera_(nullptr)
    {
    }

    RenderableLayer::~RenderableLayer()
    {
    }

    void RenderableLayer::render() const
    {
        std::unordered_map<std::string, std::vector<Renderable*>> quadRenderablesByShader;
        std::unordered_map<std::string, std::vector<Renderable*>> textRenderablesByShader;
        
        std::vector<Renderable*> stRenderables;

        for (Renderable* r : renderables_)
        {
            if (!r)
                continue;

            if (r->getColor().a < 1.0f)
                stRenderables.push_back(r);
            else
            {
                std::string shaderName = r->getShaderName();
                if (dynamic_cast<Text*>(r))
                    textRenderablesByShader[shaderName].push_back(r);
                else
                    quadRenderablesByShader[shaderName].push_back(r);
            }
        }

        auto textIt = textRenderablesByShader.begin();

        Renderer::ref().beginScene(camera_);

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
                Renderer::ref().setActiveCamera(camera_);

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
            Renderer::ref().setActiveCamera(camera_);

            for (auto& renderable : textIt->second)
            {
                if (renderable->isVisible())
                    renderable->render();
            }

            Renderer::ref().nextBatch();
            textIt++;
        }

        std::sort(stRenderables.begin(), stRenderables.end(), [](Renderable* r1, Renderable* r2) {
            return r1->getPriority() > r2->getPriority();
        });

        glDepthMask(GL_FALSE);
        for (const auto& r : stRenderables)
        {
            if (!r)
                continue;

            ShaderRef shader = ShaderCache::ref().get(r->getShaderName());
            if (dynamic_cast<Text*>(r))
                Renderer::ref().setActiveTextShader(shader);
            else
                Renderer::ref().setActiveQuadShader(shader);

            r->render();
            Renderer::ref().nextBatch();
        }
        glDepthMask(GL_TRUE);

        Renderer::ref().endScene();
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