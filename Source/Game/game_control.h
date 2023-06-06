#pragma once

#include "Map/map.h"
#include "GameLevel/level_manager.h"
#include "AudioManager/audio_manager.h"
#include "CloudAnimation/cloud_animation.h"

extern bool enterGame;
extern bool mainPageInited;
extern bool gameEnd;
extern bool atMainMenu;
extern int currentShowingLayout;
extern int currentLevel;
extern int lastestMap;
extern Map levelMap;
extern POINT map1000BoxPosition;
extern POINT map1001BoxPosition;
extern LevelManager levelManager;
extern AudioManager audioManager;
extern CloudAnimation cloudAnimation;