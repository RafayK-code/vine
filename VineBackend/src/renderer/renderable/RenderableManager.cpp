#include <vine/renderer/renderable/RenderableManager.h>

#include <vine/renderer/Renderer.h>
#include <vine/renderer/backend/ShaderCache.h>
#include <vine/renderer/renderable/Sprite.h>
#include <vine/renderer/renderable/Quad.h>
#include <vine/renderer/renderable/Text.h>
#include <vine/core/Logger.h>
#include <vine/resource/ResourceManager.h>
#include <vine/resource/ResourceImage.h>

#include <pugixml.hpp>

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

    void RenderableManager::createSpritesFromSheet(const std::string& sheet, const RenderableState& defaultState)
    {
        pugi::xml_document doc;
        doc.load_file(sheet.c_str());

        pugi::xml_node textureAtlas = doc.child("TextureAtlas");
        Handle handle = ResourceManager::ref().createAndLoadResource<ResourceImage>({ textureAtlas.attribute("imagePath").as_string() });

        for (pugi::xml_node spriteNode = textureAtlas.child("sprite"); spriteNode; spriteNode = spriteNode.next_sibling("sprite"))
        {
            std::string name = spriteNode.attribute("n").as_string();
            int x = spriteNode.attribute("x").as_int();
            int y = spriteNode.attribute("y").as_int();
            int w = spriteNode.attribute("w").as_int();
            int h = spriteNode.attribute("h").as_int();

            // unsused for now
            float pX = spriteNode.attribute("pX").as_float();
            float pY = spriteNode.attribute("pY").as_float();

            SpriteState state;
            state.spritePos = { (float)x, (float)y };
            state.spriteScale = { (float)w, (float)h };
            state.pos = defaultState.pos;
            state.scale = defaultState.scale;
            state.rotation = defaultState.rotation;
            state.color = defaultState.color;
            state.layer = defaultState.layer;
            state.visible = defaultState.visible;

            RenderableManager::ref().addRenderable(name, new Sprite(handle, state));
        }
    }
}