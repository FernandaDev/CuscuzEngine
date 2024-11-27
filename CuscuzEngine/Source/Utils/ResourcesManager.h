#pragma once

#include <memory>
#include <unordered_map>
#include "Render/Texture.h"

class Texture;

class ResourcesManager
{
    static ResourcesManager* s_Instance;
    
    std::unordered_map<unsigned short, std::unique_ptr<Texture>> m_TexturesMap;
    std::unique_ptr<Texture> m_DefaultTexture;
    
    std::unordered_map<std::string, unsigned short> m_NameToGUIDMap;
    
public:
    void Init();
    void Unload();
    
    static ResourcesManager& Get()
    {
        if(!s_Instance)
            s_Instance = new ResourcesManager;
        return *s_Instance;
    }

    Texture* GetTexture(unsigned short GUID);
    Texture* GetTexture(const std::string& name);
    std::vector<std::reference_wrapper<Texture>> GetAllTextures() const;

private:
    void LoadAllTextures(const std::string& directory);
    
};
