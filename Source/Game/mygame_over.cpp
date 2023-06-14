#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g): CGameState(g)
{
}

void CGameStateOver::OnMove()
{
}

void CGameStateOver::OnBeginState()
{
	if (gameEnd) {
		mainPageClear();
		mapClear();
		gameLevelClear();
		saveGameData();
		exit(0);
	}
	GotoGameState(GAME_STATE_INIT);
}

void CGameStateOver::OnInit()
{
	ShowInitProgress(100, "OK!");
}

void CGameStateOver::OnShow()
{

}

void CGameStateOver::mainPageClear() {
}
void CGameStateOver::mapClear() {
}
void CGameStateOver::gameLevelClear() {
}