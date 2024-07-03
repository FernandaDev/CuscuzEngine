#pragma once

class IRender
{
public:
    void virtual Draw(SDL_Renderer* renderer) = 0; // TODO create an abstraction for a Renderer!
    int virtual GetDrawOrder() const = 0;
};