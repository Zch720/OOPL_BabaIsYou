#include "stdafx.h"
#include "setting.h"
#include "../../Expansion/dataio.h"
#include "../../Expansion/string_proc.h"
#include "../../Expansion/center_text.h"

ObjectButton::ObjectButton() {}
ObjectButton::ObjectButton(Button button) : Button(button) {}


void Setting::Load() {
	std::string setting = loadFile("setting.txt");
	if  (setting == "") return;
	if (setting.find("\r") != std::string::npos)
		setting = setting.replace(setting.find("\r"), 1, "");
	if (setting.find("\n") != std::string::npos)
		setting = setting.replace(setting.find("\n"), 1, "");

	std::vector<std::string> settingValues = stringSplit(setting, '|');

	barPointVector[0].SetTopLeft(1155 + stringToInt(settingValues[0]), 167);
	barPointVector[1].SetTopLeft(1155 + stringToInt(settingValues[1]), 221);
	barPointVector[2].SetTopLeft(1155 + stringToInt(settingValues[2]), 275);

	if (settingValues[3] != "0") SwitchButtonDo(languageSetup, false);
	if (settingValues[4] != "0") SwitchButtonDo(controls, false);
	if (settingValues[5] != "0") SwitchButtonDo(toggleFullscreen, false);
	if (settingValues[6] != "0") SwitchButtonDo(enableGrid, false);
	if (settingValues[7] != "0") SwitchButtonDo(disableWobbleEffect, false);
	if (settingValues[8] != "0") SwitchButtonDo(disableParticalEffect, false);
	if (settingValues[9] != "0") SwitchButtonDo(disableScreenshack, false);
	if (settingValues[10] != "0") SwitchButtonDo(forceHighcontrastColours, false);
	if (settingValues[11] != "0") SwitchButtonDo(preventBlingkingColours, false);
	if (settingValues[12] != "0") SwitchButtonDo(doNotPromptOnRestart, false);
	if (settingValues[13] != "0") SwitchButtonShortDo(None);
	if (settingValues[14] != "0") SwitchButtonShortDo(deFault);
	if (settingValues[15] != "0") SwitchButtonShortDo(stretch);
}

void Setting::Save() {
	std::string data = "";
	data += std::to_string(barPointVector[0].GetLeft() - 1155) + "|";
	data += std::to_string(barPointVector[1].GetLeft() - 1155) + "|";
	data += std::to_string(barPointVector[2].GetLeft() - 1155) + "|";
	data += std::to_string(buttonVector[languageSetup].objectButtonDo) + "|";
	data += std::to_string(buttonVector[controls].objectButtonDo) + "|";
	data += std::to_string(buttonVector[toggleFullscreen].objectButtonDo) + "|";
	data += std::to_string(buttonVector[enableGrid].objectButtonDo) + "|";
	data += std::to_string(buttonVector[disableWobbleEffect].objectButtonDo) + "|";
	data += std::to_string(buttonVector[disableParticalEffect].objectButtonDo) + "|";
	data += std::to_string(buttonVector[disableScreenshack].objectButtonDo) + "|";
	data += std::to_string(buttonVector[forceHighcontrastColours].objectButtonDo) + "|";
	data += std::to_string(buttonVector[preventBlingkingColours].objectButtonDo) + "|";
	data += std::to_string(buttonVector[doNotPromptOnRestart].objectButtonDo) + "|";
	data += std::to_string(buttonVector[None].objectButtonDo) + "|";
	data += std::to_string(buttonVector[deFault].objectButtonDo) + "|";
	data += std::to_string(buttonVector[stretch].objectButtonDo);

	saveFile("setting.txt", data);
}

void Setting::SetButtonWorld(Style style) {

	chooser_x = { 250, 428, 482, 913, 1345 };
	chooser_y = { 180, 228, 276, 381, 435, 489, 543, 597, 651, 705, 759, 813, 867, 922, 977 };
	chooserPoint_x = 0;
	chooserPoint_y = 0;
	chooser.LoadBitmapByString({"Resources/setting/chooser1.bmp", "Resources/setting/chooser2.bmp", "Resources/setting/chooser3.bmp"}, 0x00FF00);
	chooser.SetTopLeft(chooser_x[chooserPoint_x], chooser_y[chooserPoint_y]);
	chooser.SetAnimation(250, false);
	if (style == STYLE_DEFAULT) {
		worldDefault.LoadBitmapByString({ "Resources/setting/0_button_long_1.bmp", "Resources/setting/0_button_long_2.bmp" , "Resources/setting/0_button_long_3.bmp" }, 0x00FF00);
		worldDo.LoadBitmapByString({ "Resources/setting/0_do_button_long_1.bmp", "Resources/setting/0_do_button_long_2.bmp" , "Resources/setting/0_do_button_long_3.bmp" }, 0x00FF00);
		worldDefaultShort.LoadBitmapByString({ "Resources/setting/0_button_short_1.bmp", "Resources/setting/0_button_short_2.bmp" , "Resources/setting/0_button_short_3.bmp" }, 0x00FF00);
		worldDoShort.LoadBitmapByString({ "Resources/setting/0_do_button_short_1.bmp", "Resources/setting/0_do_button_short_2.bmp" , "Resources/setting/0_do_button_short_3.bmp" }, 0x00FF00);
		bar0.LoadBitmapByString({"Resources/setting/0_bar.bmp"});
		barPoint.LoadBitmapByString({"Resources/setting/0_bar_point_1.bmp", "Resources/setting/0_bar_point_2.bmp", "Resources/setting/0_bar_point_3.bmp"}, 0x00FF00);
	}
	else if (style == STYLE_LAKE) {
		worldDefault.LoadBitmapByString({ "Resources/setting/1_button_long_1.bmp", "Resources/setting/1_button_long_2.bmp" , "Resources/setting/1_button_long_3.bmp" }, 0x00FF00);
		worldDo.LoadBitmapByString({ "Resources/setting/1_do_button_long_1.bmp", "Resources/setting/1_do_button_long_2.bmp" , "Resources/setting/1_do_button_long_3.bmp" }, 0x00FF00);
		worldDefaultShort.LoadBitmapByString({ "Resources/setting/1_button_short_1.bmp", "Resources/setting/1_button_short_2.bmp" , "Resources/setting/1_button_short_3.bmp" }, 0x00FF00);
		worldDoShort.LoadBitmapByString({ "Resources/setting/1_do_button_short_1.bmp", "Resources/setting/1_do_button_short_2.bmp" , "Resources/setting/1_do_button_short_3.bmp" }, 0x00FF00);
		bar0.LoadBitmapByString({ "Resources/setting/1_bar.bmp" });
		barPoint.LoadBitmapByString({ "Resources/setting/1_bar_point_1.bmp", "Resources/setting/1_bar_point_2.bmp", "Resources/setting/1_bar_point_3.bmp" }, 0x00FF00);
	}
	else if (style == STYLE_ISLAND) {
		worldDefault.LoadBitmapByString({ "Resources/setting/2_button_long_1.bmp", "Resources/setting/2_button_long_2.bmp" , "Resources/setting/2_button_long_3.bmp" }, 0x00FF00);
		worldDo.LoadBitmapByString({ "Resources/setting/2_do_button_long_1.bmp", "Resources/setting/2_do_button_long_2.bmp" , "Resources/setting/2_do_button_long_3.bmp" }, 0x00FF00);
		worldDefaultShort.LoadBitmapByString({ "Resources/setting/2_button_short_1.bmp", "Resources/setting/2_button_short_2.bmp" , "Resources/setting/2_button_short_3.bmp" }, 0x00FF00);
		worldDoShort.LoadBitmapByString({ "Resources/setting/2_do_button_short_1.bmp", "Resources/setting/2_do_button_short_2.bmp" , "Resources/setting/2_do_button_short_3.bmp" }, 0x00FF00);
		bar0.LoadBitmapByString({ "Resources/setting/2_bar.bmp" });
		barPoint.LoadBitmapByString({ "Resources/setting/2_bar_point_1.bmp", "Resources/setting/2_bar_point_2.bmp", "Resources/setting/2_bar_point_3.bmp" }, 0x00FF00);
	}
	else if (style == STYLE_RUIN) {
		worldDefault.LoadBitmapByString({ "Resources/setting/3_button_long_1.bmp", "Resources/setting/3_button_long_2.bmp" , "Resources/setting/3_button_long_3.bmp" }, 0x00FF00);
		worldDo.LoadBitmapByString({ "Resources/setting/3_do_button_long_1.bmp", "Resources/setting/3_do_button_long_2.bmp" , "Resources/setting/3_do_button_long_3.bmp" }, 0x00FF00);
		worldDefaultShort.LoadBitmapByString({ "Resources/setting/3_button_short_1.bmp", "Resources/setting/3_button_short_2.bmp" , "Resources/setting/3_button_short_3.bmp" }, 0x00FF00);
		worldDoShort.LoadBitmapByString({ "Resources/setting/3_do_button_short_1.bmp", "Resources/setting/3_do_button_short_2.bmp" , "Resources/setting/3_do_button_short_3.bmp" }, 0x00FF00);
		bar0.LoadBitmapByString({ "Resources/setting/3_bar.bmp" });
		barPoint.LoadBitmapByString({ "Resources/setting/3_bar_point_1.bmp", "Resources/setting/3_bar_point_2.bmp", "Resources/setting/3_bar_point_3.bmp" }, 0x00FF00);
	}
	else if (style == STYLE_NONE) {
		worldDefault.LoadBitmapByString({ "Resources/setting/4_button_long_1.bmp", "Resources/setting/4_button_long_2.bmp" , "Resources/setting/4_button_long_3.bmp" }, 0x00FF00);
		worldDo.LoadBitmapByString({ "Resources/setting/4_do_button_long_1.bmp", "Resources/setting/4_do_button_long_2.bmp" , "Resources/setting/4_do_button_long_3.bmp" }, 0x00FF00);
		worldDefaultShort.LoadBitmapByString({ "Resources/setting/4_button_short_1.bmp", "Resources/setting/4_button_short_2.bmp" , "Resources/setting/4_button_short_3.bmp" }, 0x00FF00);
		worldDoShort.LoadBitmapByString({ "Resources/setting/4_do_button_short_1.bmp", "Resources/setting/4_do_button_short_2.bmp" , "Resources/setting/4_do_button_short_3.bmp" }, 0x00FF00);
		bar0.LoadBitmapByString({ "Resources/setting/4_bar.bmp" });
		barPoint.LoadBitmapByString({ "Resources/setting/4_bar_point_1.bmp", "Resources/setting/4_bar_point_2.bmp", "Resources/setting/4_bar_point_3.bmp" }, 0x00FF00);
	}
	LoadButton();
}

void Setting::LoadButton() {
	bar0.SetTopLeft(1176, 184);
	barPointVector[0] = barPoint;
	barPointVector[0].SetTopLeft(1155, 167);
	bar1 = bar0;
	bar1.SetTopLeft(1176, 238);
	barPointVector[1] = barPoint;
	barPointVector[1].SetTopLeft(1155, 221);
	bar2 = bar0;
	bar2.SetTopLeft(1176, 292);
	barPointVector[2] = barPoint;
	barPointVector[2].SetTopLeft(1155, 275);
	buttonVector[languageSetup].SetButtonTexture(worldDefault);
	buttonVector[languageSetup].SetButtonCenterPosition(CPoint(960, 405));
	buttonVector[languageSetup].SetButtonText("LANGUAGE SETUP");
	buttonVector[languageSetup].objectButtonDo = false;
	
	SetLanguageSetupFunc([]() {});
	buttonVector[controls].SetButtonTexture(worldDefault);
	buttonVector[controls].SetButtonCenterPosition(CPoint(960, 459));
	buttonVector[controls].SetButtonText("CONTROLS");
	buttonVector[controls].objectButtonDo = false;

	SetControlsFunc([]() {});
	buttonVector[toggleFullscreen].SetButtonTexture(worldDefault);
	buttonVector[toggleFullscreen].SetButtonCenterPosition(CPoint(960, 513));
	buttonVector[toggleFullscreen].SetButtonText("TOGGLE FULL SCREEN");
	buttonVector[toggleFullscreen].objectButtonDo = false;

	SetToggleFullscreenFunc([]() {});
	buttonVector[enableGrid].SetButtonTexture(worldDefault);
	buttonVector[enableGrid].SetButtonCenterPosition(CPoint(960, 567));
	buttonVector[enableGrid].SetButtonText("ENABLE GRID");
	buttonVector[enableGrid].objectButtonDo = false;

	SetEnableGridFunc([]() {});
	buttonVector[disableWobbleEffect].SetButtonTexture(worldDefault);
	buttonVector[disableWobbleEffect].SetButtonCenterPosition(CPoint(960, 621));
	buttonVector[disableWobbleEffect].SetButtonText("DISABLE WOBBLE EFFECT");
	buttonVector[disableWobbleEffect].objectButtonDo = false;

	SetDisableWobbleEffectFunc([]() {});
	buttonVector[disableParticalEffect].SetButtonTexture(worldDefault);
	buttonVector[disableParticalEffect].SetButtonCenterPosition(CPoint(960, 675));
	buttonVector[disableParticalEffect].SetButtonText("DISABLE PARTICAL EFFECT");
	buttonVector[disableParticalEffect].objectButtonDo = false;

	SetDisableParticalEffectFunc([]() {});
	buttonVector[disableScreenshack].SetButtonTexture(worldDefault);
	buttonVector[disableScreenshack].SetButtonCenterPosition(CPoint(960, 729));
	buttonVector[disableScreenshack].SetButtonText("DISABLE SCREENSHACK");
	buttonVector[disableScreenshack].objectButtonDo = false;

	SetDisableScreenshackFunc([]() {});
	buttonVector[forceHighcontrastColours].SetButtonTexture(worldDefault);
	buttonVector[forceHighcontrastColours].SetButtonCenterPosition(CPoint(960, 783));
	buttonVector[forceHighcontrastColours].SetButtonText("FORCE HIGH-CONTRAST COLOURS");
	buttonVector[forceHighcontrastColours].objectButtonDo = false;

	SetForceHighcontrastColoursFunc([]() {});
	buttonVector[preventBlingkingColours].SetButtonTexture(worldDefault);
	buttonVector[preventBlingkingColours].SetButtonCenterPosition(CPoint(960, 837));
	buttonVector[preventBlingkingColours].SetButtonText("PREVENT BLINGKING COLOURS");
	buttonVector[preventBlingkingColours].objectButtonDo = false;

	SetPreventBlingkingColoursFunc([]() {});
	buttonVector[doNotPromptOnRestart].SetButtonTexture(worldDefault);
	buttonVector[doNotPromptOnRestart].SetButtonCenterPosition(CPoint(960, 891));
	buttonVector[doNotPromptOnRestart].SetButtonText("DO NOT PROMPT ON RESTART");
	buttonVector[doNotPromptOnRestart].objectButtonDo = false;

	SetDoNotPromptOnRestartFunc([]() {});
	buttonVector[None].SetButtonTexture(worldDefaultShort);
	buttonVector[None].SetButtonCenterPosition(CPoint(717, 946));
	buttonVector[None].SetButtonText("NONE");
	buttonVector[None].objectButtonDo = false;

	SetNoneFunc([]() {});
	buttonVector[deFault].SetButtonTexture(worldDoShort);
	buttonVector[deFault].SetButtonCenterPosition(CPoint(1148, 946));
	buttonVector[deFault].SetButtonText("DEFAULT");
	buttonVector[deFault].objectButtonDo = true;
	SetDefaultFunc([]() {});

	buttonVector[stretch].SetButtonTexture(worldDefaultShort);
	buttonVector[stretch].SetButtonCenterPosition(CPoint(1580, 946));
	buttonVector[stretch].SetButtonText("STRETCH");
	buttonVector[stretch].objectButtonDo = false;
	buttonVector[stretch].SetActivity(true);
	SetStretchFunc([]() {});
	buttonVector[Back].SetButtonTexture(worldDefault);
	buttonVector[Back].SetButtonCenterPosition(CPoint(960, 1001));
	buttonVector[Back].SetButtonText("RETURN");
	buttonVector[Back].objectButtonDo = false;
	SetSettingActive();
	SetBackFunc([]() {});
	english.SetButtonTexture(worldDefault);
	english.SetButtonCenterPosition(CPoint(960, 200));
	english.SetButtonText("ENGLISH");
	backToSetting.SetButtonTexture(worldDefault);
	backToSetting.SetButtonCenterPosition(CPoint(960, 900));
	backToSetting.SetButtonText("RETURN");
	SetBackToSettingFunc([]() {});
}

void Setting::CheckMouseMove(CPoint point) {
	buttonVector[languageSetup].CheckMouseMove(point);
	buttonVector[controls].CheckMouseMove(point);
	buttonVector[toggleFullscreen].CheckMouseMove(point);
	buttonVector[enableGrid].CheckMouseMove(point);
	buttonVector[disableWobbleEffect].CheckMouseMove(point);
	buttonVector[disableParticalEffect].CheckMouseMove(point);
	buttonVector[disableScreenshack].CheckMouseMove(point);
	buttonVector[forceHighcontrastColours].CheckMouseMove(point);
	buttonVector[preventBlingkingColours].CheckMouseMove(point);
	buttonVector[doNotPromptOnRestart].CheckMouseMove(point);
	buttonVector[None].CheckMouseMove(point);
	buttonVector[deFault].CheckMouseMove(point);
	buttonVector[stretch].CheckMouseMove(point);
	buttonVector[Back].CheckMouseMove(point);
	english.CheckMouseMove(point);
	backToSetting.CheckMouseMove(point);
}

void Setting::CheckMouseClick(CPoint point) {
	buttonVector[languageSetup].CheckMouseClick(point);
	buttonVector[controls].CheckMouseClick(point);
	buttonVector[toggleFullscreen].CheckMouseClick(point);
	buttonVector[enableGrid].CheckMouseClick(point);
	buttonVector[disableWobbleEffect].CheckMouseClick(point);
	buttonVector[disableParticalEffect].CheckMouseClick(point);
	buttonVector[disableScreenshack].CheckMouseClick(point);
	buttonVector[forceHighcontrastColours].CheckMouseClick(point);
	buttonVector[preventBlingkingColours].CheckMouseClick(point);
	buttonVector[doNotPromptOnRestart].CheckMouseClick(point);
	buttonVector[None].CheckMouseClick(point);
	buttonVector[deFault].CheckMouseClick(point);
	buttonVector[stretch].CheckMouseClick(point);
	buttonVector[Back].CheckMouseClick(point);
	english.CheckMouseClick(point);
	backToSetting.CheckMouseClick(point);
}

void Setting::SwitchButtonDo(int switchingButton,bool objectButtonDo) {
	if (objectButtonDo == false) {
		buttonVector[switchingButton].objectButtonDo = true;
		buttonVector[switchingButton].SetButtonTexture(worldDo);
	}
	else {
		buttonVector[switchingButton].objectButtonDo = false;
		buttonVector[switchingButton].SetButtonTexture(worldDefault);
	}
}

void Setting::SwitchButtonShortDo(int switchingButton) {
	if (switchingButton == None) {
		buttonVector[None].objectButtonDo = true;
		buttonVector[None].SetButtonTexture(worldDoShort);
		buttonVector[deFault].objectButtonDo = false;
		buttonVector[deFault].SetButtonTexture(worldDefaultShort);
		buttonVector[stretch].objectButtonDo = false;
		buttonVector[stretch].SetButtonTexture(worldDefaultShort);
	}
	else if(switchingButton == deFault){
		buttonVector[None].objectButtonDo = false;
		buttonVector[None].SetButtonTexture(worldDefaultShort);
		buttonVector[deFault].objectButtonDo = true;
		buttonVector[deFault].SetButtonTexture(worldDoShort);
		buttonVector[stretch].objectButtonDo = false;
		buttonVector[stretch].SetButtonTexture(worldDefaultShort);
	}
	else {
		buttonVector[None].objectButtonDo = false;
		buttonVector[None].SetButtonTexture(worldDefaultShort);
		buttonVector[deFault].objectButtonDo = false;
		buttonVector[deFault].SetButtonTexture(worldDefaultShort);
		buttonVector[stretch].objectButtonDo = true;
		buttonVector[stretch].SetButtonTexture(worldDoShort);
	}
}

bool Setting::GetMusic() {
	return barPointVector[0].GetLeft() != 1155;
}

bool Setting::GetSound() {
	return barPointVector[1].GetLeft() != 1155;
}

int Setting::GetDelay() {
	return (barPointVector[2].GetLeft() - 1155) / 40;
}

void Setting::SetLanguageSetupFunc(ButtonOnClickFunc func) {
	buttonVector[languageSetup].SetOnClickFunc([this, func]() {
		where = 1;
		languageChooserPosition = 0;
		chooser.SetTopLeft(428, 176);
		SetLanguageActive();
		SetSettingUnActive();
		func();
	});
}

void Setting::SetControlsFunc(ButtonOnClickFunc func) {
	buttonVector[controls].SetOnClickFunc(func);
}

void Setting::SetToggleFullscreenFunc(ButtonOnClickFunc func) {
	buttonVector[toggleFullscreen].SetOnClickFunc([this, func]() {
		SwitchButtonDo(toggleFullscreen, buttonVector[toggleFullscreen].objectButtonDo);
		func();
	});
}

void Setting::SetEnableGridFunc(ButtonOnClickFunc func) {
	buttonVector[enableGrid].SetOnClickFunc([this, func]() {
		SwitchButtonDo(enableGrid, buttonVector[enableGrid].objectButtonDo);
		func();
	});
}

void Setting::SetDisableWobbleEffectFunc(ButtonOnClickFunc func) {
	buttonVector[disableWobbleEffect].SetOnClickFunc([this, func]() {
		SwitchButtonDo(disableWobbleEffect, buttonVector[disableWobbleEffect].objectButtonDo);
		func();
	});
}

void Setting::SetDisableParticalEffectFunc(ButtonOnClickFunc func) {
	buttonVector[disableParticalEffect].SetOnClickFunc([this, func]() {
		SwitchButtonDo(disableParticalEffect, buttonVector[disableParticalEffect].objectButtonDo);
		func();
	});
}

void Setting::SetDisableScreenshackFunc(ButtonOnClickFunc func) {
	buttonVector[disableScreenshack].SetOnClickFunc([this, func]() {
		SwitchButtonDo(disableScreenshack, buttonVector[disableScreenshack].objectButtonDo);
		func();
	});
}

void Setting::SetForceHighcontrastColoursFunc(ButtonOnClickFunc func) {
	buttonVector[forceHighcontrastColours].SetOnClickFunc([this, func]() {
		SwitchButtonDo(forceHighcontrastColours, buttonVector[forceHighcontrastColours].objectButtonDo);
		func();
	});
}

void Setting::SetPreventBlingkingColoursFunc(ButtonOnClickFunc func) {
	buttonVector[preventBlingkingColours].SetOnClickFunc([this, func]() {
		SwitchButtonDo(preventBlingkingColours, buttonVector[preventBlingkingColours].objectButtonDo);
		func();
	});
}

void Setting::SetDoNotPromptOnRestartFunc(ButtonOnClickFunc func) {
	buttonVector[doNotPromptOnRestart].SetOnClickFunc([this, func]() {
		SwitchButtonDo(doNotPromptOnRestart, buttonVector[doNotPromptOnRestart].objectButtonDo);
		func();
	});
}

void Setting::SetNoneFunc(ButtonOnClickFunc func) {
	buttonVector[None].SetOnClickFunc([this, func]() {
		SwitchButtonShortDo(None);
		func();
	});
}

void Setting::SetDefaultFunc(ButtonOnClickFunc func) {
	buttonVector[deFault].SetOnClickFunc([this, func]() {
		SwitchButtonShortDo(deFault);
		func();
	});
}

void Setting::SetStretchFunc(ButtonOnClickFunc func) {
	buttonVector[stretch].SetOnClickFunc([this, func]() {
		SwitchButtonShortDo(stretch);
		func();
	});
}

void Setting::SetBackFunc(ButtonOnClickFunc func) {
	buttonVector[Back].SetOnClickFunc(func);
}

void Setting::SetBackToSettingFunc(ButtonOnClickFunc func) {
	backToSetting.SetOnClickFunc([this, func]() {
		where = 0;
		chooserPoint_x = 1;
		chooserPoint_y = 3;
		chooser.SetTopLeft(chooser_x[chooserPoint_x], chooser_y[chooserPoint_y]);
		SetSettingActive();
		SetLanguageUnActive();
		func();
	});
}

void Setting::SetChooserx(int chooserWhere_y) {
	if (chooserWhere_y < 3) {
		chooserPoint_x = 0;
	}
	else if (chooserWhere_y == 13) {
		if (buttonVector[None].objectButtonDo == true) {
			chooserPoint_x = 2;
		}
		else if (buttonVector[deFault].objectButtonDo == true) {
			chooserPoint_x = 3;
		}
		else {
			chooserPoint_x = 4;
		}
	}
	else {
		chooserPoint_x = 1;
	}
}

void Setting::ChooserMoveUp() {
	if (where == 0) {
		if (chooserPoint_y == 0) {
			chooserPoint_y = 14;
		}
		else {
			chooserPoint_y -= 1;
		}
		SetChooserx(chooserPoint_y);
		chooser.SetTopLeft(chooser_x[chooserPoint_x], chooser_y[chooserPoint_y]);
	}
	else {
		if (languageChooserPosition == 0) {
			languageChooserPosition = 1;
			chooser.SetTopLeft(428, 876);
		}
		else {
			languageChooserPosition = 0;
			chooser.SetTopLeft(428, 176);

		}
	}
}

void Setting::ChooserMoveDown() {
	if (where == 0) {
		if (chooserPoint_y == 14) {
			chooserPoint_y = 0;
		}
		else {
			chooserPoint_y += 1;
		}
		SetChooserx(chooserPoint_y);
		chooser.SetTopLeft(chooser_x[chooserPoint_x], chooser_y[chooserPoint_y]);
	}
	else {
		if (languageChooserPosition == 1) {
			languageChooserPosition = 0;
			chooser.SetTopLeft(428, 176);
		}
		else {
			languageChooserPosition = 1;
			chooser.SetTopLeft(428, 876);
		}
	}
}

void Setting::ChooserMoveLeft() {
	if (where == 0) {
		if (chooserPoint_y == 13) {
			if (chooserPoint_x == 2) {
				chooserPoint_x = 4;
			}
			else {
				chooserPoint_x -= 1;
			}
		}
		else if (chooserPoint_y < 2) {
			int x = barPointVector[chooserPoint_y].GetLeft();
			int y = barPointVector[chooserPoint_y].GetTop();
			if (x > 1155) {
				barPointVector[chooserPoint_y].SetTopLeft(x - 2, y);
			}
		}
		else if (chooserPoint_y == 2) {
			int x = barPointVector[chooserPoint_y].GetLeft();
			int y = barPointVector[chooserPoint_y].GetTop();
			if (x > 1155) {
				barPointVector[chooserPoint_y].SetTopLeft(x - 40, y);
			}
		}
		chooser.SetTopLeft(chooser_x[chooserPoint_x], chooser_y[chooserPoint_y]);
	}
	else {}
}

void Setting::ChooserMoveRight() {
	if (where == 0) {
		if (chooserPoint_y == 13) {
			if (chooserPoint_x == 4) {
				chooserPoint_x = 2;
			}
			else {
				chooserPoint_x += 1;
			}
		}
		else if (chooserPoint_y < 2) {
			int x = barPointVector[chooserPoint_y].GetLeft();
			int y = barPointVector[chooserPoint_y].GetTop();
			if (x < 1595) {
				barPointVector[chooserPoint_y].SetTopLeft(x + 2, y);
			}
		}
		else if (chooserPoint_y == 2) {
			int x = barPointVector[chooserPoint_y].GetLeft();
			int y = barPointVector[chooserPoint_y].GetTop();
			if (x < 1595) {
				barPointVector[chooserPoint_y].SetTopLeft(x + 40, y);
			}
		}
		chooser.SetTopLeft(chooser_x[chooserPoint_x], chooser_y[chooserPoint_y]);
	}
	else {}
}

void Setting::ChooserClick() {
	if (where == 0) {
		if (chooserPoint_y > 2 && chooserPoint_y < 13) {
			buttonVector[chooserPoint_y - 3].Click();
		}
		else if (chooserPoint_y == 13) {
			buttonVector[chooserPoint_x + 8].Click();
		}
		else if (chooserPoint_y == 14) {
			buttonVector[chooserPoint_y - 1].Click();
		}
	}
	else {
		if (languageChooserPosition == 1) {
			backToSetting.Click();
		}
	}
}

void Setting::ShowImage() {
	if (where == 0) {
		chooser.ShowBitmap();
		buttonVector[languageSetup].ShowImage();
		buttonVector[controls].ShowImage();
		buttonVector[toggleFullscreen].ShowImage();
		buttonVector[enableGrid].ShowImage();
		buttonVector[disableWobbleEffect].ShowImage();
		buttonVector[disableParticalEffect].ShowImage();
		buttonVector[disableScreenshack].ShowImage();
		buttonVector[forceHighcontrastColours].ShowImage();
		buttonVector[preventBlingkingColours].ShowImage();
		buttonVector[doNotPromptOnRestart].ShowImage();
		buttonVector[None].ShowImage();
		buttonVector[deFault].ShowImage();
		buttonVector[stretch].ShowImage();
		buttonVector[Back].ShowImage();
		bar0.ShowBitmap();
		bar1.ShowBitmap();
		bar2.ShowBitmap();
		barPointVector[0].ShowBitmap();
		barPointVector[1].ShowBitmap();
		barPointVector[2].ShowBitmap();

	}
	else {
		chooser.ShowBitmap();
		english.ShowImage();
		backToSetting.ShowImage();
	}
}

void Setting::ShowText(CDC *pDC) {
	if (where == 0) {
		CTextDraw::ChangeFontLog(pDC, 38, "Darumadrop One", 0xFFFFFF);
		buttonVector[languageSetup].ShowText(pDC);
		buttonVector[controls].ShowText(pDC);
		buttonVector[toggleFullscreen].ShowText(pDC);
		buttonVector[enableGrid].ShowText(pDC);
		buttonVector[disableWobbleEffect].ShowText(pDC);
		buttonVector[disableParticalEffect].ShowText(pDC);
		buttonVector[disableScreenshack].ShowText(pDC);
		buttonVector[forceHighcontrastColours].ShowText(pDC);
		buttonVector[preventBlingkingColours].ShowText(pDC);
		buttonVector[doNotPromptOnRestart].ShowText(pDC);
		buttonVector[None].ShowText(pDC);
		buttonVector[deFault].ShowText(pDC);
		buttonVector[stretch].ShowText(pDC);
		buttonVector[Back].ShowText(pDC);
		CenterTextDraw::Print(pDC, 960, 100, "SETTING:");
		CenterTextDraw::Print(pDC, 500, 200, "MUSIC VOLUME:");
		CenterTextDraw::Print(pDC, 500, 250, "SOUND VILUME:");
		CenterTextDraw::Print(pDC, 578, 300, "INPUT REPEAT DELAY:");
		CenterTextDraw::Print(pDC, 237, 946, "ZOOM MODE:");
	}
	else {
		CTextDraw::ChangeFontLog(pDC, 35, "Darumadrop One", 0xFFFFFF);
		CenterTextDraw::Print(pDC, 960, 400, "ARE YOU EXPECTING A CHINESE TRANSLATION?");
		english.ShowText(pDC);
		backToSetting.ShowText(pDC);
		CTextDraw::ChangeFontLog(pDC, 100, "Darumadrop One", 0x0000FF);
		CenterTextDraw::Print(pDC, 960, 700, "NO WAY");
	}
}

void Setting::MouseDown(POINT point) {
	for (int i = 0; i < 3; i++) {
		if (point.x > barPointVector[i].GetLeft() && point.x < barPointVector[i].GetLeft() + barPointVector[i].GetWidth() && point.y > barPointVector[i].GetTop() && point.y < barPointVector[i].GetTop() + barPointVector[i].GetHeight()) {
			whichPointClick = i;
			barPointVector[i].SetFrameIndexOfBitmap(2);
		}
	}
}

void Setting::MouseUp() {
	whichPointClick = -1;
	for (int i = 0; i < 3; i++) {
		barPointVector[i].SetFrameIndexOfBitmap(0);
	}
}

void Setting::MouseMove(POINT point) {
	if (whichPointClick == 0 || whichPointClick == 1) {
		if (point.x >= 1155 && point.x <= 1595) {
			int x = point.x;
			if (x % 2 == 0) {
				x += 1;
			}
			barPointVector[whichPointClick].SetTopLeft(x, 167 + 54 * whichPointClick);
		}
		else if (point.x < 1155) {
			barPointVector[whichPointClick].SetTopLeft(1155, 167 + 54 * whichPointClick);
		}
		else {
			barPointVector[whichPointClick].SetTopLeft(1595, 167 + 54 * whichPointClick);
		}
	}
	else if (whichPointClick == 2) {
		if (point.x >= 1155 && point.x <= 1595) {
			int x = point.x;
			x = (x - 1133) / 44;
			if (x < 0) x = 0;
			if (10 < x) x = 10;
			barPointVector[2].SetTopLeft(1155 + 44 * x, 275);
		}
		else if (point.x < 1155) {
			barPointVector[whichPointClick].SetTopLeft(1155, 167 + 54 * whichPointClick);
		}
		else {
			barPointVector[whichPointClick].SetTopLeft(1595, 167 + 54 * whichPointClick);
		}
	}
	else {
		for (int i = 0; i < 3; i++) {
			if (point.x > barPointVector[i].GetLeft() && point.x < barPointVector[i].GetLeft() + barPointVector[i].GetWidth() && point.y > barPointVector[i].GetTop() && point.y < barPointVector[i].GetTop() + barPointVector[i].GetHeight()) {
				barPointVector[i].SetFrameIndexOfBitmap(1);
			}
			else if (barPointVector[i].GetFrameIndexOfBitmap() == 1) {
				barPointVector[i].SetFrameIndexOfBitmap(0);
			}
		}
	}
}

void Setting::SetSettingActive() {
	buttonVector[languageSetup].SetActivity(true);
	buttonVector[controls].SetActivity(true);
	buttonVector[toggleFullscreen].SetActivity(true);
	buttonVector[enableGrid].SetActivity(true);
	buttonVector[disableWobbleEffect].SetActivity(true);
	buttonVector[disableParticalEffect].SetActivity(true);
	buttonVector[disableScreenshack].SetActivity(true);
	buttonVector[forceHighcontrastColours].SetActivity(true);
	buttonVector[preventBlingkingColours].SetActivity(true);
	buttonVector[doNotPromptOnRestart].SetActivity(true);
	buttonVector[None].SetActivity(true);
	buttonVector[deFault].SetActivity(true);
	buttonVector[Back].SetActivity(true);
}

void Setting::SetSettingUnActive() {
	buttonVector[languageSetup].SetActivity(false);
	buttonVector[controls].SetActivity(false);
	buttonVector[toggleFullscreen].SetActivity(false);
	buttonVector[enableGrid].SetActivity(false);
	buttonVector[disableWobbleEffect].SetActivity(false);
	buttonVector[disableParticalEffect].SetActivity(false);
	buttonVector[disableScreenshack].SetActivity(false);
	buttonVector[forceHighcontrastColours].SetActivity(false);
	buttonVector[preventBlingkingColours].SetActivity(false);
	buttonVector[doNotPromptOnRestart].SetActivity(false);
	buttonVector[None].SetActivity(false);
	buttonVector[deFault].SetActivity(false);
	buttonVector[Back].SetActivity(false);
}

void Setting::SetLanguageActive() {
	english.SetActivity(true);
	backToSetting.SetActivity(true);
}

void Setting::SetLanguageUnActive() {
	english.SetActivity(false);
	backToSetting.SetActivity(false);
}