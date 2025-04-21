#pragma once 

#include <string>

namespace Cuscuz
{
    class FileDialogs
    {
    public:
        static std::string OpenFile(const char* filter);
        static std::string SaveFile(const char* filter,
                                    const char* defaultType,
                                    const char* defaultName = "Untitled");
    };
}