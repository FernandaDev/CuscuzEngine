#pragma once

#include <SDL_render.h>
#include "Render/Sprite.h"

class Texture;

class ResourceManager
{
    std::string m_RootPath;
    std::unordered_map<std::string, std::shared_ptr<Texture>> m_Textures;
    std::vector<std::shared_ptr<Sprite>> m_Sprites;

public:
    static ResourceManager& Get()
    {
        static auto* s_Instance = new ResourceManager();
        return *s_Instance;
    }

    void SetRootResourcesPath(const std::string& RootPath);
    
    std::weak_ptr<Texture> GetTexture(SDL_Renderer* Renderer, const std::string& Filepath);

    std::weak_ptr<Sprite> CreateSprite(const std::string& FilePath, SDL_Renderer* Renderer);
    
    void UnloadResources();
    
private:
    ResourceManager() = default;
    ~ResourceManager() = default;
    ResourceManager(ResourceManager const&){}
    ResourceManager operator=(ResourceManager const&){return *this;}
};
