#pragma once

#include <string>

enum Style {
    STYLE_NONE,
    STYLE_DEFAULT,
    STYLE_LAKE,
    STYLE_ISLAND,
    STYLE_RUIN,
};

class StyleProc {
public:
    static Style GetStyleByName(std::string name);
    static std::string GetStyleName(Style style);
};