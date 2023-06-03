#include "stdafx.h"
#include "game_level_config.h"
#include "property_manager.h"
#include "texture_manager.h"
#include "level_data.h"
#include "level_property.h"
#include "level_description.h"
#include "level_display.h"

int LevelDisplay::nextTextureWaitTime = LevelDisplay::MAX_TEXTURE_WAIT_TIME;
int LevelDisplay::textureCount = 0;
bool LevelDisplay::changeTexture = false;
Point LevelDisplay::floatOffset = Point(0, 0);
int LevelDisplay::floatOffsetCount = LevelDisplay::OFFSET_COUNT_OFFSET;

std::vector<WinObjectEffect> LevelDisplay::winObjectEffects = {};
std::vector<DispearEffect> LevelDisplay::dispearEffects = {};

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

    LevelData::GetBackground().ShowBitmap();
    for (int i = 1; i < MAX_OBJECT_Z_INDEX; i++) {
        showByZIndex(i);
    }
    LevelData::AllObjectForeach([](ObjectBase &object) {
        if (!LevelDescription::IsConnectedTextobject(object.GetInfo())) return;
        if (LevelDescription::IsUsableTextobject(object.GetInfo())) return;
        object.ShowCrossed();
    });

	showAniations();
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

void LevelDisplay::showAniations() {
	for (WinObjectEffect &effect : winObjectEffects) {
		effect.Show();
	}
	for (DispearEffect &effect : dispearEffects) {
		effect.Show();
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
}