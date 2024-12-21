#pragma once
#include "Shader.h"
#include "VertexArray.h"

class IRender
{
public:
    virtual void Draw() = 0;
    virtual int GetDrawOrder() const = 0;
    virtual const CC_AssetRef<VertexArray>& GetVertexArray() const = 0;
    virtual const CC_AssetRef<Shader>& GetShader() const = 0;
};
