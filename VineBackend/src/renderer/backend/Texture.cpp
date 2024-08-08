#include <vine/renderer/backend/Texture.h>

#include <vine/core/Logger.h>

#include <stb/stb_image.h>

namespace vine
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

    Texture::Texture(const TextureSpecification& spec)
        : spec_(spec), loaded_(false)
    {
        dataFormat_ = vineImageFormatToGLDataFormat(spec_.format);
        internalFormat_ = vineImageFormatToGLInternalFormat(spec_.format);

        glGenTextures(1, &rendererID_);
        glBindTexture(GL_TEXTURE_2D, rendererID_);
        
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat_, spec_.width, spec_.height, 0, dataFormat_, GL_UNSIGNED_BYTE, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        if (spec.generateMips)
            glGenerateMipmap(GL_TEXTURE_2D);
    }

    Texture::Texture(const std::string& path)
        : internalFormat_(0), dataFormat_(0)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

        DBG_ASSERT(data, "Image could not be loaded");

        loaded_ = true;
        spec_.width = width;
        spec_.height = height;

        if (channels == 4)
        {
            internalFormat_ = GL_RGBA8;
            dataFormat_ = GL_RGBA;
        }
        else if (channels == 3)
        {
            internalFormat_ = GL_RGB8;
            dataFormat_ = GL_RGB;
        }
        else if (channels == 1)
        {
            internalFormat_ = GL_R8;
            dataFormat_ = GL_RED;
        }

        DBG_ASSERT(internalFormat_ & dataFormat_, "Format not supported");

        glGenTextures(1, &rendererID_);
        glBindTexture(GL_TEXTURE_2D, rendererID_);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat_, spec_.width, spec_.height, 0, dataFormat_, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &rendererID_);
    }

    void Texture::setData(void* data, uint32_t size)
    {
        uint32_t bpp = 0;
        if (dataFormat_ == GL_RGBA)
            bpp = 4;
        else if (dataFormat_ == GL_RGB)
            bpp = 3;
        else if (dataFormat_ == GL_RED)
            bpp = 1;

        DBG_ASSERT(size == spec_.width * spec_.height * bpp, "Data must be entire texture");
        glBindTexture(GL_TEXTURE_2D, rendererID_);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, spec_.width, spec_.height, dataFormat_, GL_UNSIGNED_BYTE, data);
    }

    void Texture::bind(uint32_t slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, rendererID_);
    }

    void Texture::unbind(uint32_t slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, rendererID_);
    }
}