#include "pch.h"

#include "ResourceManager.h"
#include "Utils/Log.h"
#include "Render/Texture.h"

void ResourceManager::SetRootResourcesPath(const std::string& rootPath)
{
    m_RootPath = std::filesystem::absolute(rootPath).string();
}

std::weak_ptr<Texture> ResourceManager::GetTexture(SDL_Renderer* renderer,  const std::string& filePath)
{
    const auto surfaceSearch = m_Textures.find(filePath);

    if(surfaceSearch != m_Textures.end())
        return m_Textures[filePath];

    const std::string fullFilePath = m_RootPath + filePath;

    std::shared_ptr<Texture> newTexture =
        std::make_shared<Texture>(renderer, fullFilePath.c_str());

    if(!newTexture)
    {
        LOG_ERROR("Couldn't load the texture!");
        return {};
    }

    m_Textures.insert(std::make_pair(filePath, newTexture));
    
    return newTexture;
}

void ResourceManager::UnloadResources()
{
    m_Textures.clear();
    m_Sprites.clear();
}

std::weak_ptr<Sprite> ResourceManager::CreateSprite(const std::string& filePath, SDL_Renderer* renderer)
{
    std::weak_ptr<Texture> newTexture = GetTexture(renderer, filePath);

    auto newSprite = std::make_shared<Sprite>(newTexture);
    m_Sprites.emplace_back(newSprite);

    return newSprite;
}
