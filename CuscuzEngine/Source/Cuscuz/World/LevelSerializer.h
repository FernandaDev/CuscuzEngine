#pragma once

#include "Cuscuz/Core/Core.h"

namespace Cuscuz
{
    class Level;

    class LevelSerializer
    {
        CC_AssetRef<Level> m_Level;
        
    public:
        LevelSerializer(const CC_AssetRef<Level>& level);

        void Serialize(const std::string& filepath);
        void SerializeRuntime(const std::string& filepath);

        bool Deserialize(const std::string& filepath);
        bool DeserializeRuntime(const std::string& filepath);
    };
}
