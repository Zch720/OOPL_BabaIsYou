#pragma once

#include <string>

class CenterTextDraw {
private:
    static POINT calculateTextareaSize(CDC *pDC, std::string text);

public:
    static void Print(CDC *pDC, int centerX, int centerY, std::string text);
};