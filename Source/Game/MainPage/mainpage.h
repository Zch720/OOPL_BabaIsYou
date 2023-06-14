#pragma once
#include "../../Library/gameutil.h"
#include "../UI/button.h"

using namespace game_framework;
class MainPage {
private:
	CMovingBitmap standbyBackgroung;
	CMovingBitmap startScreenTitle;
	CMovingBitmap startScreenLine;
	CMovingBitmap chooser;
	Button continuePlaying;
	Button startTheGame;
	Button playLevel;
	Button levelEditor;
	Button settings;
	Button credits;
	Button exitTheGame;
	POINT chooserLocation[8] = { {615, 569}, {264, 677}, {264, 758}, {264, 839}, {615, 569},  {965, 677}, {965, 758}, {965, 839} };
	std::vector<CMovingBitmap> background = vector<CMovingBitmap>(9);
	CPoint chooserPoint;
	bool screenSwitch = false;

	bool showWarning = false;

public:
	void MainpageInit();
	void StandbyScreenInit();
	void StartScreenInit();
	void SwitchCheck();
	void ChooserMove(int direction);	// 0:up, 1:down, 2:left, 3:right
	void CheckMouseMove(CPoint point);
	void CheckMouseClick(CPoint point);
	void ChooserEnter();
	void SetContieuePlayingFunc(ButtonOnClickFunc func);
	void SetStartTheGameFunc(ButtonOnClickFunc func);
	void SetPlayLevelFunc(ButtonOnClickFunc func);
	void SetLevelEditorFunc(ButtonOnClickFunc func);
	void SetSettingsFunc(ButtonOnClickFunc func);
	void SetCreditsFunc(ButtonOnClickFunc func);
	void SetExitTheGameFunc(ButtonOnClickFunc func);
	void BackgroundOnMove();
	void ExitWarning();
	void ShowImage();
	void ShowText(CDC *pDC);
};