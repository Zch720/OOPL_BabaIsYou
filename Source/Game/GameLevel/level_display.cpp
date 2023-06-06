#include "stdafx.h"
#include "game_level_config.h"
#include "property_manager.h"
#include "texture_manager.h"
#include "level_data.h"
#include "level_property.h"
#include "level_description.h"
#include "level_display.h"
#include "level_move.h"

int LevelDisplay::nextTextureWaitTime = LevelDisplay::MAX_TEXTURE_WAIT_TIME;
int LevelDisplay::textureCount = 0;
bool LevelDisplay::changeTexture = false;
Point LevelDisplay::floatOffset = Point(0, 0);
int LevelDisplay::floatOffsetCount = LevelDisplay::OFFSET_COUNT_OFFSET;

game_framework::CMovingBitmap LevelDisplay::deadUndoHint = {};
game_framework::CMovingBitmap LevelDisplay::deadRestartHint = {};
bool LevelDisplay::showDeadTimming = false;
bool LevelDisplay::shouldShowDeadHint = false;
clock_t LevelDisplay::showDeadHintTimer = 0;

std::vector<WinObjectEffect> LevelDisplay::winObjectEffects = {};
std::vector<DispearEffect> LevelDisplay::dispearEffects = {};
std::vector<DeadHintBubbleEffect> LevelDisplay::deadHintBubbleEffects = {};
std::vector<EffectObjectBase*> LevelDisplay::moveEffects = {};

void LevelDisplay::Init() {
    deadUndoHint.LoadBitmapByString({
        "./resources/DeadHint/undo/0.bmp",
        "./resources/DeadHint/undo/1.bmp",
        "./resources/DeadHint/undo/2.bmp",
    }, 0x000000);
    deadUndoHint.SetAnimation(200, false);
    deadUndoHint.SetTopLeft(600, 10);
    deadRestartHint.LoadBitmapByString({
        "./resources/DeadHint/restart/0.bmp",
        "./resources/DeadHint/restart/1.bmp",
        "./resources/DeadHint/restart/2.bmp",
    }, 0x000000);
    deadRestartHint.SetAnimation(200, false);
    deadRestartHint.SetTopLeft(1170, 10);
}

void LevelDisplay::TextureCounterAdd() {
    if (--nextTextureWaitTime <= 0) {
        nextTextureWaitTime = MAX_TEXTURE_WAIT_TIME;
        textureCount = (textureCount + 1) % 3;
        changeTexture = true;
    } else {
        changeTexture = false;
    }
}

void LevelDisplay::UpdateAllObjectTexture() {
    LevelData::AllObjectForeach([](ObjectBase &object) {
        object.AddAnimationCount();
        object.CheckColorUpdate();
    });
}

void LevelDisplay::Show() {
    updateFloatOffset();
	addWinObjectAnimation();
	addDispearAnimation();
    addMoveAnimation();
    checkDeadHint();

    LevelData::GetBackground().ShowBitmap();
    for (int i = 1; i < MAX_OBJECT_Z_INDEX; i++) {
        showByZIndex(i);
    }    
	LevelData::AllObjectForeach([](ObjectBase &object) {
        if (!LevelDescription::IsConnectedTextobject(object.GetInfo())) return;
        if (LevelDescription::IsUsableTextobject(object.GetInfo())) return;
        object.ShowCrossed();
    });

    showDeadHint();
    showDeadHintBubbleAniations();

    showMoveAniations();
    showDispearAniations();
	showWinAniations();
	cleanAnimations();
}

void LevelDisplay::AnimationsClear() {
	winObjectEffects.clear();
}

ShowInfo LevelDisplay::getObjectShowInfo(ObjectInfo &info) {
    return {
        changeTexture,
        LevelDescription::IsConnectedTextobject(info),
        LevelData::GetGameobjectConnectState(info),
        getObjectTextureOffset(info.objectId)
    };
}

void LevelDisplay::showByZIndex(int zIndex) {
    LevelData::AllObjectForeach([zIndex](ObjectBase &object) {
        if (TextureManager::GetZIndex(object.GetObjectId()) == zIndex) {
            object.UpdateTextureFrame(getObjectShowInfo(object.GetInfo()));
            object.Show();
        }
    });
}

Point LevelDisplay::getObjectTextureOffset(ObjectId objectId) {
    if (PropertyManager::ObjectHasProperty(objectId, PROPERTY_FLOAT)) {
        return floatOffset;
    }
    return Point(0, 0);
}

void LevelDisplay::updateFloatOffset() {
    if (++floatOffsetCount >= MAX_OFFSET_COUNT) floatOffsetCount = 1;
    floatOffset = Point(
        0,
        -abs(floatOffsetCount / OFFSET_SPEED - OFFSET_COUNT_CENTER) + OFFSET_COUNT_OFFSET
    );
    if (TextureManager::GetTextureSize() == 108) floatOffset *= 2;
}

void LevelDisplay::checkDeadHint() {
    if (LevelData::HasYouObjectInGameboard()) {
        if (shouldShowDeadHint) {
            addDeadHintBubbleAnimation();
        }
        showDeadTimming = false;
        shouldShowDeadHint = false;
        return;
    }
    if (shouldShowDeadHint) return;

    if (!showDeadTimming) {
        showDeadTimming = true;
        showDeadHintTimer = clock();
    }
    else if (clock() - showDeadHintTimer > SHOW_DEAD_HINT_TIME) {
        addDeadHintBubbleAnimation();
        shouldShowDeadHint = true;
        showDeadTimming = false;
    }
}

void LevelDisplay::showDeadHint() {
    if (shouldShowDeadHint) {
        deadUndoHint.ShowBitmap();
        deadRestartHint.ShowBitmap();
    }
}

void LevelDisplay::addWinObjectAnimation() {
	LevelData::AllObjectForeach([](ObjectBase &object) {
		if (object.HasProperty(PROPERTY_WIN)) {
			if (rand() % 41) return;
			Point position = TextureManager::GetTextureOrogionPosition();
			position += object.GetPosition() * TextureManager::GetTextureSize();
			position += Point(1, 1) * (TextureManager::GetTextureSize() / 2);

			winObjectEffects.push_back(WinObjectEffect(position, TextureManager::GetTextureSize()));
		}
	});
}

void LevelDisplay::addDispearAnimation() {
	std::vector<Point> points = LevelProperty::GetDeleteObjectPoints();
	LevelProperty::ClearDeleteObjectPoints();
	for (Point &point : points) {
		int time = rand() % 3 + 5;
		Point position = TextureManager::GetTextureOrogionPosition();
		position += point * TextureManager::GetTextureSize();
		position += Point(1, 1) * (TextureManager::GetTextureSize() / 2);
		while (time--) {
			dispearEffects.push_back(DispearEffect(position, TextureManager::GetTextureSize()));
		}
	}
}

void LevelDisplay::addDeadHintBubbleAnimation() {
    POINT undoCenter = {
        deadUndoHint.GetLeft() + deadUndoHint.GetWidth() / 2,
        deadUndoHint.GetTop() + deadUndoHint.GetHeight() / 2
    };
    POINT restartCenter = {
        deadRestartHint.GetLeft() + deadRestartHint.GetWidth() / 2,
        deadRestartHint.GetTop() + deadRestartHint.GetHeight() / 2
    };
    for (int i = 0; i < 30; i++) {
        deadHintBubbleEffects.push_back(DeadHintBubbleEffect(undoCenter, deadUndoHint.GetWidth() - 16));
    }
    for (int i = 0; i < 40; i++) {
        deadHintBubbleEffects.push_back(DeadHintBubbleEffect(restartCenter, deadRestartHint.GetWidth() - 16));
    }
}

void LevelDisplay::addMoveAnimation() {
    std::vector<LevelMove::MoveInfo> moveInfos = LevelMove::GetMoveObjects();
    for (LevelMove::MoveInfo &moveInfo : moveInfos) {
        Point position = TextureManager::GetTextureOrogionPosition();
        position += moveInfo.position * TextureManager::GetTextureSize();
        position += Point(1, 1) * (TextureManager::GetTextureSize() / 2);

        if (moveInfo.moveDirection == DIRECTION_UP) {
            moveEffects.push_back(new MoveUpEffect(position, TextureManager::GetTextureSize()));
        }
        else if (moveInfo.moveDirection == DIRECTION_DOWN) {
            moveEffects.push_back(new MoveDownEffect(position, TextureManager::GetTextureSize()));
        }
        else if (moveInfo.moveDirection == DIRECTION_LEFT) {
            moveEffects.push_back(new MoveLeftEffect(position, TextureManager::GetTextureSize()));
        }
        else if (moveInfo.moveDirection == DIRECTION_RIGHT) {
            moveEffects.push_back(new MoveRightEffect(position, TextureManager::GetTextureSize()));
        }
    }
}

void LevelDisplay::showWinAniations() {
	for (WinObjectEffect &effect : winObjectEffects) {
		effect.Show();
	}
}

void LevelDisplay::showDispearAniations() {
    for (DispearEffect &effect : dispearEffects) {
        effect.Show();
    }
}

void LevelDisplay::showDeadHintBubbleAniations() {
    for (DeadHintBubbleEffect &effect : deadHintBubbleEffects) {
        effect.Show();
    }
}

void LevelDisplay::showMoveAniations() {
    for (EffectObjectBase *effect : moveEffects) {
        effect -> Show();
    }
}

void LevelDisplay::cleanAnimations() {
	for (size_t i = 0; i < winObjectEffects.size(); i++) {
		if (winObjectEffects[i].IsEnd()) {
			winObjectEffects.erase(winObjectEffects.begin() + i);
			i--;
		}
	}
	for (size_t i = 0; i < dispearEffects.size(); i++) {
		if (dispearEffects[i].IsEnd()) {
			dispearEffects.erase(dispearEffects.begin() + i);
			i--;
		}
	}
    for (size_t i = 0; i < deadHintBubbleEffects.size(); i++) {
		if (deadHintBubbleEffects[i].IsEnd()) {
			deadHintBubbleEffects.erase(deadHintBubbleEffects.begin() + i);
			i--;
		}
	}
    for (size_t i = 0; i < moveEffects.size(); i++) {
        if (moveEffects[i] -> IsEnd()) {
            delete moveEffects[i];
            moveEffects.erase(moveEffects.begin() + i);
            i--;
        }
    }
}