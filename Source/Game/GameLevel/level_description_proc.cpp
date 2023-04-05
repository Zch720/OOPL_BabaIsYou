#include "stdafx.h"
#include "level_description_proc.h"
#include "level_data.h"
#include "gameobject_properties_manager.h"

std::vector<DescriptionProc::GameobjectIdPair>
	DescriptionProc::descriptionProps = std::vector<DescriptionProc::GameobjectIdPair>();
DescriptionProc::GameobjectSet
	DescriptionProc::connectedTextObjects = DescriptionProc::GameobjectSet();

std::vector<DescriptionProc::GameobjectIdPair> DescriptionProc::GetDescriptionProps() {
	return descriptionProps;
}
DescriptionProc::GameobjectSet DescriptionProc::GetConnectedTextObjects() {
	return connectedTextObjects;
}

void DescriptionProc::Clear() {
	descriptionProps.clear();
	connectedTextObjects.clear();
}
void DescriptionProc::GetAllDescription() {
	descriptionProps.clear();
	checkOperatorIs();
}
void DescriptionProc::UpdatePropFromDescription() {
	GetAllDescription();
}

Gameobject* DescriptionProc::getNounTextInBlock(Point position) {
	for (Gameobject *gameobject : LevelData::gameboard[position]) {
		if (IsNounTextObject(gameobject->gameobjectId)) {
			return gameobject;
		}
	}
	return nullptr;
}
Gameobject* DescriptionProc::getPropTextInBlock(Point position) {
	for (Gameobject *gameobject : LevelData::gameboard[position]) {
		if (IsPropTextObject(gameobject->gameobjectId)) {
			return gameobject;
		}
	}
	return nullptr;
}
void DescriptionProc::checkOperatorIs() {
	for (auto &col : LevelData::gameboard) {
		for (Block &block : col) {
			for (Gameobject *gameobject : block) {
				if (gameobject->gameobjectId == GAMEOBJECT_TEXT_IS) {
					checkOperatorIsHorizontal(gameobject);
					checkOperatorIsVertical(gameobject);
				}
			}
		}
	}
}
void DescriptionProc::checkOperatorIsHorizontal(Gameobject *gameobject) {
	Point position = gameobject->gameBoardPosition;

	if (position.x == 0 || position.x == LevelData::gameboardWidth - 1) return;

	Gameobject *mainNoun = getNounTextInBlock(position.Left());
	Gameobject *subNoun = getNounTextInBlock(position.Right());
	Gameobject *prop = getPropTextInBlock(position.Right());

	if (mainNoun && subNoun) {
		descriptionProps.push_back(std::make_pair(mainNoun->gameobjectId, subNoun->gameobjectId));
		connectedTextObjects.insert(gameobject);
		connectedTextObjects.insert(mainNoun);
		connectedTextObjects.insert(subNoun);
	}
	if (mainNoun && prop) {
		descriptionProps.push_back(std::make_pair(mainNoun->gameobjectId, prop->gameobjectId));
		connectedTextObjects.insert(gameobject);
		connectedTextObjects.insert(mainNoun);
		connectedTextObjects.insert(prop);
	}
}
void DescriptionProc::checkOperatorIsVertical(Gameobject *gameobject) {
	Point position = gameobject->gameBoardPosition;

	if (position.y == 0 || position.y == LevelData::gameboardHeight - 1) return;

	Gameobject *mainNoun = getNounTextInBlock(position.Up());
	Gameobject *subNoun = getNounTextInBlock(position.Down());
	Gameobject *prop = getPropTextInBlock(position.Down());

	if (mainNoun && subNoun) {
		descriptionProps.push_back(std::make_pair(mainNoun->gameobjectId, subNoun->gameobjectId));
		connectedTextObjects.insert(gameobject);
		connectedTextObjects.insert(mainNoun);
		connectedTextObjects.insert(subNoun);
	}
	if (mainNoun && prop) {
		descriptionProps.push_back(std::make_pair(mainNoun->gameobjectId, prop->gameobjectId));
		connectedTextObjects.insert(gameobject);
		connectedTextObjects.insert(mainNoun);
		connectedTextObjects.insert(prop);
	}
}