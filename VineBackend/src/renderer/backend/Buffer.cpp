#include <vine/renderer/backend/Buffer.h>

#include <vine/core/Logger.h>

#include <glad/glad.h>

namespace vine
{
    uint32_t shaderDataTypeSize(ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::Bool: return 1;

        case ShaderDataType::Float: return 4;
        case ShaderDataType::Float2: return 4 * 2;
        case ShaderDataType::Float3: return 4 * 3;
        case ShaderDataType::Float4: return 4 * 4;

        case ShaderDataType::Int: return 4;
        case ShaderDataType::Int2: return 4 * 2;
        case ShaderDataType::Int3: return 4 * 3;
        case ShaderDataType::Int4: return 4 * 4;

        case ShaderDataType::Mat3: return 4 * 3 * 3;
        case ShaderDataType::Mat4: return 4 * 4 * 4;
        }

        DBG_ASSERT(false, "Unknown shader data type!");
        return 0;
    }

    uint32_t BufferElement::getComponentCount() const
    {
        switch (type)
        {
        case ShaderDataType::Bool: return 1;

        case ShaderDataType::Float: return 1;
        case ShaderDataType::Float2: return 2;
        case ShaderDataType::Float3: return 3;
        case ShaderDataType::Float4: return 4;

        case ShaderDataType::Int: return 1;
        case ShaderDataType::Int2: return 2;
        case ShaderDataType::Int3: return 3;
        case ShaderDataType::Int4: return 4;

        case ShaderDataType::Mat3: return 3;
        case ShaderDataType::Mat4: return 4;
        }

        DBG_ASSERT(false, "Unknown shader data type!");
        return 0;
    }

    void BufferLayout::calculateOffsetStide()
    {
        size_t offset = 0;
        stride_ = 0;

        for (auto& element : elements_)
        {
            element.offset = offset;
            offset += element.size;
            stride_ += element.size;
        }
    }

    VertexBuffer::VertexBuffer(float* vertices, uint32_t size)
    {
        glGenBuffers(1, &rendererID_);
        glBindBuffer(GL_ARRAY_BUFFER, rendererID_);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    VertexBuffer::VertexBuffer(uint32_t size)
    {
        glGenBuffers(1, &rendererID_);
        glBindBuffer(GL_ARRAY_BUFFER, rendererID_);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &rendererID_);
    }

    void VertexBuffer::bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, rendererID_);
    }

    void VertexBuffer::unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::setData(const void* data, uint32_t size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, rendererID_);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }

    IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count)
        : count_(count)
    {
        glGenBuffers(1, &rendererID_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count_ * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &rendererID_);
    }

    void IndexBuffer::bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID_);
    }

    void IndexBuffer::unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}