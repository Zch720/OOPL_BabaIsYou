#include "stdafx.h"
#include "block.h"
#include <algorithm>
#include "level_data.h"
#include "gameobject_properties_manager.h"

std::vector<Gameobject*>::iterator Block::begin() {
	return blockObjects.begin();
}
std::vector<Gameobject*>::iterator Block::end() {
	return blockObjects.end();
}

Block::Block(CPoint position) : gameboardPosition(position) {}

size_t Block::GetSize() {
	return blockObjects.size();
}
CPoint Block::GetPosition() {
	return gameboardPosition;
}

Gameobject* Block::operator[](const int index) {
	return blockObjects[index];
}

void Block::clear() {
	for (Gameobject *gameobject : blockObjects) {
		delete gameobject;
	}
	blockObjects.clear();
}

Gameobject* Block::GenGameobject(GameobjectId gameobjectId) {
	Gameobject* gameobject = new Gameobject(gameobjectId, gameboardPosition, LevelData::textureSize);
	blockObjects.push_back(gameobject);
	gameobject->setTextureWithColor(
		LevelData::textureOrigionPosition,
		static_cast<PropId>(GameobjectPropsManager::GetColorProp(gameobjectId))
	);
	sortBlockObjects();
	return gameobject;
}
void Block::DeleteGameobject(Gameobject* gameobject) {
	for (size_t i = 0; i < blockObjects.size(); i++) {
		if (blockObjects[i] == gameobject) {
			delete gameobject;
			blockObjects.erase(blockObjects.begin() + i);
			return;
		}
	}
}
void Block::AddGameobject(Gameobject* gameobject) {
	blockObjects.push_back(gameobject);
	sortBlockObjects();
}
void Block::RemoveGameobject(Gameobject* gameobject) {
	for (size_t i = 0; i < blockObjects.size(); i++) {
		if (blockObjects[i] == gameobject) {
			blockObjects.erase(blockObjects.begin() + i);
			return;
		}
	}
}

bool Block::HasGameobjectId(GameobjectId gameobjectId) {
	for (Gameobject *gameobject : blockObjects) {
		if (gameobject->gameobjectId == gameobjectId) {
			return true;
		}
	}
	return false;
}
Gameobject* Block::FindGameobjectById(GameobjectId gameobjectId) {
	for (auto gameobject = blockObjects.rbegin(); gameobject != blockObjects.rend(); gameobject++) {
		if ((*gameobject)->gameobjectId == gameobjectId) {
			return (*gameobject);
		}
	}
	return nullptr;
}
Gameobject* Block::FindGameobjectByProp(PropId propId) {
	for (Gameobject *gameobject : blockObjects) {
		if (GameobjectPropsManager::GetGameobjectProp(gameobject->gameobjectId, propId)) {
			return gameobject;
		}
	}
	return nullptr;
}

void Block::UpdateGameobjectColor() {

}

void Block::sortBlockObjects() {
	sort(blockObjects.begin(), blockObjects.end(),
		[this](Gameobject* obj1, Gameobject*obj2) {
			bool obj1_textObj = IsTextObject(obj1->gameobjectId);
			bool obj2_textObj = IsTextObject(obj2->gameobjectId);
			if (obj1_textObj ^ obj2_textObj) return obj2_textObj;

			bool obj1_youProp = GameobjectPropsManager::GetGameobjectProp(obj1->gameobjectId, PROP_YOU);
			bool obj2_youProp = GameobjectPropsManager::GetGameobjectProp(obj2->gameobjectId, PROP_YOU);
			if (obj1_youProp ^ obj2_youProp) return obj2_youProp;

			return false;
		}
	);
}