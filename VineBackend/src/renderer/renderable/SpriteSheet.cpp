#include <vine/renderer/renderable/SpriteSheet.h>

#include <pugixml.hpp>
#include <algorithm>
#include <filesystem>

namespace vine
{
    SpriteSheet::SpriteSheet(const std::string& sheet, const RenderableState& defaultState)
    {
        pugi::xml_document doc;
        doc.load_file(sheet.c_str());

        pugi::xml_node textureAtlas = doc.child("TextureAtlas");
        texture_ = createTexture(textureAtlas.attribute("imagePath").as_string());

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

            sprites_.push_back({ new Sprite(texture_, state), name });
        }
    }

    SpriteSheet::~SpriteSheet()
    {
        for (auto& ns : sprites_)
            delete ns.sprite;
    }

    Sprite* SpriteSheet::getSprite(const std::string& name)
    {
        auto it = std::find_if(sprites_.begin(), sprites_.end(), [name](const NamedSprite& ns)
        {
            return ns.name == name;
        });

        if (it == sprites_.end())
            return nullptr;

        return it->sprite;
    }

    SpriteSheetRef createSpriteSheet(const std::string& sheet, const RenderableState& defaultState)
    {
        return std::make_shared<SpriteSheet>(sheet, defaultState);
    }
}