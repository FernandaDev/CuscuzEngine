#pragma once

#include <SDL_keyboard.h>
#include <SDL_mouse.h>
#include <SDL_stdinc.h>

namespace Cuscuz
{
    class Input
    {
    public:
        static bool IsKeyPressed(uint32_t keyCode);

        static bool IsMousePressed(uint32_t button);
        static std::pair<uint32_t, uint32_t> GetMousePositionInt();
        static std::pair<float, float> GetMousePosition();
        static float GetMouseX();
        static float GetMouseY();
    };
} 