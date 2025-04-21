#pragma once

namespace Cuscuz
{
    namespace Utils
    {
        static std::string ExtractNameFromFile(const std::string& source)
        {
            //Example:
            //  "Assets/Shaders/Sprite.glsl"

            size_t nameBegin = source.find_last_of("/\\"); // try to find the last slash or backslash.

            if(nameBegin == std::string::npos) 
                nameBegin = 0; // we didn't find slashes, so we'll start at the beginning of the string.
            else
                nameBegin = nameBegin + 1; // we found a slash and the name starts 1 char after the slash.

            const size_t lastDot = source.rfind('.'); // try to find a dot/file extension.
            size_t nameCharCount;
    
            if(lastDot == std::string::npos) 
                nameCharCount = source.size() - nameBegin; // if we didn't find a dot, just count from the end of the source.
            else
                nameCharCount = lastDot - nameBegin; // otherwise count from the dot that we found.

            return source.substr(nameBegin, nameCharCount);
        }
    }
}
