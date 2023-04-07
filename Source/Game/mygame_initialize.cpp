#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include "MainPage/mainpage.h"

using namespace game_framework;
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(0, "Start Initialize...");	// 一開始的loading進度為0%

	MainPage::StandbyScreenInit();
	MainPage::StartScreenInit();

	MainPage::SetContieuePlayingFunc([this]() {
		GotoGameState(GAME_STATE_RUN);
	});
	MainPage::SetStartTheGameFunc([this]() {
		GotoGameState(GAME_STATE_RUN);
	});
	MainPage::SetExitTheGameFunc([]() {
		exit(0);
	});
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_RETURN || nChar == VK_SPACE) {
		MainPage::ChooserEnter();
		MainPage::SwitchCheck();
	}
	if (nChar == VK_UP) {
		MainPage::ChooserMove(0);
	}
	if (nChar == VK_DOWN) {
		MainPage::ChooserMove(1);
	}
	if (nChar == VK_LEFT) {
		MainPage::ChooserMove(2);
	}
	if (nChar == VK_RIGHT) {
		MainPage::ChooserMove(3);
	}
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	MainPage::SwitchCheck();
	MainPage::CheckMouseClick(point);
}

void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point) {
	MainPage::CheckMouseMove(point);
}

void CGameStateInit::OnShow()
{
	MainPage::ShowImage();

	CDC *pDC = CDDraw::GetBackCDC();

	CTextDraw::ChangeFontLog(pDC, 37, "微軟黑正體", 0xFFFFFF);
	
	MainPage::ShowText(pDC);

	CDDraw::ReleaseBackCDC();
}
