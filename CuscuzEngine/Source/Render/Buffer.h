#pragma once
#include "Core/CC_Core.h"

enum class ShaderDataType //this should probably be in the shader class?
{
    None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
};

static uint32_t GetShaderDataTypeSize(ShaderDataType type)
{
    switch (type)
    {
        case ShaderDataType::Int:
        case ShaderDataType::Float:   return 4;
            
        case ShaderDataType::Int2:
        case ShaderDataType::Float2:  return 4 * 2;
            
        case ShaderDataType::Int3:
        case ShaderDataType::Float3:  return 4 * 3;
            
        case ShaderDataType::Int4:
        case ShaderDataType::Float4:  return 4 * 4;
            
        case ShaderDataType::Mat3:    return 4 * 3 * 3;
        case ShaderDataType::Mat4:    return 4 * 4 * 4;
            
        case ShaderDataType::Bool:    return 1;
    
        case ShaderDataType::None:
        default:
            CC_ASSERT(false, "Invalid shader type!")
            return 0;
    }
}

struct BufferElement
{
    ShaderDataType Type;
    std::string Name;
    uint32_t Size;
    uint32_t Offset;
    bool Normalized;

    BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
        : Type(type), Name(name), Size(GetShaderDataTypeSize(type)), Offset(0), Normalized(normalized) {}

    uint32_t GetElementCount() const
    {
        switch (Type)
        {
            case ShaderDataType::Int:
            case ShaderDataType::Float:   return 1;
                
            case ShaderDataType::Int2:
            case ShaderDataType::Float2:  return 2;
                
            case ShaderDataType::Int3:
            case ShaderDataType::Float3:  return 3;
                
            case ShaderDataType::Int4:
            case ShaderDataType::Float4:  return 4;
                
            case ShaderDataType::Mat3:    return 3 * 3;
            case ShaderDataType::Mat4:    return 4 * 4;
                
            case ShaderDataType::Bool:    return 1;
        
            case ShaderDataType::None:
            default:
                CC_ASSERT(false, "Invalid shader type!")
                return 0;
        }
    }
};

class BufferLayout
{
    std::vector<BufferElement> m_Elements;
    uint32_t m_Stride;

public:
    BufferLayout() = default;
    BufferLayout(const std::initializer_list<BufferElement>& elements)
        : m_Elements(elements), m_Stride(0)
    {
        CalculateStrideAndOffset();
    }

    const std::vector<BufferElement>& GetElements() const { return m_Elements; }
    uint32_t GetStride() const { return m_Stride; }

    std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
    std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
    
private:
    void CalculateStrideAndOffset()
    {
        m_Stride = 0;
        uint32_t offset = 0;

        for(auto& element : m_Elements)
        {
            element.Offset = offset;
            offset += element.Size;
            m_Stride += element.Size;
        }
    }
};

class VertexBuffer
{
public:
    virtual ~VertexBuffer() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual const BufferLayout& GetLayout() const = 0;
    virtual void SetLayout(const BufferLayout& layout) = 0;

    static CC_AssetRef<VertexBuffer> Create(const void* data, uint32_t size);
};


class IndexBuffer
{
public:
    virtual ~IndexBuffer() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual uint32_t GetCount() const = 0;

    static CC_AssetRef<IndexBuffer> Create(const uint32_t* data, uint32_t count);
};