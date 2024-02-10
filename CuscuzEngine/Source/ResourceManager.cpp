#include "pch.h"
#include "ResourceManager.h"
#include "Utils/Log.h"
#include <filesystem>

void ResourceManager::SetRootResourcesPath(const std::string& RootPath)
{
    m_RootPath = std::filesystem::absolute(RootPath).string();
}

std::weak_ptr<Texture> ResourceManager::GetTexture(SDL_Renderer* Renderer,  const std::string& Filepath)
{
    const auto surfaceSearch = m_Textures.find(Filepath);

    if(surfaceSearch != m_Textures.end())
        return m_Textures[Filepath];

    const std::string fullFilePath = m_RootPath + Filepath;

    std::shared_ptr<Texture> newTexture =
        std::make_shared<Texture>(Renderer, fullFilePath.c_str());

    if(!newTexture)
    {
        LOG_ERROR("Couldn't load the texture!");
        return {};
    }

    m_Textures.insert(std::make_pair(Filepath, newTexture));
    
    return newTexture;
}

void ResourceManager::UnloadResources()
{
    m_Textures.clear();
}