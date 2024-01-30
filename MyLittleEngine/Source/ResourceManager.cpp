﻿#include "pch.h"
#include "ResourceManager.h"
#include "SDL_image.h"
#include "Utils/Log.h"
#include <filesystem>

void ResourceManager::SetRootResourcesPath(const std::string& RootPath)
{
    m_RootPath = std::filesystem::absolute(RootPath).string();
}

SDL_Texture& ResourceManager::GetTexture(SDL_Renderer* Renderer,  const std::string& Filepath)
{
    const auto surfaceSearch = m_Textures.find(Filepath);

    if(surfaceSearch != m_Textures.end())
        return *m_Textures[Filepath];

    const std::string fullFilePath = m_RootPath + Filepath;
    
    SDL_Texture* newTexture = IMG_LoadTexture(Renderer, fullFilePath.c_str());

    if(!newTexture)
        LOG_ERROR("Couldn't load the texture!");

    m_Textures.insert(std::make_pair(Filepath, newTexture));
    
    return *newTexture;
}

ResourceManager::~ResourceManager()
{
    for (const auto& texture : m_Textures)
        SDL_DestroyTexture(texture.second);

    m_Textures.clear();
}
