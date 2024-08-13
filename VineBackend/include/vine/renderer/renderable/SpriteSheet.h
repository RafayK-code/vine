#pragma once

#include <vine/renderer/renderable/Sprite.h>
#include <vine/renderer/backend/Texture.h>

#include <string>
#include <vector>

namespace vine
{
    class SpriteSheet
    {
    public:
        SpriteSheet(const std::string& sheet, const RenderableState& defaultState = RenderableState());
        ~SpriteSheet();

        Sprite* getSprite(const std::string& name);

    private:
        struct NamedSprite
        {
            Sprite* sprite;
            std::string name;
        };

        std::vector<NamedSprite> sprites_;
        TextureRef texture_;
    };
}