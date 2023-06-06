#pragma once

#include "../UI/button.h"
#include "../style.h"

class PauseLayout {
private:
    static const int RESUME_BUTTON_INDEX;
    static const int RETURN_TO_MAP_BUTTON_INDEX;
    static const int RESTART_BUTTON_INDEX;
    static const int SETTING_BUTTON_INDEX;
    static const int RETURN_TO_MENU_BUTTON_INDEX;
    static const POINT buttonPosition[5];
    static const std::string buttonText[5];
    static const POINT chooserPosition[5];

    game_framework::CMovingBitmap background;
    std::string levelTitle = "";
    Button buttons[5];
    std::vector<std::string> rules = {};

	game_framework::CMovingBitmap chooser;
    int chooserIndex = 0;

    void showRulesOneLine(CDC *pDC);
    void showRulesTwoLine(CDC *pDC);

public:
    PauseLayout();
    PauseLayout(Style style, std::string levelTitle, std::vector<std::string> rules);

    void SetActivity(bool activity);

    void SetResumeButtonOnClickFunc(ButtonOnClickFunc func);
    void SetReturnMapButtonOnClickFunc(ButtonOnClickFunc func);
    void SetRestartButtonOnClickFunc(ButtonOnClickFunc func);
    void SetSettingButtonOnClickFunc(ButtonOnClickFunc func);
    void SetReturnMenuButtonOnClickFunc(ButtonOnClickFunc func);

    void MouseMove(CPoint point);
    void MouseClick(CPoint point);

    void ChooserMoveUp();
    void ChooserMoveDown();
    void Choose();

    void ShowImage();
    void ShowText(CDC *pDC);
};