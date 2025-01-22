#pragma once

#include <vine/resource/Resource.h>

#include <glad/glad.h>

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

    enum class TextureFilterMode
    {
        None = 0,
        Nearest,
        Linear,
        NearestMipmapNearest,
        LinearMipmapNearest,
        NearestMipmapLinear,
        LinearMipmapLinear,
    };

    enum class TextureWrapMode
    {
        None = 0,
        Repeat,
        RepeatMirrored,
        Clamp,
        ClampEdge,
        ClampBorder,
    };

    struct TextureSpecification
    {
        uint32_t width = 1;
        uint32_t height = 1;
        ImageFormat format = ImageFormat::RGBA8;
        bool generateMips = true;
    };

    struct TextureSamplerSettings
    {
        TextureFilterMode minFilter = TextureFilterMode::Nearest;
        TextureFilterMode magFilter = TextureFilterMode::Nearest;

        TextureWrapMode sWrap = TextureWrapMode::ClampEdge;
        TextureWrapMode tWrap = TextureWrapMode::ClampEdge;
    };

    class ResourceImageCreationData : public ResourceCreationData
    {
    public:
        ResourceImageCreationData(const std::string& filename);
        ResourceImageCreationData(const std::string& filename, const TextureSamplerSettings& settings);

        ResourceImageCreationData(const ResourceImageCreationData& other);

        ~ResourceImageCreationData();

        virtual ResourceCreationData* clone() const override;

        TextureSamplerSettings samplerSettings;
    };

    class ResourceFont;

    class ResourceImage : public Resource
    {
        friend class ResourceManager;
    public:
        static Ref<ResourceImage> create(const std::string& filename, const TextureSamplerSettings& settings = TextureSamplerSettings());
        static Ref<ResourceImage> createBuiltinWhite();

        virtual ~ResourceImage();

        virtual void reload() override;
        virtual void unload() override;

        void bind(uint32_t slot = 0) const;
        void unbind(uint32_t slot = 0) const;

        const TextureSpecification& getSpecification() const { return spec_; }

        uint32_t getWidth() const { return spec_.width; }
        uint32_t getHeight() const { return spec_.height; }
        uint32_t getRendererID() const { return rendererID_; }

        static constexpr std::string_view BUILTIN_WHITE_TEXTURE_KEY = "_builtin_white_texture";

    protected:
        ResourceImage(const ResourceCreationData& data);

    private:
        void loadBuiltinWhite();
        void loadFromData();

    private:
        uint32_t rendererID_;

        GLenum internalFormat_;
        GLenum dataFormat_;

        TextureSpecification spec_;

        void* rawData_;
        bool allowReload_;
    };
}