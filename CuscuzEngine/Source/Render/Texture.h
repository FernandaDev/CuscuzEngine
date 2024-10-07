#pragma once

//#include <SDL_image.h>
#include "SDL.h"
#include "Utils/Log.h"

class Texture
{
    SDL_Texture* m_Texture;
    
public:
   Texture(SDL_Renderer* renderer, std::string filePath) : m_Texture(nullptr)
   {
       //m_Texture = IMG_LoadTexture(renderer, filePath.c_str());

       if(!m_Texture)
           LOG_ERROR("Couldn't load the texture!");
   }

   ~Texture()
   {
       SDL_DestroyTexture(m_Texture);
       LOG_INFO("Destroyed texture!");
   }

    SDL_Texture* SDLPtr() const { return m_Texture; }
};
