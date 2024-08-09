#pragma once

#include <string>
#include <glad/glad.h>
#include <memory>

namespace vine
{
    enum class ImageFormat
    {
        None = 0,
        R8,
        RGB8,
        RGBA8,
        RGBA32F,
    };

    struct TextureSpecification
    {
        uint32_t width = 1;
        uint32_t height = 1;
        ImageFormat format = ImageFormat::RGBA8;
        bool generateMips = true;
    };

    class Texture
    {
    public:
        Texture(const TextureSpecification& spec);
        Texture(const std::string& path);

        ~Texture();

        void bind(uint32_t slot = 0) const;
        void unbind(uint32_t slot = 0) const;

        const TextureSpecification& getSpecification() const { return spec_; }

        uint32_t getWidth() const { return spec_.width; }
        uint32_t getHeight() const { return spec_.height; }

        void setData(void* data, uint32_t size);

        bool isLoaded() const { return loaded_; }

    private:
        uint32_t rendererID_;

        TextureSpecification spec_;
        bool loaded_;

        GLenum internalFormat_;
        GLenum dataFormat_;
    };

    using TextureRef = std::shared_ptr<Texture>;
    TextureRef createTexture(const TextureSpecification& spec);
    TextureRef createTexture(const std::string& path);
}