#pragma once

#include <vine/renderer/renderable/SpriteImmediate.h>
#include <vine/renderer/backend/Texture.h>

#include <vector>

namespace vine
{
    class SpriteSheet
    {
    public:
        SpriteSheet(const std::string& sheet, const SpriteState& state);
        ~SpriteSheet();

        const SpriteImmediate& getSprite(const std::string& name) const;

    private:
        std::vector<SpriteImmediate> sprites_;
    };
}