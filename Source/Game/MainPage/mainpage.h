#pragma once
#include "../../Library/gameutil.h"
#include "../UI/button.h"

using namespace game_framework;
class MainPage {
private:
	static CMovingBitmap standbyBackgroung;
	static CMovingBitmap startScreenTitle;
	static CMovingBitmap startScreenLine;
	static CMovingBitmap chooser;
	static Button continuePlaying;
	static Button startTheGame;
	static Button playLevel;
	static Button levelEditor;
	static Button settings;
	static Button credits;
	static Button exitTheGame;
	static POINT chooserLocation[8];
	static CPoint chooserPoint;
	static bool screenSwitch;

public:
	static void StandbyScreenInit();
	static void StartScreenInit();
	static void SwitchCheck();
	static void ChooserMove(int direction);	// 0:up, 1:down, 2:left, 3:right
	static void CheckMouseMove(CPoint point);
	static void CheckMouseClick(CPoint point);
	static void ChooserEnter();
	static void SetContieuePlayingFunc(ButtonOnClickFunc func);
	static void SetStartTheGameFunc(ButtonOnClickFunc func);
	static void SetExitTheGameFunc(ButtonOnClickFunc func);
	static void ShowImage();
	static void ShowText(CDC *pDC);
};