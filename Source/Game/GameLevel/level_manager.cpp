#include "stdafx.h"
#include "level_manager.h"
#include "effect_object.h"
#include "level_data.h"
#include "level_undo.h"
#include "level_move.h"
#include "level_description.h"
#include "level_display.h"
#include "level_property.h"
#include "../AudioManager/audio_manager.h"

void LevelManager::Init() {
	EffectTextures::Init();
}

void LevelManager::Clean() {
	LevelDisplay::AnimationsClear();
}

void LevelManager::LoadLevel(int level) {
	LevelData::LoadLevel(level);
	LevelMove::CreateMoveableMap();
    LevelDescription::CalculateAllDescription();
	LevelProperty::SetBeginProperties();
	LevelDescription::CalculateTextInfo();
	LevelDisplay::UpdateAllObjectTexture();
}

bool LevelManager::IsWin() {
	return LevelData::IsWin();
}

bool LevelManager::IsMoving() {
	bool result = false;
	LevelData::AllObjectForeach([&result](ObjectBase &object) {
		result |= object.IsMoving();
	});
	return result;
}

std::string LevelManager::GetWorldTitle() {
	return LevelData::GetWorldTitle();
}

std::string LevelManager::GetLevelTitle() {
	return LevelData::GetLevelTitle();
}

std::string LevelManager::GetFullTitle() {
	return LevelData::GetFullTitle();
}

Style LevelManager::GetWorldMainStyle() {
	return LevelData::GetWorldMainStyle();
}

std::vector<std::string> LevelManager::GetRules() {
	return PropertyManager::GetRules();
}

void LevelManager::Undo() {
	if (!LevelUndo::CanUndo()) return;
	LevelUndo::Undo();
	LevelProperty::ClearObjectActionFlags();
	LevelDescription::CalculateAllDescription();
	LevelDescription::CalculateTextInfo();
	LevelDisplay::UpdateAllObjectTexture();
	playObjectSound();
}

void LevelManager::MoveWait() {
	LevelMove::Reset();
	LevelMove::ClearObjectMoveFlag();
	LevelMove::MoveWait();
    LevelDescription::CalculateAllDescription();
	LevelProperty::ClearObjectActionFlags();
	LevelProperty::SetProperties();
	LevelDescription::CalculateTextInfo();
	LevelProperty::GameobjectConvert();
	LevelProperty::UpdateOverlapProperty();
	LevelUndo::AddBufferToObjectUndo();
	LevelDisplay::UpdateAllObjectTexture();
	playObjectSound();
}

void LevelManager::MoveUp() {
	LevelMove::Reset();
	LevelMove::ClearObjectMoveFlag();
	LevelMove::MoveUp();
	LevelMove::MoveWait();
    LevelDescription::CalculateAllDescription();
	LevelProperty::ClearObjectActionFlags();
	LevelProperty::SetProperties();
	LevelDescription::CalculateTextInfo();
	LevelProperty::GameobjectConvert();
	LevelProperty::UpdateOverlapProperty();
	LevelUndo::AddBufferToObjectUndo();
	LevelDisplay::UpdateAllObjectTexture();
	playObjectSound();
}

void LevelManager::MoveDown() {
	LevelMove::Reset();
	LevelMove::ClearObjectMoveFlag();
	LevelMove::MoveDown();
	LevelMove::MoveWait();
    LevelDescription::CalculateAllDescription();
	LevelProperty::ClearObjectActionFlags();
	LevelProperty::SetProperties();
	LevelDescription::CalculateTextInfo();
	LevelProperty::GameobjectConvert();
	LevelProperty::UpdateOverlapProperty();
	LevelUndo::AddBufferToObjectUndo();
	LevelDisplay::UpdateAllObjectTexture();
	playObjectSound();
}

void LevelManager::MoveLeft() {
	LevelMove::Reset();
	LevelMove::ClearObjectMoveFlag();
	LevelMove::MoveLeft();
	LevelMove::MoveWait();
    LevelDescription::CalculateAllDescription();
	LevelProperty::ClearObjectActionFlags();
	LevelProperty::SetProperties();
	LevelDescription::CalculateTextInfo();
	LevelProperty::GameobjectConvert();
	LevelProperty::UpdateOverlapProperty();
	LevelUndo::AddBufferToObjectUndo();
	LevelDisplay::UpdateAllObjectTexture();
	playObjectSound();
}

void LevelManager::MoveRight() {
	LevelMove::Reset();
	LevelMove::ClearObjectMoveFlag();
	LevelMove::MoveRight();
	LevelMove::MoveWait();
    LevelDescription::CalculateAllDescription();
	LevelProperty::ClearObjectActionFlags();
	LevelProperty::SetProperties();
	LevelDescription::CalculateTextInfo();
	LevelProperty::GameobjectConvert();
	LevelProperty::UpdateOverlapProperty();
	LevelUndo::AddBufferToObjectUndo();
	LevelDisplay::UpdateAllObjectTexture();
	playObjectSound();
}

void LevelManager::Show() {
	LevelDisplay::TextureCounterAdd();
	LevelDisplay::Show();
}

void LevelManager::playObjectSound() {
	if (LevelProperty::HasObjectDefeat()) {
		AudioManager::PlayDefeatSound();
	}
	if (LevelProperty::HasObjectSink()) {
		AudioManager::PlaySinkSound();
	}
	if (LevelProperty::HasObjectMelt()) {
		AudioManager::PlayMeltSound();
	}
	if (LevelProperty::HasObjectOpen()) {
		AudioManager::PlayOpenSound();
	}
	if (LevelDescription::HasNewDescription()) {
		AudioManager::PlayDescriptionSound();
	}
	if (LevelMove::HasObjectMove()) {
		AudioManager::PlayMoveSound();
	}
	if (LevelUndo::HasDidUndo()) {
		AudioManager::PlayUndoSound();
	}
}