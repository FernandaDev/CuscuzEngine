#pragma once
#include "Buffer.h"

namespace Cuscuz
{
    class VertexArray
    {
    public:
        virtual ~VertexArray() = default;
    
        virtual void AddBuffer(const CC_AssetRef<VertexBuffer>& vertexBuffer) = 0;
        virtual void SetIndexBuffer(const CC_AssetRef<IndexBuffer>& indexBuffer) = 0;
    
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual const std::vector<CC_AssetRef<VertexBuffer>>& GetVertexBuffers() const = 0;
        virtual const CC_AssetRef<IndexBuffer>& GetIndexBuffer() const = 0;
    
        static CC_AssetRef<VertexArray> Create();
    };
}