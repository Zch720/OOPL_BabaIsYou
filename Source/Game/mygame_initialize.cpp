#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

bool enterGame = true;
bool mainPageInited = false;
bool gameEnd = false;
bool atMainMenu = true;
int currentShowingLayout = 0;
int currentLevel = 1000;
int lastestMap = 1000;
Map levelMap = Map();
POINT map1000BoxPosition = {0, 13};
POINT map1001BoxPosition = {4, 9};
LevelManager levelManager;
AudioManager audioManager;
CloudAnimation cloudAnimation;

using namespace game_framework;
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	ShowInitProgress(0, "Start Initialize...");
	audioManager.Init();
	ShowInitProgress(25, "Initialize Audio...");
	cloudAnimation.Init();
	ShowInitProgress(50, "Initialize Animation...");
	levelManager.Init();
	ShowInitProgress(75, "Initialize Level...");
	initialized = true;
}

void CGameStateInit::OnBeginState()
{
	if (!atMainMenu) {
		if (currentLevel >= 1000) {
			levelMap.LoadWorld(currentLevel);
			if (currentLevel == 1000) {
				levelMap.SetBoxPosition(Point(map1000BoxPosition.x, map1000BoxPosition.y));
			}
			else if (currentLevel == 1001) {
				levelMap.SetBoxPosition(Point(map1001BoxPosition.x, map1001BoxPosition.y));
			}
			lastestMap = currentLevel;
		}
		else {
			levelManager.LoadLevel(currentLevel);
		}
	}
	if (initialized) GotoGameState(GAME_STATE_RUN);
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
}

void CGameStateInit::OnMove() {
	if (initialized) GotoGameState(GAME_STATE_RUN);
}
void CGameStateInit::OnShow()
{
}
