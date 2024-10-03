#pragma once
#include <SDL_keyboard.h>
#include <SDL_mouse.h>
#include <SDL_stdinc.h>

class Input
{
public:
    static bool IsKeyPressed(unsigned int keyCode)
    {
        const Uint8* key_CurrentState = SDL_GetKeyboardState(nullptr);
        return key_CurrentState[keyCode];
    }

    static bool IsMousePressed(unsigned int button)
    {
        return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(button);
    }
};
