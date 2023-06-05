#include "stdafx.h"
#include "level_manager.h"
#include "effect_object.h"
#include "level_data.h"
#include "level_undo.h"
#include "level_move.h"
#include "level_description.h"
#include "level_display.h"
#include "level_property.h"

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
	LevelDescription::CalculateAllDescription();
	LevelDescription::CalculateTextInfo();
	LevelDisplay::UpdateAllObjectTexture();
}

void LevelManager::MoveWait() {
	LevelMove::Reset();
	LevelMove::MoveWait();
    LevelDescription::CalculateAllDescription();
	LevelProperty::SetProperties();
	LevelDescription::CalculateTextInfo();
	LevelProperty::GameobjectConvert();
	LevelProperty::UpdateOverlapProperty();
	LevelUndo::AddBufferToObjectUndo();
	LevelDisplay::UpdateAllObjectTexture();
}

void LevelManager::MoveUp() {
	LevelMove::Reset();
	LevelMove::MoveUp();
	LevelMove::MoveWait();
    LevelDescription::CalculateAllDescription();
	LevelProperty::SetProperties();
	LevelDescription::CalculateTextInfo();
	LevelProperty::GameobjectConvert();
	LevelProperty::UpdateOverlapProperty();
	LevelUndo::AddBufferToObjectUndo();
	LevelDisplay::UpdateAllObjectTexture();
}

void LevelManager::MoveDown() {
	LevelMove::Reset();
	LevelMove::MoveDown();
	LevelMove::MoveWait();
    LevelDescription::CalculateAllDescription();
	LevelProperty::SetProperties();
	LevelDescription::CalculateTextInfo();
	LevelProperty::GameobjectConvert();
	LevelProperty::UpdateOverlapProperty();
	LevelUndo::AddBufferToObjectUndo();
	LevelDisplay::UpdateAllObjectTexture();
}

void LevelManager::MoveLeft() {
	LevelMove::Reset();
	LevelMove::MoveLeft();
	LevelMove::MoveWait();
    LevelDescription::CalculateAllDescription();
	LevelProperty::SetProperties();
	LevelDescription::CalculateTextInfo();
	LevelProperty::GameobjectConvert();
	LevelProperty::UpdateOverlapProperty();
	LevelUndo::AddBufferToObjectUndo();
	LevelDisplay::UpdateAllObjectTexture();
}

void LevelManager::MoveRight() {
	LevelMove::Reset();
	LevelMove::MoveRight();
	LevelMove::MoveWait();
    LevelDescription::CalculateAllDescription();
	LevelProperty::SetProperties();
	LevelDescription::CalculateTextInfo();
	LevelProperty::GameobjectConvert();
	LevelProperty::UpdateOverlapProperty();
	LevelUndo::AddBufferToObjectUndo();
	LevelDisplay::UpdateAllObjectTexture();
}

void LevelManager::Show() {
	LevelDisplay::TextureCounterAdd();
	LevelDisplay::Show();
}