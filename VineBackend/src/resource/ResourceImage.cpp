#include <vine/resource/ResourceImage.h>

#include <vine/core/Logger.h>
#include <vine/sys/Ref.h>

#include <stb/stb_image.h>

namespace vine
{
    namespace util
    {
        static GLenum vineImageFormatToGLInternalFormat(ImageFormat format)
        {
            switch (format)
            {
            case ImageFormat::R8: return GL_R8;
            case ImageFormat::RGB8: return GL_RGB8;
            case ImageFormat::RGBA8: return GL_RGBA8;
            }

            DBG_ASSERT(false, "Unsupported image format");
            return 0;
        }

        static GLenum vineImageFormatToGLDataFormat(ImageFormat format)
        {
            switch (format)
            {
            case ImageFormat::R8: return GL_RED;
            case ImageFormat::RGB8: return GL_RGB;
            case ImageFormat::RGBA8: return GL_RGBA;
            }

            DBG_ASSERT(false, "Unsupported image format");
            return 0;
        }

        static GLenum vineFilterModeToGLFilterMode(TextureFilterMode filter)
        {
            switch (filter)
            {
            case TextureFilterMode::Nearest: return GL_NEAREST;
            case TextureFilterMode::Linear: return GL_LINEAR;
            case TextureFilterMode::NearestMipmapNearest: return GL_NEAREST_MIPMAP_NEAREST;
            case TextureFilterMode::LinearMipmapNearest: return GL_LINEAR_MIPMAP_NEAREST;
            case TextureFilterMode::NearestMipmapLinear: return GL_NEAREST_MIPMAP_LINEAR;
            case TextureFilterMode::LinearMipmapLinear: return GL_LINEAR_MIPMAP_LINEAR;
            }

            DBG_ASSERT(false, "Unsupported filter mode");
            return 0;
        }

        static GLenum vineWrapModeToGLWrapMode(TextureWrapMode wrap)
        {
            switch (wrap)
            {
            case TextureWrapMode::Repeat: return GL_REPEAT;
            case TextureWrapMode::RepeatMirrored: return GL_MIRRORED_REPEAT;
            case TextureWrapMode::Clamp: return GL_CLAMP;
            case TextureWrapMode::ClampEdge: return GL_CLAMP_TO_EDGE;
            case TextureWrapMode::ClampBorder: return GL_CLAMP_TO_BORDER;
            }

            DBG_ASSERT(false, "Unsupported wrap mode");
            return 0;
        }
    }

    ResourceImageCreationData::ResourceImageCreationData(const std::string& filename)
        : ResourceCreationData(filename), samplerSettings(TextureSamplerSettings())
    {
        type = ResourceDataType::ResourceDataTypeImage;
    }

    ResourceImageCreationData::ResourceImageCreationData(const std::string& filename, const TextureSamplerSettings& settings)
        : ResourceCreationData(filename), samplerSettings(settings)
    {
        type = ResourceDataType::ResourceDataTypeImage;
    }

    ResourceImageCreationData::ResourceImageCreationData(const ResourceImageCreationData& other)
        : ResourceCreationData(other), samplerSettings(other.samplerSettings)
    {
    }

    ResourceImageCreationData::~ResourceImageCreationData()
    {
    }

    ResourceCreationData* ResourceImageCreationData::clone() const
    {
        return new ResourceImageCreationData(*this);
    }

    ResourceImage::ResourceImage(const ResourceCreationData& data)
        : Resource(data), internalFormat_(0), dataFormat_(0), rendererID_(0), allowReload_(false)
    {
    }

    ResourceImage::~ResourceImage()
    {
        unload();
    }

    void ResourceImage::reload()
    {
        if (loaded_ || !allowReload_)
            return;

        loaded_ = true;
    }

    void ResourceImage::unload()
    {
        if (!loaded_)
            return;

        glDeleteTextures(1, &rendererID_);
        loaded_ = false;
    }

    void ResourceImage::bind(uint32_t slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, rendererID_);
    }

    void ResourceImage::unbind(uint32_t slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void ResourceImage::loadFromFile()
    {
        const ResourceImageCreationData* data = dynamic_cast<const ResourceImageCreationData*>(getCreationData());

        if (data->file == BUILTIN_WHITE_TEXTURE_KEY)
        {
            loadBuiltinWhite();
            return;
        }

        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* bytes = stbi_load(data->file.c_str(), &width, &height, &channels, 0);

        DBG_ASSERT(bytes, "Image could not be loaded");

        spec_.width = width;
        spec_.height = height;

        if (channels == 4)
        {
            internalFormat_ = GL_RGBA8;
            dataFormat_ = GL_RGBA;
        }
        else if (channels == 3)
        {
            internalFormat_ = GL_RGB;
            dataFormat_ = GL_RGB;
        }
        else if (channels == 1)
        {
            internalFormat_ = GL_R8;
            dataFormat_ = GL_RED;
        }

        DBG_ASSERT(internalFormat_ & dataFormat_, "Format not supported");

        loadFromBytes(bytes);

        stbi_image_free(bytes);

        loaded_ = true;
    }

    void ResourceImage::loadBuiltinWhite()
    {
        spec_ = TextureSpecification();

        dataFormat_ = util::vineImageFormatToGLDataFormat(spec_.format);
        internalFormat_ = util::vineImageFormatToGLInternalFormat(spec_.format);

        uint32_t whiteTex = 0xffffffff;
        loadFromBytes(&whiteTex);

        loaded_ = true;
    }


    void ResourceImage::loadFromBytes(const void* bytes)
    {
        const ResourceImageCreationData* data = dynamic_cast<const ResourceImageCreationData*>(getCreationData());

        glGenTextures(1, &rendererID_);
        glBindTexture(GL_TEXTURE_2D, rendererID_);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, util::vineFilterModeToGLFilterMode(data->samplerSettings.minFilter));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, util::vineFilterModeToGLFilterMode(data->samplerSettings.magFilter));

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, util::vineWrapModeToGLWrapMode(data->samplerSettings.sWrap));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, util::vineWrapModeToGLWrapMode(data->samplerSettings.tWrap));

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat_, spec_.width, spec_.height, 0, dataFormat_, GL_UNSIGNED_BYTE, bytes);
        if (spec_.generateMips)
            glGenerateMipmap(GL_TEXTURE_2D);

        loaded_ = true;
    }

    Ref<ResourceImage> ResourceImage::create(const std::string& file, const TextureSamplerSettings& settings)
    {
        ResourceImageCreationData data = ResourceImageCreationData(file, settings);
        ResourceImage* res = new ResourceImage(data);
        res->loadFromFile();

        return Ref<ResourceImage>(res);
    }

    Ref<ResourceImage> ResourceImage::createFromBytes(const void* bytes, const std::string& name, const TextureSpecification& spec, const TextureSamplerSettings& settings)
    {
        ResourceImageCreationData data = ResourceImageCreationData(name, settings);
        ResourceImage* res = new ResourceImage(data);
        res->spec_ = spec;

        res->dataFormat_ = util::vineImageFormatToGLDataFormat(spec.format);
        res->internalFormat_ = util::vineImageFormatToGLInternalFormat(spec.format);

        res->loadFromBytes(bytes);

        return Ref<ResourceImage>(res);
    }

    Ref<ResourceImage> ResourceImage::createBuiltinWhite()
    {
        TextureSamplerSettings settings;
        settings.minFilter = settings.magFilter = TextureFilterMode::Linear;
        settings.sWrap = settings.tWrap = TextureWrapMode::Repeat;

        ResourceImageCreationData data = ResourceImageCreationData(std::string(BUILTIN_WHITE_TEXTURE_KEY), settings);

        ResourceImage* res = new ResourceImage(data);
        res->loadBuiltinWhite();

        return Ref<ResourceImage>(res);
    }
}