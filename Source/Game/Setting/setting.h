#pragma once
#include "../../Library/gameutil.h"
#include "../UI/button.h"
#include "../style.h"

#define languageSetup 0
#define controls 1
#define toggleFullscreen 2
#define enableGrid 3
#define disableWobbleEffect 4
#define disableParticalEffect 5
#define disableScreenshack 6
#define forceHighcontrastColours 7
#define preventBlingkingColours 8
#define doNotPromptOnRestart 9
#define None 10
#define deFault 11
#define stretch 12
#define Back 13

class ObjectButton : public Button {
public:
	ObjectButton();
	ObjectButton(Button button);
	bool objectButtonDo;
};

using namespace game_framework;
class Setting {
private:
	CMovingBitmap worldDefault;
	CMovingBitmap worldDo;
	CMovingBitmap worldDefaultShort;
	CMovingBitmap worldDoShort;
	CMovingBitmap chooser;
	CMovingBitmap bar0;
	CMovingBitmap bar1;
	CMovingBitmap bar2;
	CMovingBitmap barPoint;
	Button english;
	Button backToSetting;
	std::vector<ObjectButton> buttonVector = vector<ObjectButton>(14);
	std::vector<CMovingBitmap> barPointVector = vector<CMovingBitmap>(3);
	std::vector<int> chooser_x = vector<int>(5);
	std::vector<int> chooser_y = vector<int>(15);
	int chooserPoint_x;
	int chooserPoint_y;
	int languageChooserPosition = 0;
	int whichPointClick = -1;
	int where = 0;	//0: setting, 1: language setup
	void SetChooserx(int chooserWhere_y);
	void LoadButton();
	void SwitchButtonDo(int switchingButton, bool objectButtonDo);
	void SwitchButtonShortDo(int switchingButton);
	void SetSettingActive();
	void SetSettingUnActive();
	void SetLanguageActive();
	void SetLanguageUnActive();

public:
	void Load();
	void Save();

	void CheckMouseMove(CPoint point);
	void CheckMouseClick(CPoint point);
	void ShowImage();
	void ShowText(CDC *pDC);
	void SetButtonWorld(Style style);

	void ChooserMoveUp();
	void ChooserMoveDown();
	void ChooserMoveLeft();
	void ChooserMoveRight();
	void ChooserClick();

	void MouseDown(POINT point);
	void MouseUp();
	void MouseMove(POINT point);

	bool GetMusic();
	bool GetSound();
	int GetDelay();

	void SetLanguageSetupFunc(ButtonOnClickFunc func);
	void SetControlsFunc(ButtonOnClickFunc func);
	void SetToggleFullscreenFunc(ButtonOnClickFunc func);
	void SetEnableGridFunc(ButtonOnClickFunc func);
	void SetDisableWobbleEffectFunc(ButtonOnClickFunc func);
	void SetDisableParticalEffectFunc(ButtonOnClickFunc func);
	void SetDisableScreenshackFunc(ButtonOnClickFunc func);
	void SetForceHighcontrastColoursFunc(ButtonOnClickFunc func);
	void SetPreventBlingkingColoursFunc(ButtonOnClickFunc func);
	void SetDoNotPromptOnRestartFunc(ButtonOnClickFunc func);
	void SetNoneFunc(ButtonOnClickFunc func);
	void SetDefaultFunc(ButtonOnClickFunc func);
	void SetStretchFunc(ButtonOnClickFunc func);
	void SetBackFunc(ButtonOnClickFunc func);
	void SetBackToSettingFunc(ButtonOnClickFunc func);
};