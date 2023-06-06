#pragma once

#include <vector>
#include "effect_object.h"

class LevelDisplay {
private:
    static const int OFFSET_SPEED = 3;
    static const int OFFSET_COUNT = 24;
    static const int MAX_OFFSET_COUNT = OFFSET_SPEED * OFFSET_COUNT;
    static const int OFFSET_COUNT_CENTER = OFFSET_COUNT / 2 + 1;
    static const int OFFSET_COUNT_OFFSET = OFFSET_COUNT / 4 + 1;
    static const int MAX_TEXTURE_WAIT_TIME = 12;
    static const clock_t SHOW_DEAD_HINT_TIME = 3000;
    static int nextTextureWaitTime;
    static int textureCount;
    static bool changeTexture;
    static Point floatOffset;
    static int floatOffsetCount;

    static game_framework::CMovingBitmap deadUndoHint;
    static game_framework::CMovingBitmap deadRestartHint;
    static bool showDeadTimming;
    static bool shouldShowDeadHint;
    static clock_t showDeadHintTimer;

	static std::vector<WinObjectEffect> winObjectEffects;
	static std::vector<DispearEffect> dispearEffects;
    static std::vector<EffectObjectBase*> moveEffects;

    static ShowInfo getObjectShowInfo(ObjectInfo &objectInfo);
    static void showByZIndex(int zIndex);
    static Point getObjectTextureOffset(ObjectId objectId);
    static void updateFloatOffset();

    static void checkDeadHint();
    static void showDeadHint();

	static void addWinObjectAnimation();
	static void addDispearAnimation();
    static void addMoveAnimation();

	static void showWinAniations();
	static void showDispearAniations();
	static void showMoveAniations();
	static void cleanAnimations();

public:
    static void Init();

    static void TextureCounterAdd();
    static void UpdateAllObjectTexture();
    static void Show();
	static void AnimationsClear();
};