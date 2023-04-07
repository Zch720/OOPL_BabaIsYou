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
	levelManager.LoadLevel(0);
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	if (levelManager.IsWin()) {
		GotoGameState(GAME_STATE_OVER);
	}
	if (!moveBuffer.empty() && !levelManager.IsMoving()) {
		int step = moveBuffer.top();
		moveBuffer.pop();

		if (step == DIRECTION_UP) {
			levelManager.MoveUp();
		}
		else if (step == DIRECTION_DOWN) {
			levelManager.MoveDown();
		}
		else if (step == DIRECTION_LEFT) {
			levelManager.MoveLeft();
		}
		else if (step == DIRECTION_RIGHT) {
			levelManager.MoveRight();
		}
		else if (step == -1) {
			levelManager.Undo();
		}
	}
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_UP) {
		moveBuffer.push(DIRECTION_UP);
	}
	else if (nChar == VK_DOWN) {
		moveBuffer.push(DIRECTION_DOWN);
	}
	else if (nChar == VK_LEFT) {
		moveBuffer.push(DIRECTION_LEFT);
	}
	else if (nChar == VK_RIGHT) {
		moveBuffer.push(DIRECTION_RIGHT);
	}
	else if (nChar == VK_BACK || nChar == 'Z') {
		moveBuffer.push(-1);
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
	levelManager.Show();
}
