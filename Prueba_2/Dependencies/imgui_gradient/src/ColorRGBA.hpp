#pragma once

#include "Imgui/imgui.h" // Include ImVec4

namespace ImGG {

using ColorRGBA = ImVec4;

inline auto operator==(const ColorRGBA& a, const ColorRGBA& b) -> bool
{
    return (a.x == b.x)
           && (a.y == b.y)
           && (a.z == b.z)
           && (a.w == b.w);
}

} // namespace ImGG