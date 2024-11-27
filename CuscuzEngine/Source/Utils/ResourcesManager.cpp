#include "pch.h"
#include "ResourcesManager.h"

#include <ranges>

#include "Platform/OpenGL/OpenGLTexture.h"

ResourcesManager* ResourcesManager::s_Instance = nullptr;

unsigned short g_GUID = 1;

void ResourcesManager::Init()
{
    m_DefaultTexture = std::make_unique<OpenGLTexture>();
    LoadAllTextures("Assets/Images");
}

void ResourcesManager::Unload()
{
    m_TexturesMap.clear();
    m_NameToGUIDMap.clear();
    g_GUID = 1;
}

void ResourcesManager::LoadAllTextures(const std::string& directory)
{
    for (const auto& entry : std::filesystem::directory_iterator(directory))
    {
        if (entry.is_regular_file())
        {
            std::string path = entry.path().generic_string();
            
            if (path.ends_with(".png") || path.ends_with(".jpg") || path.ends_with(".jpeg"))
            {
                m_TexturesMap[g_GUID] = std::make_unique<OpenGLTexture>(path.data());
                m_TexturesMap[g_GUID]->SetGUID(g_GUID);
                
                const auto textureName = m_TexturesMap[g_GUID]->GetName();
                if(m_NameToGUIDMap.contains(textureName))
                    LOG_ERROR("The {0} texture is duplicated!", textureName);
                else
                    m_NameToGUIDMap[textureName] = g_GUID;

                g_GUID++;
            }
        }
    }
}   

Texture* ResourcesManager::GetTexture(unsigned short GUID)
{
    if(m_TexturesMap.contains(GUID))
        return m_TexturesMap[GUID].get();

    LOG_ERROR("Couldn't find texture: {0}", GUID);
    return m_DefaultTexture.get();
}

Texture* ResourcesManager::GetTexture(const std::string& name)
{
    if(m_NameToGUIDMap.contains(name))
        return GetTexture(m_NameToGUIDMap[name]);
    
    LOG_ERROR("Couldn't find texture: {0}", name);
    return m_DefaultTexture.get();
}

std::vector<std::reference_wrapper<Texture>> ResourcesManager::GetAllTextures() const
{
    std::vector<std::reference_wrapper<Texture>> textures {};
    textures.reserve(m_TexturesMap.size());

    for (const auto& tex : m_TexturesMap | std::views::values)
    {
        textures.emplace_back(*tex);
    }

    return textures;
}
