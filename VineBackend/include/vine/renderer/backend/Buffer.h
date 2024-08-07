#pragma once

#include <string>
#include <vector>

namespace vine
{
    enum class ShaderDataType
    {
        None = 0,
        Bool,
        Float, Float2, Float3, Float4,
        Int, Int2, Int3, Int4,
        Mat3, Mat4,
    };

    uint32_t shaderDataTypeSize(ShaderDataType type);

    class BufferElement
    {
    public:
        std::string name;
        ShaderDataType type;
        uint32_t size;
        size_t offset;
        bool normalized;

        BufferElement() = default;

        BufferElement(const std::string& name, ShaderDataType type, bool normalized = false)
            : name(name), type(type), size(shaderDataTypeSize(type)), offset(0), normalized(normalized)
        {
        }

        uint32_t getComponentCount() const;
    };

    class BufferLayout
    {
    public:
        BufferLayout()
        {
        }

        BufferLayout(std::initializer_list<BufferElement> elements)
            : elements_(elements)
        {
            calculateOffsetStide();
        }

        uint32_t getStride() const { return stride_; }
        const std::vector<BufferElement>& getElements() const { return elements_; }

        std::vector<BufferElement>::iterator begin() { return elements_.begin(); }
        std::vector<BufferElement>::iterator end() { return elements_.end(); }
        std::vector<BufferElement>::const_iterator begin() const { return elements_.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return elements_.end(); }

    private:
        void calculateOffsetStide();

    private:
        std::vector<BufferElement> elements_;
        uint32_t stride_ = 0;
    };

    class VertexBuffer
    {
    public:
        VertexBuffer(float* vertices, uint32_t size);
        VertexBuffer(uint32_t size);

        ~VertexBuffer();

        void bind() const;
        void unbind() const;

        void setData(const void* data, uint32_t size);

        const BufferLayout& getLayout() const { return layout_; }
        void setLayout(const BufferLayout& layout) { layout_ = layout; }

    private:
        uint32_t rendererID_;
        BufferLayout layout_;
    };

    class IndexBuffer
    {
    public:
        IndexBuffer(uint32_t* indices, uint32_t count);
        ~IndexBuffer();

        void bind() const;
        void unbind() const;

        uint32_t getCount() const { return count_; }

    private:
        uint32_t rendererID_;
        uint32_t count_;
    };
}