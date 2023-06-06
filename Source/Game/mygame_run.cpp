#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include "MainPage/mainpage.h"
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
	if (!inputBuffer.empty()) {
		KeyInputType inputKey = inputBuffer.front();
		inputBuffer.pop();
		if (isPause) {
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
		inputBuffer.push(INPUT_MOVE_UP);
	}
	else if (nChar == VK_DOWN || nChar == 'S') {
		inputBuffer.push(INPUT_MOVE_DOWN);
	}
	else if (nChar == VK_LEFT || nChar == 'A') {
		inputBuffer.push(INPUT_MOVE_LEFT);
	}
	else if (nChar == VK_RIGHT || nChar == 'D') {
		inputBuffer.push(INPUT_MOVE_RIGHT);
	}
	else if (nChar == VK_SPACE || nChar == VK_RETURN) {
		inputBuffer.push(INPUT_ENTER);
	}
	else if (nChar == VK_BACK || nChar == 'Z') {
		inputBuffer.push(INPUT_BACK);
	}
	else if (nChar == VK_ESCAPE || nChar == 'P') {
		inputBuffer.push(INPUT_PAUSE);
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	if (atMainMenu) {
		mainPageLeftButtonDown(point);
	}
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	if (atMainMenu) {
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
	if (isPause) {
		pausePage.ShowImage();
		CDC *pDC = CDDraw::GetBackCDC();
		pausePage.ShowText(pDC);
		CDDraw::ReleaseBackCDC();
	}
	else if (currentShowingLayout == 0) {
		MainPage::ShowImage();
		CDC *pDC = CDDraw::GetBackCDC();
		CTextDraw::ChangeFontLog(pDC, 40, "Darumadrop One", 0xFFFFFF);
		MainPage::ShowText(pDC);
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

void CGameStateRun::mainPageInit() {
	MainPage::MainpageInit();
	MainPage::SetContieuePlayingFunc([this]() {
		atMainMenu = false;
		currentLevel = lastestMap;
		clearInputBuffer();
		audioManager.PlayChangeSceneSound();
		cloudAnimation.StartCloudClose();
	});
	MainPage::SetStartTheGameFunc([this]() {
		atMainMenu = false;
		currentLevel = lastestMap;
		clearInputBuffer();
		audioManager.PlayChangeSceneSound();
		cloudAnimation.StartCloudClose();
	});
	MainPage::SetExitTheGameFunc([this]() {
		gameEnd = true;
		GotoGameState(GAME_STATE_OVER);
	});
}

void CGameStateRun::mainPageKeyDown(KeyInputType inputType) {
	if (inputType == INPUT_MOVE_UP) {
		MainPage::ChooserMove(0);
	}
	else if (inputType == INPUT_MOVE_DOWN) {
		MainPage::ChooserMove(1);
	}
	else if (inputType == INPUT_MOVE_LEFT) {
		MainPage::ChooserMove(2);
	}
	else if (inputType == INPUT_MOVE_RIGHT) {
		MainPage::ChooserMove(3);
	}
	else if (inputType == INPUT_ENTER) {
		MainPage::ChooserEnter();
		MainPage::SwitchCheck();
	}
}
void CGameStateRun::mainPageLeftButtonDown(CPoint point) {
	MainPage::CheckMouseClick(point);
	MainPage::SwitchCheck();
}
void CGameStateRun::mainPageMouseMove(CPoint point) {
	MainPage::CheckMouseMove(point);
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
	std::vector<std::string> rules = {};
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
	pausePage = PauseLayout(
		style,
		title,
		rules
	);
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