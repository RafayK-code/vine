#pragma once

#include <vine/renderer/backend/Buffer.h>
#include <vine/core/Base.h>

namespace vine
{
    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        void bind() const;
        void unbind() const;

        void addVertexBuffer(const RefPtr<VertexBuffer>& vertexBuffer);
        void setIndexBuffer(const RefPtr<IndexBuffer>& indexBuffer);

        const std::vector<RefPtr<VertexBuffer>>& getVertexBuffers() const { return vertexBuffers_; }
        const RefPtr<IndexBuffer>& getIndexBuffer() const { return indexBuffer_; }

    private:
        uint32_t rendererID_;
        uint32_t vbIndex_;

        std::vector<RefPtr<VertexBuffer>> vertexBuffers_;
        RefPtr<IndexBuffer> indexBuffer_;
    };
}