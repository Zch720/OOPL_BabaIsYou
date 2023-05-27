#include "stdafx.h"
#include "center_text.h"
#include "../Library/gameutil.h"
#include "log.h"

void CenterTextDraw::Print(CDC *pDC, int centerX, int centerY, std::string text) {
    POINT textareaSize = calculateTextareaSize(pDC, text);
    game_framework::CTextDraw::Print(pDC, centerX - textareaSize.x / 2, centerY - textareaSize.y / 2, text);
}

POINT CenterTextDraw::calculateTextareaSize(CDC *pDC, std::string text) {
    CSize result = pDC->GetOutputTextExtent(text.c_str());
    return {result.cx, (LONG)(result.cy * 1.2)};
}