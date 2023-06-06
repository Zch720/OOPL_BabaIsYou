#include "stdafx.h"
#include "style.h"
#include "../Expansion/log.h"

Style StyleProc::GetStyleByName(std::string name) {
    if (name == "style_default") {
        return STYLE_DEFAULT;
    } else if (name == "style_lake") {
        return STYLE_LAKE;
    } else if (name == "style_island") {
        return STYLE_ISLAND;
    } else if (name == "style_ruin") {
        return STYLE_RUIN;
    }
    Log::LogError("Unknown style name: %s", name.c_str());
    return STYLE_NONE;
}

std::string StyleProc::GetStyleName(Style style) {
    switch (style) {
    case STYLE_DEFAULT:
        return "style_default";
    case STYLE_LAKE:
        return "style_lake";
    case STYLE_ISLAND:
        return "style_island";
    case STYLE_RUIN:
        return "style_ruin";
    }
    Log::LogError("Unknown style: %d", style);
    return "";
}