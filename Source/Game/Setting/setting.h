#pragma once
#include "../../Library/gameutil.h"
#include "../UI/button.h"

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
	ObjectButton(Button button);
	bool objectButtonDo = false;
};

using namespace game_framework;
class Setting {
private:
	int settingWorld;
	Button worldDefault;
	Button world0Default;
	Button world1Default;
	Button world2Default;
	Button world3Default;
	Button world4Default;
	Button worldDo;
	Button world0Do;
	Button world1Do;
	Button world2Do;
	Button world3Do;
	Button world4Do;
	std::vector<ObjectButton> buttonVector = vector<ObjectButton>(14);
	void LoadButton();
	void SwitchButtonDo(int switchingButton, bool objectButtonDo);

public:
	void SettingInit();
	void CheckMouseMove(CPoint point);
	void CheckMouseClick(CPoint point);
	void ShowImage();
	void ShowText(CDC *pDC);
	void SetButtonWorld(int world);
	void SetLanguageSetupFunc();
};