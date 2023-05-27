#include "stdafx.h"
#include "game_level_config.h"
#include "property_manager.h"
#include "texture_manager.h"
#include "level_data.h"
#include "level_description.h"
#include "level_display.h"

int LevelDisplay::nextTextureWaitTime = LevelDisplay::MAX_TEXTURE_WAIT_TIME;
int LevelDisplay::textureCount = 0;
bool LevelDisplay::changeTexture = false;
Point LevelDisplay::floatOffset = Point(0, 0);
int LevelDisplay::floatOffsetCount = LevelDisplay::OFFSET_COUNT_OFFSET;

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

    LevelData::GetBackground().ShowBitmap();
    for (int i = 1; i < MAX_OBJECT_Z_INDEX; i++) {
        showByZIndex(i);
    }
    LevelData::AllObjectForeach([](ObjectBase &object) {
        if (!LevelDescription::IsConnectedTextobject(object.GetInfo())) return;
        if (LevelDescription::IsUsableTextobject(object.GetInfo())) return;
        object.ShowCrossed();
    });
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