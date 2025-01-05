#pragma once

#include <cstdint>
#include <vector>
#include <memory>

namespace vine
{
    enum class FramebufferTextureFormat
    {
        None = 0,
        RGBA8,
        RED_INTEGER,
        DEPTH24STENCIL8,
    };

    struct FramebufferTextureSpecification
    {
        FramebufferTextureSpecification()
            : format(FramebufferTextureFormat::None)
        {
        }

        FramebufferTextureSpecification(FramebufferTextureFormat format)
            : format(format)
        {
        }

        FramebufferTextureFormat format;
    };

    struct FramebufferAttachmentSpecification
    {
        FramebufferAttachmentSpecification() = default;

        FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments)
            : attachments(attachments)
        {
        }

        std::vector<FramebufferTextureSpecification> attachments;
    };

    struct FramebufferSpecification
    {
        FramebufferSpecification()
            : width(0), height(0), samples(1), swapChainTarget(false)
        {
        }

        uint32_t width, height;
        FramebufferAttachmentSpecification attachments;
        uint32_t samples;
        bool swapChainTarget;
    };

    class Framebuffer
    {
    public:
        Framebuffer(const FramebufferSpecification& spec);
        ~Framebuffer();

        void invalidate();

        void bind() const;
        void unbind() const;

        void resize(uint32_t width, uint32_t height);
        int readPixel(uint32_t attachmentIndex, int x, int y);

        void clearAttachment(uint32_t attachmentIndex, int value);
        uint32_t getColorAttachmentID(uint32_t index = 0) { return colorAttachments_[index]; }

        const FramebufferSpecification& getSpecification() const { return specification_; }

    private:
        uint32_t rendererID_;
        FramebufferSpecification specification_;

        std::vector<FramebufferTextureSpecification> colorAttachmentSpecifications_;
        FramebufferTextureSpecification depthAttachmentSpecification_;

        std::vector<uint32_t> colorAttachments_;
        uint32_t depthAttachment_;
    };

    using FramebufferRef = std::shared_ptr<Framebuffer>;
    FramebufferRef createFramebuffer(const FramebufferSpecification& spec);
}