#pragma once
#include <SDL_render.h>

#define TextureMap std::unordered_map<std::string, SDL_Texture*>

class ResourceManager
{
    TextureMap m_Textures;
    
public:
    static ResourceManager& Instance()
    {
        static ResourceManager* s_Instance = new ResourceManager();
        return *s_Instance;
    }

    SDL_Texture& GetTexture(SDL_Renderer* Renderer, const std::string& Filepath);
    
private:
    ResourceManager() = default;
    ~ResourceManager();
    ResourceManager(ResourceManager const&){}
    ResourceManager operator=(ResourceManager const&){return *this;}
};
