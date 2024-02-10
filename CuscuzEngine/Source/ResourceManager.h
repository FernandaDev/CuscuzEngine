#pragma once

#include <SDL_render.h>
#include "pch.h"

#include "Render/Texture.h"

class ResourceManager
{
    std::unordered_map<std::string, std::shared_ptr<Texture>> m_Textures;
    std::string m_RootPath;
    
public:
    static ResourceManager& Instance()
    {
        static auto* s_Instance = new ResourceManager();
        return *s_Instance;
    }

    void SetRootResourcesPath(const std::string& RootPath);
    
    std::weak_ptr<Texture> GetTexture(SDL_Renderer* Renderer, const std::string& Filepath);

    void UnloadResources();
    
private:
    ResourceManager() = default;
    ~ResourceManager() = default;
    ResourceManager(ResourceManager const&){}
    ResourceManager operator=(ResourceManager const&){return *this;}
};
