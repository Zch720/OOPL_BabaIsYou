#include "stdafx.h"
#include "level_description_proc.h"
#include "level_data.h"
#include "level_gameboard_proc.h"
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

	//Gameobject *mainNoun = getNounTextInBlock(position.Left());
	//Gameobject *subNoun = getNounTextInBlock(position.Right());
	//Gameobject *prop = getPropTextInBlock(position.Right());
	std::unordered_map<Gameobject*, bool> mainObjects = checkMainObjectHorizontal(position.Left());
	std::unordered_map<Gameobject*, bool> subObjects = checkSubObjectHorizontal(position.Right());

	//if (mainNoun && subNoun) {
	//	descriptionProps.push_back(std::make_pair(mainNoun->gameobjectId, subNoun->gameobjectId));
	//	connectedTextObjects.insert(gameobject);
	//	connectedTextObjects.insert(mainNoun);
	//	connectedTextObjects.insert(subNoun);
	//}
	//if (mainNoun && prop) {
	//	descriptionProps.push_back(std::make_pair(mainNoun->gameobjectId, prop->gameobjectId));
	//	connectedTextObjects.insert(gameobject);
	//	connectedTextObjects.insert(mainNoun);
	//	connectedTextObjects.insert(prop);
	//}
	if (!mainObjects.empty() && !subObjects.empty()) {
		connectedTextObjects.insert(gameobject);
		for (auto object : mainObjects) {
			connectedTextObjects.insert(object.first);
		}
		for (auto object : subObjects) {
			connectedTextObjects.insert(object.first);
		}
	}

	for (auto mainObject : mainObjects) {
		for (auto subObject : subObjects) {
			bool mainObjectIsOperator = IsOperatorTextObject(mainObject.first->gameobjectId);
			bool subObjectIsOperator = IsOperatorTextObject(subObject.first->gameobjectId);
			if (!mainObjectIsOperator && !subObjectIsOperator) {
				descriptionProps.push_back(
					std::make_pair(mainObject.first->gameobjectId, subObject.first->gameobjectId)
				);
			}
		}
	}
}
void DescriptionProc::checkOperatorIsVertical(Gameobject *gameobject) {
	Point position = gameobject->gameBoardPosition;

	if (position.y == 0 || position.y == LevelData::gameboardHeight - 1) return;

	//Gameobject *mainNoun = getNounTextInBlock(position.Up());
	//Gameobject *subNoun = getNounTextInBlock(position.Down());
	//Gameobject *prop = getPropTextInBlock(position.Down());
	std::unordered_map<Gameobject*, bool> mainObjects = checkMainObjectVertical(position.Left());
	std::unordered_map<Gameobject*, bool> subObjects = checkSubObjectVertical(position.Right());

	//if (mainNoun && subNoun) {
	//	descriptionProps.push_back(std::make_pair(mainNoun->gameobjectId, subNoun->gameobjectId));
	//	connectedTextObjects.insert(gameobject);
	//	connectedTextObjects.insert(mainNoun);
	//	connectedTextObjects.insert(subNoun);
	//}
	//if (mainNoun && prop) {
	//	descriptionProps.push_back(std::make_pair(mainNoun->gameobjectId, prop->gameobjectId));
	//	connectedTextObjects.insert(gameobject);
	//	connectedTextObjects.insert(mainNoun);
	//	connectedTextObjects.insert(prop);
	//}
	if (!mainObjects.empty() && !subObjects.empty()) {
		connectedTextObjects.insert(gameobject);
		for (auto object : mainObjects) {
			connectedTextObjects.insert(object.first);
		}
		for (auto object : subObjects) {
			connectedTextObjects.insert(object.first);
		}
	}

	for (auto mainObject : mainObjects) {
		for (auto subObject : subObjects) {
			bool mainObjectIsOperator = IsOperatorTextObject(mainObject.first->gameobjectId);
			bool subObjectIsOperator = IsOperatorTextObject(subObject.first->gameobjectId);
			if (!mainObjectIsOperator && !subObjectIsOperator) {
				descriptionProps.push_back(
					std::make_pair(mainObject.first->gameobjectId, subObject.first->gameobjectId)
				);
			}
		}
	}
}
std::unordered_map<Gameobject*, bool> DescriptionProc::checkMainObjectHorizontal(Point position) {
	std::unordered_map<Gameobject*, bool> result;
	Gameobject *nounObject = getNounTextInBlock(position);

	if (!nounObject) {
		return result;
	}

	Gameobject *operatorAnd = nullptr;
	if (position.x > 1) {
		operatorAnd = GameboardProc::FindGameobjectByIdInBlock(position.Left(), GAMEOBJECT_TEXT_AND);
	}
	if (operatorAnd) {
		size_t resultSize = result.size();
		result = checkMainObjectHorizontal(position.Offset(-2, 0));
		if (resultSize != result.size()) {
			result[operatorAnd] = false;
		}
	}
	result[nounObject] = true;
	return result;
}
std::unordered_map<Gameobject*, bool> DescriptionProc::checkSubObjectHorizontal(Point position) {
	std::unordered_map<Gameobject*, bool> result;
	Gameobject *nounObject = getNounTextInBlock(position);
	Gameobject *propObject = getPropTextInBlock(position);

	if (!nounObject && !propObject) {
		return result;
	}
	
	Gameobject *operatorAnd = nullptr;
	if (position.x < LevelData::gameboardWidth - 2) {
		operatorAnd = GameboardProc::FindGameobjectByIdInBlock(position.Right(), GAMEOBJECT_TEXT_AND);
	}
	if (operatorAnd) {
		size_t resultSize = result.size();
		result = checkSubObjectHorizontal(position.Offset(2, 0));
		if (resultSize != result.size()) {
			result[operatorAnd] = false;
		}
	}
	if (nounObject) {
		result[nounObject] = true;
	}
	else if (propObject) {
		result[propObject] = true;
	}

	return result;
}
std::unordered_map<Gameobject*, bool> DescriptionProc::checkMainObjectVertical(Point position) {
	std::unordered_map<Gameobject*, bool> result;
	Gameobject *nounObject = getNounTextInBlock(position);

	if (!nounObject) {
		return result;
	}
	
	Gameobject *operatorAnd = nullptr;
	if (position.y > 1) {
		operatorAnd = GameboardProc::FindGameobjectByIdInBlock(position.Up(), GAMEOBJECT_TEXT_AND);
	}
	if (operatorAnd) {
		size_t resultSize = result.size();
		result = checkMainObjectVertical(position.Offset(0, -2));
		if (resultSize != result.size()) {
			result[operatorAnd] = false;
		}
	}
	result[nounObject] = true;
	return result;
}
std::unordered_map<Gameobject*, bool> DescriptionProc::checkSubObjectVertical(Point position) {
	std::unordered_map<Gameobject*, bool> result;
	Gameobject *nounObject = getNounTextInBlock(position);
	Gameobject *propObject = getPropTextInBlock(position);

	if (!nounObject && !propObject) {
		return result;
	}
	
	Gameobject *operatorAnd = nullptr;
	if (position.y < LevelData::gameboardHeight - 2) {
		operatorAnd = GameboardProc::FindGameobjectByIdInBlock(position.Down(), GAMEOBJECT_TEXT_AND);
	}
	if (operatorAnd) {
		size_t resultSize = result.size();
		result = checkSubObjectVertical(position.Offset(0, 2));
		if (resultSize != result.size()) {
			result[operatorAnd] = false;
		}
	}
	if (nounObject) {
		result[nounObject] = true;
	}
	else if (propObject) {
		result[propObject] = true;
	}

	return result;
}