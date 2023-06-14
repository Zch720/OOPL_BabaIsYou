#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include "../Expansion/log.h"

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
	if (!mainPageInited) {
		mainPageInit();
		mainPageInited = true;
	}

	if (!enterGame) {
		cloudAnimation.StartCloudOpen();
	} else {
		enterGame = false;
	}

	if (atMainMenu) {
		currentShowingLayout = 0;
		audioManager.PlayMenuBGM();
	}
	else if (currentLevel >= 1000) {
		currentShowingLayout = 1;
		audioManager.PlayMapBGM();
	}
	else {
		currentShowingLayout = 2;
		audioManager.PlayBabaBGM();
	}
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	if (!atMainMenu && currentLevel < 1000 && !cloudAnimation.IsShowing() && levelManager.IsWin()) {
		currentLevel = lastestMap;
		clearInputBuffer();
		audioManager.PlayCongratulationSound();
		cloudAnimation.StartCloudCloseWithCongratulation();
	}
	if (cloudAnimation.IsCloudClosing() && cloudAnimation.IsCloudCloseEnd()) {
		cloudAnimation.StopCloudClose();
		GotoGameState(GAME_STATE_OVER);
	}
	if (cloudAnimation.IsCloudOpenEnd()) {
		cloudAnimation.StopCloudOpen();
	}
	updateLongPressInput();
	if (!inputBuffer.empty()) {
		KeyInputType inputKey = inputBuffer.front();
		inputBuffer.pop();
		if (isSetting) {
			settingKeyDown(inputKey);
		} else if (isPause) {
			pauseKeyDown(inputKey);
		} else if (atMainMenu) {
			mainPageKeyDown(inputKey);
		} else if (currentLevel >= 1000) {
			levelMapKeyDown(inputKey);
		} else {
			gameLevelKeyDown(inputKey);
		}
	}
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (cloudAnimation.IsShowing()) return;
	if (nChar == VK_UP || nChar == 'W') {
		upPress.isPress = true;
		upPress.pressTime = clock();
		upPress.lastPressTime = clock();
		inputBuffer.push(INPUT_MOVE_UP);
	}
	else if (nChar == VK_DOWN || nChar == 'S') {
		downPress.isPress = true;
		downPress.pressTime = clock();
		downPress.lastPressTime = clock();
		inputBuffer.push(INPUT_MOVE_DOWN);
	}
	else if (nChar == VK_LEFT || nChar == 'A') {
		leftPress.isPress = true;
		leftPress.pressTime = clock();
		leftPress.lastPressTime = clock();
		inputBuffer.push(INPUT_MOVE_LEFT);
	}
	else if (nChar == VK_RIGHT || nChar == 'D') {
		rightPress.isPress = true;
		rightPress.pressTime = clock();
		rightPress.lastPressTime = clock();
		inputBuffer.push(INPUT_MOVE_RIGHT);
	}
	else if (nChar == VK_SPACE || nChar == VK_RETURN) {
		waitPress.isPress = true;
		waitPress.pressTime = clock();
		waitPress.lastPressTime = clock();
		inputBuffer.push(INPUT_ENTER);
	}
	else if (nChar == VK_BACK || nChar == 'Z') {
		undoPress.isPress = true;
		undoPress.pressTime = clock();
		undoPress.lastPressTime = clock();
		inputBuffer.push(INPUT_BACK);
	}
	else if (nChar == VK_ESCAPE || nChar == 'P') {
		inputBuffer.push(INPUT_PAUSE);
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (nChar == VK_UP || nChar == 'W') {
		upPress.isPress = false;
	}
	else if (nChar == VK_DOWN || nChar == 'S') {
		downPress.isPress = false;
	}
	else if (nChar == VK_LEFT || nChar == 'A') {
		leftPress.isPress = false;
	}
	else if (nChar == VK_RIGHT || nChar == 'D') {
		rightPress.isPress = false;
	}
	else if (nChar == VK_SPACE || nChar == VK_RETURN) {
		waitPress.isPress = false;
	}
	else if (nChar == VK_BACK || nChar == 'Z') {
		undoPress.isPress = false;
	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	if (isSetting) {
		settingPage.MouseDown(point);
		settingPage.CheckMouseClick(point);
	} else if (isPause) {
		pausePage.MouseClick(point);
	} else if (atMainMenu) {
		mainPageLeftButtonDown(point);
	}
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	if (isSetting) {
		settingPage.MouseUp();
	}
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	if (isSetting) {
		settingPage.MouseMove(point);
		settingPage.CheckMouseMove(point);
	} else if (isPause) {
		pausePage.MouseMove(point);
	} else if (atMainMenu) {
		mainPageMouseMove(point);
	}
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
	if (isSetting) {
		settingPage.ShowImage();
		CDC *pDC = CDDraw::GetBackCDC();
		settingPage.ShowText(pDC);
		CDDraw::ReleaseBackCDC();
	}
	else if (isPause) {
		pausePage.ShowImage();
		CDC *pDC = CDDraw::GetBackCDC();
		pausePage.ShowText(pDC);
		CDDraw::ReleaseBackCDC();
	}
	else if (currentShowingLayout == 0) {
		mainPage.ShowImage();
		CDC *pDC = CDDraw::GetBackCDC();
		CTextDraw::ChangeFontLog(pDC, 40, "Darumadrop One", 0xFFFFFF);
		mainPage.ShowText(pDC);
		CDDraw::ReleaseBackCDC();
	}
	else if (currentShowingLayout == 1) {
		levelMap.Show();
	}
	else if (currentShowingLayout == 2) {
		levelManager.Show();
	}
	cloudAnimation.Show();
}

void CGameStateRun::clearInputBuffer() {
	while(!inputBuffer.empty()) inputBuffer.pop();
}

void CGameStateRun::updateLongPressInput() {
	if (upPress.isPress) {
		if (clock() - upPress.pressTime > PRESS_WAIT_TIME && clock() - upPress.lastPressTime > PRESS_INTERVAL) {
			upPress.lastPressTime = clock();
			inputBuffer.push(INPUT_MOVE_UP);
		}
	}
	else if (downPress.isPress) {
		if (clock() - downPress.pressTime > PRESS_WAIT_TIME && clock() - downPress.lastPressTime > PRESS_INTERVAL) {
			downPress.lastPressTime = clock();
			inputBuffer.push(INPUT_MOVE_DOWN);
		}
	}
	else if (leftPress.isPress) {
		if (clock() - leftPress.pressTime > PRESS_WAIT_TIME && clock() - leftPress.lastPressTime > PRESS_INTERVAL) {
			leftPress.lastPressTime = clock();
			inputBuffer.push(INPUT_MOVE_LEFT);
		}
	}
	else if (rightPress.isPress) {
		if (clock() - rightPress.pressTime > PRESS_WAIT_TIME && clock() - rightPress.lastPressTime > PRESS_INTERVAL) {
			rightPress.lastPressTime = clock();
			inputBuffer.push(INPUT_MOVE_RIGHT);
		}
	}
	else if (waitPress.isPress) {
		if (clock() - waitPress.pressTime > PRESS_WAIT_TIME && clock() - waitPress.lastPressTime > PRESS_INTERVAL) {
			waitPress.lastPressTime = clock();
			inputBuffer.push(INPUT_ENTER);
		}
	}
	else if (undoPress.isPress) {
		if (clock() - undoPress.pressTime > PRESS_WAIT_TIME && clock() - undoPress.lastPressTime > PRESS_INTERVAL) {
			undoPress.lastPressTime = clock();
			inputBuffer.push(INPUT_BACK);
		}
	}
}

void CGameStateRun::mainPageInit() {
	mainPage.MainpageInit();
	mainPage.SetContieuePlayingFunc([this]() {
		atMainMenu = false;
		currentLevel = lastestMap;
		clearInputBuffer();
		audioManager.PlayChangeSceneSound();
		cloudAnimation.StartCloudClose();
	});
	mainPage.SetStartTheGameFunc([this]() {
		atMainMenu = false;
		currentLevel = lastestMap;
		clearInputBuffer();
		audioManager.PlayChangeSceneSound();
		cloudAnimation.StartCloudClose();
	});
	mainPage.SetSettingsFunc([this]() {
		isSetting = true;
		audioManager.PlayChooseSettingSound();
		createMenuSettingPage();
	});
	mainPage.SetExitTheGameFunc([this]() {
		gameEnd = true;
		GotoGameState(GAME_STATE_OVER);
	});
}

void CGameStateRun::mainPageKeyDown(KeyInputType inputType) {
	if (inputType == INPUT_MOVE_UP) {
		mainPage.ChooserMove(0);
	}
	else if (inputType == INPUT_MOVE_DOWN) {
		mainPage.ChooserMove(1);
	}
	else if (inputType == INPUT_MOVE_LEFT) {
		mainPage.ChooserMove(2);
	}
	else if (inputType == INPUT_MOVE_RIGHT) {
		mainPage.ChooserMove(3);
	}
	else if (inputType == INPUT_ENTER) {
		mainPage.ChooserEnter();
		mainPage.SwitchCheck();
	}
}
void CGameStateRun::mainPageLeftButtonDown(CPoint point) {
	mainPage.CheckMouseClick(point);
	mainPage.SwitchCheck();
}
void CGameStateRun::mainPageMouseMove(CPoint point) {
	mainPage.CheckMouseMove(point);
}

void CGameStateRun::levelMapKeyDown(KeyInputType inputType) {
	if (inputType == INPUT_MOVE_UP) {
		levelMap.MoveUp();
	}
	else if (inputType == INPUT_MOVE_DOWN) {
		levelMap.MoveDown();
	}
	else if (inputType == INPUT_MOVE_LEFT) {
		levelMap.MoveLeft();
	}
	else if (inputType == INPUT_MOVE_RIGHT) {
		levelMap.MoveRight();
	}
	else if (inputType == INPUT_ENTER) {
		if (levelMap.CheckIndex() != -1) {
			if (currentLevel == 1000) {
				map1000BoxPosition = levelMap.GetBoxPosition();
			}
			else if (currentLevel == 1001) {
				map1001BoxPosition = levelMap.GetBoxPosition();
			}
			currentLevel = levelMap.CheckIndex();
			cloudAnimation.StartCloudClose();
		}
	}
	else if (inputType == INPUT_PAUSE) {
		isPause = true;
		createMapPausePage();
	}
}

void CGameStateRun::gameLevelKeyDown(KeyInputType inputType) {
	if (inputType == INPUT_MOVE_UP) {
		levelManager.MoveUp();
	}
	else if (inputType == INPUT_MOVE_DOWN) {
		levelManager.MoveDown();
	}
	else if (inputType == INPUT_MOVE_LEFT) {
		levelManager.MoveLeft();
	}
	else if (inputType == INPUT_MOVE_RIGHT) {
		levelManager.MoveRight();
	}
	else if (inputType == INPUT_ENTER) {
		levelManager.MoveWait();
	}
	else if (inputType == INPUT_BACK) {
		levelManager.Undo();
	}
	else if (inputType == INPUT_PAUSE) {
		isPause = true;
		createLevelPausePage();
	}
}

void CGameStateRun::createMapPausePage() {
	Style style;
	std::string title;
	if (currentLevel == 1000) {
		style = STYLE_DEFAULT;
		title = "MAP";
	}
	else if (currentLevel == 1001) {
		style = STYLE_LAKE;
		title = "1. THE LAKE";
	}
	else if (currentLevel == 1002) {
		style = STYLE_ISLAND;
		title = "2. SOLITARY ISLAND";
	}
	else if (currentLevel == 1003) {
		style = STYLE_RUIN;
		title = "3. TEMPLE RUINS";
	}
	pausePage = PauseLayout(style, title, {});
	pausePage.SetResumeButtonOnClickFunc([this]() {
		isPause = false;
	});

	if (currentLevel != 1000) {
		pausePage.SetReturnMapButtonOnClickFunc([this]() {
			isPause = false;
			currentLevel = 1000;
			audioManager.PlayChangeSceneSound();
			cloudAnimation.StartCloudClose();
		});
	}
	
	pausePage.SetRestartButtonOnClickFunc([this]() {
		isPause = false;
		audioManager.PlayRestartSound();
		cloudAnimation.StartCloudClose();
	});
	pausePage.SetSettingButtonOnClickFunc([this]() {
		isSetting = true;
		audioManager.PlayChooseSettingSound();
		createMapSettingPage();
	});
	pausePage.SetReturnMenuButtonOnClickFunc([this]() {
		isPause = false;
		atMainMenu = true;
		audioManager.PlayChangeSceneSound();
		cloudAnimation.StartCloudClose();
	});
}

void CGameStateRun::createLevelPausePage() {
	pausePage = PauseLayout(
		levelManager.GetWorldMainStyle(),
		levelManager.GetFullTitle(),
		levelManager.GetRules()
	);
	pausePage.SetResumeButtonOnClickFunc([this]() {
		isPause = false;
	});
	pausePage.SetReturnMapButtonOnClickFunc([this]() {
		isPause = false;
		currentLevel = lastestMap;
		audioManager.PlayChangeSceneSound();
		cloudAnimation.StartCloudClose();
	});
	pausePage.SetRestartButtonOnClickFunc([this]() {
		isPause = false;
		audioManager.PlayRestartSound();
		cloudAnimation.StartCloudClose();
	});
	pausePage.SetSettingButtonOnClickFunc([this]() {
		isSetting = true;
		audioManager.PlayChooseSettingSound();
		createLevelSettingPage();
	});
	pausePage.SetReturnMenuButtonOnClickFunc([this]() {
		isPause = false;
		atMainMenu = true;
		audioManager.PlayChangeSceneSound();
		cloudAnimation.StartCloudClose();
	});
}

void CGameStateRun::pauseKeyDown(KeyInputType inputKey) {
	if (inputKey == INPUT_MOVE_UP) {
		pausePage.ChooserMoveUp();
	} else if (inputKey == INPUT_MOVE_DOWN) {
		pausePage.ChooserMoveDown();
	} else if (inputKey == INPUT_ENTER) {
		pausePage.Choose();
	} else if (inputKey == INPUT_PAUSE) {
		isPause = false;
	}
}

void CGameStateRun::createMenuSettingPage() {
	settingPage = Setting();
	settingPage.SetButtonWorld(STYLE_DEFAULT);
	settingPage.SetBackFunc([this]() {
		isSetting = false;
		audioManager.PlayChooseButtonSound();
	});
}

void CGameStateRun::createMapSettingPage() {
	settingPage = Setting();
	if (currentLevel == 1000) {
		settingPage.SetButtonWorld(STYLE_DEFAULT);
	} else if (currentLevel == 1001) {
		settingPage.SetButtonWorld(STYLE_LAKE);
	} else if (currentLevel == 1002) {
		settingPage.SetButtonWorld(STYLE_ISLAND);
	} else if (currentLevel == 1003) {
		settingPage.SetButtonWorld(STYLE_RUIN);
	}
	settingPage.SetBackFunc([this]() {
		isSetting = false;
		audioManager.PlayChooseButtonSound();
	});
}

void CGameStateRun::createLevelSettingPage() {
	settingPage = Setting();
	settingPage.SetButtonWorld(levelManager.GetWorldMainStyle());
	settingPage.SetBackFunc([this]() {
		isSetting = false;
		audioManager.PlayChooseButtonSound();
	});
}

void CGameStateRun::settingKeyDown(KeyInputType inputType) {
	if (inputType == INPUT_MOVE_UP) {
		settingPage.ChooserMoveUp();
	} else if (inputType == INPUT_MOVE_DOWN) {
		settingPage.ChooserMoveDown();
	} else if (inputType == INPUT_MOVE_LEFT) {
		settingPage.ChooserMoveLeft();
	} else if (inputType == INPUT_MOVE_RIGHT) {
		settingPage.ChooserMoveRight();
	} else if (inputType == INPUT_ENTER) {
		settingPage.ChooserClick();
	} else if (inputType == INPUT_PAUSE) {
		isSetting = false;
	}
}