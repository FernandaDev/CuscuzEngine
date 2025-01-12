#pragma once

class IRender
{
public:
    virtual void Draw() = 0;
    virtual int GetDrawOrder() const = 0;
};
