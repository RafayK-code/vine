#pragma once

#include <vine/renderer/backend/Texture.h>

#include <string>

namespace vine
{
    struct MSDFData;
    class Font;

    using FontRef = std::shared_ptr<Font>;

    class Font
    {
    public:
        Font(const std::string& font);
        ~Font();

        const MSDFData* getData() const { return data_; }
        TextureRef getAtlasTexture() const { return atlasTexture_; }

        static FontRef getDefault();

    private:
        MSDFData* data_;
        TextureRef atlasTexture_;
    };
}