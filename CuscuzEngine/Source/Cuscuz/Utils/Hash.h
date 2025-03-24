#pragma once

namespace Cuscuz
{
    constexpr uint32_t fnv1a_32(std::string_view str, uint32_t hash = 0x811c9dc5)
    {
        return str.empty() ? hash : fnv1a_32(str.substr(1), (hash ^ str[0]) * 0x1000193);
    }
}
