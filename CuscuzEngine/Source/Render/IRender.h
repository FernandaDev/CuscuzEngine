#pragma once
#include "Shader.h"
#include "VertexArray.h"

class IRender
{
public:
    virtual void Draw() = 0;
    virtual int GetDrawOrder() const = 0;
};
