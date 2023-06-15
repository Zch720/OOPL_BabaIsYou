#pragma once

#include "Map/map.h"
#include "MainPage/mainpage.h"
#include "GameLevel/level_manager.h"
#include "AudioManager/audio_manager.h"
#include "CloudAnimation/cloud_animation.h"

extern bool enterGame;
extern bool mainPageInited;
extern bool gameEnd;
extern bool atMainMenu;
extern bool showMainMenuCredits;
extern int currentShowingLayout;
extern int currentLevel;
extern int lastestMap;
extern Map levelMap;
extern POINT map1000BoxPosition;
extern POINT map1001BoxPosition;
extern POINT map1002BoxPosition;
extern POINT map1003BoxPosition;
extern LevelManager levelManager;
extern AudioManager audioManager;
extern CloudAnimation cloudAnimation;
extern MainPage mainPage;

void loadGameData();
void saveGameData();