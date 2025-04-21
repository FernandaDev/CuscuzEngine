#include "pch.h"

#include <commdlg.h>

#include "Cuscuz/Utils/PlatformUtils.h"
#include "Cuscuz/Core/Engine.h"
#include "Cuscuz/Core/Window.h"

namespace Cuscuz
{
    std::string FileDialogs::OpenFile(const char* filter)
    {
        OPENFILENAMEA ofn;
        CHAR szFile[260] = { 0 };
        ZeroMemory(&ofn, sizeof(OPENFILENAME));
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.hwndOwner = Engine::Get().CC_Window->GetWindowHandle();
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = filter;
        ofn.nFilterIndex = 1;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
        if(GetOpenFileNameA(&ofn) == TRUE)
        {
            return ofn.lpstrFile;
        }
        return {};
    }
    
    std::string FileDialogs::SaveFile(const char* filter, const char* defaultType, const char* defaultName)
    {
        OPENFILENAMEA ofn;
        CHAR szFile[260];
        strncpy(szFile, defaultName, sizeof(szFile));
        szFile[sizeof(szFile) - 1] = '\0';
        
        ZeroMemory(&ofn, sizeof(OPENFILENAME));
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.hwndOwner = Engine::Get().CC_Window->GetWindowHandle();
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = filter;
        ofn.nFilterIndex = 1;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;
        ofn.lpstrDefExt = defaultType;
        
        if(GetSaveFileNameA(&ofn) == TRUE)
        {
            return ofn.lpstrFile;
        }
        return {};
    }
}
