#include <vine/renderer/backend/VertexArray.h>

#include <vine/core/Logger.h>

#include <glad/glad.h>

namespace vine
{
    static GLenum ShaderDataTypeToGL(ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::Bool: return GL_BOOL;

        case ShaderDataType::Float: return GL_FLOAT;
        case ShaderDataType::Float2: return GL_FLOAT;
        case ShaderDataType::Float3: return GL_FLOAT;
        case ShaderDataType::Float4: return GL_FLOAT;

        case ShaderDataType::Int: return GL_INT;
        case ShaderDataType::Int2: return GL_INT;
        case ShaderDataType::Int3: return GL_INT;
        case ShaderDataType::Int4: return GL_INT;

        case ShaderDataType::Mat3: return GL_FLOAT;
        case ShaderDataType::Mat4: return GL_FLOAT;
        }

        DBG_ASSERT(false, "Unknown shader data type!");
        return GL_NONE;
    }

    VertexArray::VertexArray()
        : vbIndex_(0)
    {
        glGenVertexArrays(1, &rendererID_);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &rendererID_);
    }

    void VertexArray::bind() const
    {
        glBindVertexArray(rendererID_);
    }

    void VertexArray::unbind() const
    {
        glBindVertexArray(0);
    }

    void VertexArray::addVertexBuffer(const VertexBufferRef& vertexBuffer)
    {
        DBG_ASSERT(vertexBuffer->getLayout().getElements().size() > 0, "Vertex buffer has no layout");

        glBindVertexArray(rendererID_);
        vertexBuffer->bind();

        const BufferLayout& layout = vertexBuffer->getLayout();
        for (const auto& element : layout)
        {
            switch (element.type)
            {
            case ShaderDataType::Float:
            case ShaderDataType::Float2:
            case ShaderDataType::Float3:
            case ShaderDataType::Float4:
            {
                glEnableVertexAttribArray(vbIndex_);
                glVertexAttribPointer(
                    vbIndex_,
                    element.getComponentCount(),
                    ShaderDataTypeToGL(element.type),
                    element.normalized ? GL_TRUE : GL_FALSE,
                    layout.getStride(),
                    (const void*)element.offset
                );
                vbIndex_++;
                break;
            }

            case ShaderDataType::Bool:
            case ShaderDataType::Int:
            case ShaderDataType::Int2:
            case ShaderDataType::Int3:
            case ShaderDataType::Int4:
            {
                glEnableVertexAttribArray(vbIndex_);
                glVertexAttribIPointer(
                    vbIndex_,
                    element.getComponentCount(),
                    ShaderDataTypeToGL(element.type),
                    layout.getStride(),
                    (const void*)element.offset
                );
                vbIndex_++;
                break;
            }

            case ShaderDataType::Mat3:
            case ShaderDataType::Mat4:
            {
                uint8_t count = (uint8_t)element.getComponentCount();
                for (uint8_t i = 0; i < count; i++)
                {
                    glEnableVertexAttribArray(vbIndex_);
                    glVertexAttribPointer(
                        vbIndex_,
                        count,
                        ShaderDataTypeToGL(element.type),
                        element.normalized ? GL_TRUE : GL_FALSE,
                        layout.getStride(),
                        (const void*)(element.offset + sizeof(float) * count * i)
                    );
                    glVertexAttribDivisor(vbIndex_, 1);
                    vbIndex_++;
                }
                break;
            }
            default:
                DBG_ASSERT(false, "Unknown shader data type!");
                break;
            }
        }

        vertexBuffers_.push_back(vertexBuffer);
    }

    void VertexArray::setIndexBuffer(const IndexBufferRef& indexBuffer)
    {
        glBindVertexArray(rendererID_);
        indexBuffer->bind();

        indexBuffer_ = indexBuffer;
    }

    VertexArrayRef createVertexArray()
    {
        return std::make_shared<VertexArray>();
    }
}