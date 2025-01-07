#include <vine/renderer/backend/Framebuffer.h>
#include <vine/core/Logger.h>

#include <glad/glad.h>

namespace vine
{
    static const uint32_t MAX_FRAMEBUFFER_SIZE = 8192;

    static GLenum textureTarget(bool multisampled)
    {
        return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
    }

    static void createTextures(bool multisampled, uint32_t* outID, uint32_t count)
    {
        glGenTextures(count, outID);
        GLenum target = textureTarget(multisampled);

        for (uint32_t i = 0; i < count; i++)
            glBindTexture(target, outID[i]);
    }

    static void bindTexture(bool multisampled, uint32_t id)
    {
        glBindTexture(textureTarget(multisampled), id);
    }

    static void attachColorTexture(uint32_t id, int samples, GLenum internalFormat, GLenum format, uint32_t width, uint32_t height, int index)
    {
        bool multisampled = samples > 1;
        if (multisampled)
            glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, GL_FALSE);
        else
        {
            glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, textureTarget(multisampled), id, 0);
    }

    static void attachDepthTexture(uint32_t id, int samples, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height)
    {
        bool multisampled = samples > 1;
        if (multisampled)
            glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
        else
        {
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, nullptr);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }

        glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, textureTarget(multisampled), id, 0);
    }

    static bool isDepthFormat(FramebufferTextureFormat format)
    {
        switch (format)
        {
        case FramebufferTextureFormat::DEPTH24STENCIL8: return true;
        }

        return false;
    }

    static GLenum framebufferTextureFormatToGL(FramebufferTextureFormat format)
    {
        switch (format)
        {
        case FramebufferTextureFormat::RGBA8: return GL_RGBA8;
        case FramebufferTextureFormat::RED_INTEGER: return GL_RED_INTEGER;
        }

        return 0;
    }

    Framebuffer::Framebuffer(const FramebufferSpecification& specification)
        :
        rendererID_(0),
        specification_(specification),
        depthAttachmentSpecification_(FramebufferTextureFormat::None),
        depthAttachment_(0)
    {
        for (auto spec : specification_.attachments.attachments)
        {
            if (!isDepthFormat(spec.format))
                colorAttachmentSpecifications_.emplace_back(spec);
            else
                depthAttachmentSpecification_ = spec;
        }

        invalidate();
    }

    Framebuffer::~Framebuffer()
    {
        glDeleteFramebuffers(1, &rendererID_);
        glDeleteTextures(colorAttachments_.size(), colorAttachments_.data());
        glDeleteTextures(1, &depthAttachment_);
    }

    void Framebuffer::invalidate()
    {
        if (rendererID_ > 0)
        {
            glDeleteFramebuffers(1, &rendererID_);
            glDeleteTextures(colorAttachments_.size(), colorAttachments_.data());
            glDeleteTextures(1, &depthAttachment_);

            colorAttachments_.clear();
            depthAttachment_ = 0;
        }

        glGenFramebuffers(1, &rendererID_);
        glBindFramebuffer(GL_FRAMEBUFFER, rendererID_);

        bool multisample = specification_.samples > 1;

        if (colorAttachmentSpecifications_.size() > 0)
        {
            colorAttachments_.resize(colorAttachmentSpecifications_.size());
            createTextures(multisample, colorAttachments_.data(), colorAttachments_.size());

            for (size_t i = 0; i < colorAttachments_.size(); i++)
            {
                bindTexture(multisample, colorAttachments_[i]);
                switch (colorAttachmentSpecifications_[i].format)
                {
                case FramebufferTextureFormat::RGBA8:
                    attachColorTexture(colorAttachments_[i], specification_.samples, GL_RGBA8, GL_RGBA, specification_.width, specification_.height, i);
                    break;
                case FramebufferTextureFormat::RED_INTEGER:
                    attachColorTexture(colorAttachments_[i], specification_.samples, GL_R32I, GL_RED_INTEGER, specification_.width, specification_.height, i);
                    break;
                }
            }
        }

        if (depthAttachmentSpecification_.format != FramebufferTextureFormat::None)
        {
            createTextures(multisample, &depthAttachment_, 1);
            bindTexture(multisample, depthAttachment_);
            
            switch (depthAttachmentSpecification_.format)
            {
            case FramebufferTextureFormat::DEPTH24STENCIL8:
                attachDepthTexture(depthAttachment_, specification_.samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, specification_.width, specification_.height);
                break;
            }
        }

        if (colorAttachments_.size() > 1)
        {
            DBG_ASSERT(colorAttachments_.size() <= 4, "Error");
            GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
            glDrawBuffers(colorAttachments_.size(), buffers);
        }
        else if (colorAttachments_.empty())
        {
            glDrawBuffer(GL_NONE);
        }

        DBG_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Frame buffer is incomplete");

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Framebuffer::bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, rendererID_);
        glViewport(0, 0, specification_.width, specification_.height);
    }

    void Framebuffer::unbind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Framebuffer::bindToTexture(uint32_t slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, colorAttachments_[0]);
    }

    void Framebuffer::unbindToTexture(uint32_t slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, colorAttachments_[0]);
    }

    void Framebuffer::resize(uint32_t width, uint32_t height)
    {
        if (width == 0 || height == 0 || width > MAX_FRAMEBUFFER_SIZE || height > MAX_FRAMEBUFFER_SIZE)
        {
            DBG_WARN("Attempted to resize framebuffer to {0}, {1}", width, height);
            return;
        }

        specification_.width = width;
        specification_.height = height;

        invalidate();
    }

    int Framebuffer::readPixel(uint32_t attachmentIndex, int x, int y)
    {
        DBG_ASSERT(attachmentIndex < colorAttachments_.size(), "Invalid attachment index");

        glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
        int pixelData;
        glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
        return pixelData;
    }

    void Framebuffer::clearAttachment(uint32_t attachmentIndex, int value)
    {
        DBG_ASSERT(attachmentIndex < colorAttachments_.size(), "Invalid attachment index");

        FramebufferTextureSpecification& spec = colorAttachmentSpecifications_[attachmentIndex];
        
        GLuint framebuffer;
        glGenFramebuffers(1, &framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorAttachments_[attachmentIndex], 0);

        GLint clearValue = value;
        glClearBufferiv(GL_COLOR, 0, &clearValue);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDeleteFramebuffers(1, &framebuffer);
    }

    FramebufferRef createFramebuffer(const FramebufferSpecification& spec)
    {
        return std::make_shared<Framebuffer>(spec);
    }
}