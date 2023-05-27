#include "stdafx.h"
#include "setting.h"

ObjectButton::ObjectButton(Button button) : Button(button) {}


void Setting::SettingInit() {
	world0Default.SetButtonTexture(CPoint(500, 500), { "Resources/setting/0_button_long_1.bmp", "Resources/setting/0_button_long_2.bmp" , "Resources/setting/0_button_long_3.bmp" });
	world1Default.SetButtonTexture(CPoint(500, 500), { "Resources/setting/1_button_long_1.bmp", "Resources/setting/1_button_long_2.bmp" , "Resources/setting/1_button_long_3.bmp" });
	world2Default.SetButtonTexture(CPoint(500, 500), { "Resources/setting/2_button_long_1.bmp", "Resources/setting/2_button_long_2.bmp" , "Resources/setting/2_button_long_3.bmp" });
	world3Default.SetButtonTexture(CPoint(500, 500), { "Resources/setting/3_button_long_1.bmp", "Resources/setting/3_button_long_2.bmp" , "Resources/setting/3_button_long_3.bmp" });
	world4Default.SetButtonTexture(CPoint(500, 500), { "Resources/setting/4_button_long_1.bmp", "Resources/setting/4_button_long_2.bmp" , "Resources/setting/4_button_long_3.bmp" });
	world0Do.SetButtonTexture(CPoint(500, 500), { "Resources/setting/0_do_button_long_1.bmp", "Resources/setting/0_do_button_long_2.bmp" , "Resources/setting/0_do_button_long_3.bmp" });
	for (int i = 0; i < 14; i++) {
		buttonVector.push_back(world0Default);
	}
}

void Setting::SetButtonWorld(int world) {
	settingWorld = world;
	if (world == 1000) { worldDefault = world0Default; worldDo = world0Do; }
	else if (world == 1001) { worldDefault = world1Default; }
	else if (world == 1002) { worldDefault = world2Default; }
	else if (world == 1003) { worldDefault = world3Default; }
	else if (world == 1004) { worldDefault = world4Default; }
	LoadButton();
}

void Setting::LoadButton() {
	buttonVector[languageSetup] = worldDefault;
	buttonVector[languageSetup].SetButtonTexture(CPoint(800, 700), {});
	buttonVector[languageSetup].SetButtonText("LANGUAGE SETUP");
	buttonVector[languageSetup].SetActivity(true);
	buttonVector[controls] = worldDefault;
	buttonVector[controls].SetButtonTexture(CPoint(800, 800), {});
	buttonVector[controls].SetButtonText("CONTROLS");
	buttonVector[controls].SetActivity(true);
}

void Setting::CheckMouseMove(CPoint point) {
	buttonVector[languageSetup].CheckMouseMove(point);
	buttonVector[controls].CheckMouseMove(point);
}

void Setting::CheckMouseClick(CPoint point) {
	buttonVector[languageSetup].CheckMouseClick(point);
	buttonVector[controls].CheckMouseClick(point);
}

void Setting::SwitchButtonDo(int switchingButton,bool objectButtonDo) {
	if (objectButtonDo == false) {
		objectButtonDo = true;
		buttonVector[switchingButton] = worldDo;
	}
	else {
		objectButtonDo = false;
		buttonVector[switchingButton] = worldDefault;
	}
}

void Setting::SetLanguageSetupFunc() {
	buttonVector[languageSetup].SetOnClickFunc([this]() { SwitchButtonDo(languageSetup, buttonVector[languageSetup].objectButtonDo); });
}

void Setting::ShowImage() {
	buttonVector[languageSetup].ShowImage();
	buttonVector[controls].ShowImage();
}

void Setting::ShowText(CDC *pDC) {
	buttonVector[languageSetup].ShowText(pDC);
	buttonVector[controls].ShowText(pDC);
}
