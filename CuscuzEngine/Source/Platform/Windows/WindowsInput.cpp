#include "pch.h"

#include "Cuscuz/Core/Input.h"

namespace Cuscuz
{
    bool Input::IsKeyPressed(uint32_t keyCode)
    {
        const Uint8* key_CurrentState = SDL_GetKeyboardState(nullptr);
        return key_CurrentState[keyCode];
    }

    bool Input::IsMousePressed(uint32_t button)
    {
        return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(button);
    }

    std::pair<uint32_t, uint32_t> Input::GetMousePositionInt()
    {
        static int x, y;
        SDL_GetMouseState(&x, &y);
        return std::pair<uint32_t, uint32_t>{x,y};
    }

    std::pair<float, float> Input::GetMousePosition()
    {
        static int x, y;
        SDL_GetMouseState(&x, &y);
        return std::pair<float, float>{x,y};
    }

    float Input::GetMouseX()
    {
        static int x;
        SDL_GetMouseState(&x, nullptr);
        return static_cast<float>(x);
    }
    
    float Input::GetMouseY()
    {
        static int y;
        SDL_GetMouseState(nullptr, &y);
        return static_cast<float>(y);
    }
}
