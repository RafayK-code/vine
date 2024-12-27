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
        renderables_.emplace(Layer::Background, new RenderableLayer(Layer::Background));
        renderables_.emplace(Layer::CG, new RenderableLayer(Layer::CG));
        renderables_.emplace(Layer::Game, new RenderableLayer(Layer::Game));
        renderables_.emplace(Layer::Foreground, new RenderableLayer(Layer::Foreground));
        renderables_.emplace(Layer::Effects, new RenderableLayer(Layer::Effects));
        renderables_.emplace(Layer::UI, new RenderableLayer(Layer::UI));
    }

    RenderableManager::~RenderableManager()
    {
        for (const auto& pair : renderables_)
        {
            if (pair.second)
                delete pair.second;
        }
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
        {
            if (pair.second)
                pair.second->render();
        }
    }

    Renderable* RenderableManager::addRenderable(const std::string& name, Renderable* renderable)
    {
        DBG_ASSERT(Layer::isValidLayer(renderable->getLayer()), "Renderable is not on a valid layer");
        return renderables_[renderable->getLayer()]->addRenderable(name, renderable);
    }

    Renderable* RenderableManager::getRenderable(const std::string& name)
    {
        for (const auto& pair : renderables_)
        {
            Renderable* renderable = pair.second->getRenderable(name);
            if (renderable)
                return renderable;
        }

        return nullptr;
    }

    void RenderableManager::removeRenderable(const std::string& name)
    {
        for (auto& pair : renderables_)
        {
            if (pair.second->hasRenderable(name));
            {
                pair.second->removeRenderable(name);
                return;
            }
        }
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