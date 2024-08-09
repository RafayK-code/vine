#pragma once

#include <vine/renderer/backend/Buffer.h>

namespace vine
{
    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        void bind() const;
        void unbind() const;

        void addVertexBuffer(const VertexBufferRef& vertexBuffer);
        void setIndexBuffer(const IndexBufferRef& indexBuffer);

        const std::vector<VertexBufferRef>& getVertexBuffers() const { return vertexBuffers_; }
        const IndexBufferRef & getIndexBuffer() const { return indexBuffer_; }

    private:
        uint32_t rendererID_;
        uint32_t vbIndex_;

        std::vector<VertexBufferRef> vertexBuffers_;
        IndexBufferRef indexBuffer_;
    };

    using VertexArrayRef = std::shared_ptr<VertexArray>;
    VertexArrayRef createVertexArray();
}