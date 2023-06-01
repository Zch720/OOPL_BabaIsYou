#include "stdafx.h"
#include "pause.h"
#include "../../Expansion/center_text.h"


const int PauseLayout::RESUME_BUTTON_INDEX = 0;
const int PauseLayout::RETURN_TO_MAP_BUTTON_INDEX = 1;
const int PauseLayout::RESTART_BUTTON_INDEX = 2;
const int PauseLayout::SETTING_BUTTON_INDEX = 3;
const int PauseLayout::RETURN_TO_MENU_BUTTON_INDEX = 4;
const std::string PauseLayout::styleToString[4] = {
    "default",
    "water",
    "island",
    "ruin",
};
const POINT PauseLayout::buttonPosition[5] = {
    POINT{960, 161},
    POINT{960, 215},
    POINT{960, 269},
    POINT{960, 323},
    POINT{960, 404},
};
const std::string PauseLayout::buttonText[5] = {
    "RESUME",
    "RETURN TO MAP",
    "RESTART",
    "SETTING",
    "RETURN TO MENU",
};
const POINT PauseLayout::chooserPosition[5] = {
    POINT{639, 134},
    POINT{639, 188},
    POINT{639, 242},
    POINT{639, 296},
    POINT{639, 377},
};

PauseLayout::PauseLayout() {}

PauseLayout::PauseLayout(Style style, std::string levelTitle, std::vector<std::string> rules) {
    this -> levelTitle = levelTitle;
    this -> rules = rules;

    chooser.LoadBitmapByString({ "./resources/pause/chooser1.bmp", "./resources/pause/chooser2.bmp", "./resources/pause/chooser3.bmp" }, 0x00FF00);
    chooser.SetAnimation(100, false);
    chooser.SetTopLeft(chooserPosition[chooserIndex].x, chooserPosition[chooserIndex].y);

    background.LoadBitmapByString({ "./resources/pause/" + styleToString[style] + "/background.bmp" }, 0x00FF00);
    for (int i = 0; i < 5; i++) {
        buttons[i].SetButtonTexture(
            buttonPosition[i],
            {
                "./resources/pause/" + styleToString[style] + "/button1.bmp",
                "./resources/pause/" + styleToString[style] + "/button2.bmp",
                "./resources/pause/" + styleToString[style] + "/button3.bmp",
            }
        );
        buttons[i].SetButtonText(buttonText[i]);
    }
}

void PauseLayout::SetActivity(bool activity) {
    for (Button &button : buttons) {
        button.SetActivity(activity);
    }
}

void PauseLayout::SetResumeButtonOnClickFunc(ButtonOnClickFunc func) {
    buttons[RESUME_BUTTON_INDEX].SetOnClickFunc(func);
}
void PauseLayout::SetReturnMapButtonOnClickFunc(ButtonOnClickFunc func) {
    buttons[RETURN_TO_MAP_BUTTON_INDEX].SetOnClickFunc(func);
}
void PauseLayout::SetRestartButtonOnClickFunc(ButtonOnClickFunc func) {
    buttons[RESTART_BUTTON_INDEX].SetOnClickFunc(func);
}
void PauseLayout::SetSettingButtonOnClickFunc(ButtonOnClickFunc func) {
    buttons[SETTING_BUTTON_INDEX].SetOnClickFunc(func);
}
void PauseLayout::SetReturnMenuButtonOnClickFunc(ButtonOnClickFunc func) {
    buttons[RETURN_TO_MENU_BUTTON_INDEX].SetOnClickFunc(func);
}


void PauseLayout::MouseMove(CPoint point) {
    for (Button &button : buttons) {
        button.CheckMouseMove(point);
    }
}
void PauseLayout::MouseClick(CPoint point) {
    for (Button &button : buttons) {
        button.CheckMouseClick(point);
    }
}

void PauseLayout::ChooserMoveUp() {
    if (--chooserIndex == -1) chooserIndex = 4;
    chooser.SetTopLeft(chooserPosition[chooserIndex].x, chooserPosition[chooserIndex].y);
}
void PauseLayout::ChooserMoveDown() {
    if (++chooserIndex == 5) chooserIndex = 0;
    chooser.SetTopLeft(chooserPosition[chooserIndex].x, chooserPosition[chooserIndex].y);
}
void PauseLayout::Choose() {
    buttons[chooserIndex].Click();
}

void PauseLayout::ShowImage() {
    background.ShowBitmap();
    chooser.ShowBitmap();
    for (Button &button : buttons) {
        button.ShowImage();
    }
}
void PauseLayout::ShowText(CDC *pDC) {
	game_framework::CTextDraw::ChangeFontLog(pDC, 34, "Darumadrop One", 0xFFFFFF);

    for (Button &button : buttons) {
        button.ShowText(pDC);
    }
    CenterTextDraw::Print(pDC, 960, 28, levelTitle);

    if (rules.size() != 0) {
        CenterTextDraw::Print(pDC, 960, 485, "RULES:");
    }
    if (rules.size() < 13) {
        showRulesOneLine(pDC);
    }
    else {
        showRulesTwoLine(pDC);
    }
}

void PauseLayout::showRulesOneLine(CDC *pDC) {
    for (size_t i = 0; i < rules.size(); i++) {
        CenterTextDraw::Print(pDC, 960, 528 + i * 43, rules[i]);
    }
}
void PauseLayout::showRulesTwoLine(CDC *pDC) {
    for (size_t i = 0; i < rules.size(); i++) {
        CenterTextDraw::Print(pDC, 652 + 616 * (i / 12), 528 + (i % 12) * 43, rules[i]);
    }
}