#pragma once

class IRender
{
public:
    void virtual Draw() = 0;
    int virtual GetDrawOrder() const = 0;
};