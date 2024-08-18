#include <vine/renderer/renderable/Sprite.h>

#include <vine/renderer/renderable/RenderableManager.h>
#include <vine/renderer/Renderer.h>
#include <vine/resource/ResourceManager.h>
#include <vine/resource/ResourceImage.h>
#include <vine/core/Logger.h>

#include <pugixml.hpp>

namespace vine
{
    Sprite::Sprite(const Handle& textureHandle, const SpriteState& state)
        : Renderable(state), spritePos_(state.spritePos), spriteScale_(state.spriteScale), textureHandle_(textureHandle)
    {
        ResourceImage* resTex = ResourceManager::ref().getResource<ResourceImage>(textureHandle_);
        DBG_ASSERT(resTex, "Texture resource with given handle could not be found");

        if (!resTex->isLoaded())
            resTex->load();

        texture_ = resTex->getTexture();
    }

    Sprite::~Sprite()
    {
    }

    void Sprite::render() const
    {
        Renderer::ref().drawQuad(getTransform(), texture_, getSpritePos(), getSpriteScale(), getColor());
    }

    void createSpritesFromSheet(const std::string& sheet, const RenderableState& defaultState)
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