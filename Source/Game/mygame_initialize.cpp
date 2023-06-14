#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "../Expansion/dataio.h"
#include "../Expansion/string_proc.h"
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
POINT map1002BoxPosition = {2, 10};
POINT map1003BoxPosition = {1, 8};
LevelManager levelManager;
AudioManager audioManager;
CloudAnimation cloudAnimation;
MainPage mainPage;

void loadGameData() {
    std::string data = loadFile("game_data.txt");
    if (data == "") return;
    if (data.find('\r') != std::string::npos)
        data.erase(data.find('\r'), 1);
    if (data.find('\n') != std::string::npos)
        data.erase(data.find('\n'), 1);

    std::vector<std::string> datas = stringSplit(data, '|');
    
    lastestMap = std::stoi(datas[0]);
    map1000BoxPosition = { std::stoi(datas[1]), std::stoi(datas[2]) };
    map1001BoxPosition = { std::stoi(datas[3]), std::stoi(datas[4]) };
    map1002BoxPosition = { std::stoi(datas[5]), std::stoi(datas[6]) };
    map1003BoxPosition = { std::stoi(datas[7]), std::stoi(datas[8]) };
}

void saveGameData() {
    std::string data = std::to_string(lastestMap) + "|";
    data += std::to_string(map1000BoxPosition.x) + "|";
    data += std::to_string(map1000BoxPosition.y) + "|";
    data += std::to_string(map1001BoxPosition.x) + "|";
    data += std::to_string(map1001BoxPosition.y) + "|";
    data += std::to_string(map1002BoxPosition.x) + "|";
    data += std::to_string(map1002BoxPosition.y) + "|";
    data += std::to_string(map1003BoxPosition.x) + "|";
    data += std::to_string(map1003BoxPosition.y);
    saveFile("game_data.txt", data);
}

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
	loadGameData();
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
			else if (currentLevel == 1002) {
				levelMap.SetBoxPosition(Point(map1002BoxPosition.x, map1002BoxPosition.y));
			}
			else if (currentLevel == 1003) {
				levelMap.SetBoxPosition(Point(map1003BoxPosition.x, map1003BoxPosition.y));
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
