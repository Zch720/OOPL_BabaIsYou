#include "stdafx.h"
#include "level_description_proc.h"
#include "level_data.h"
#include "level_gameboard_proc.h"
#include "gameobject_properties_manager.h"

namespace std {
	template<> struct hash<DescriptionProc::TextObjectInfo> {
		size_t operator()(const DescriptionProc::TextObjectInfo &info) const noexcept {
			return info(info);
		}
	};
}

std::unordered_multimap<GameobjectId, std::vector<DescriptionProc::TextObjectInfo>>
	DescriptionProc::descriptionProps = std::unordered_multimap<GameobjectId, std::vector<DescriptionProc::TextObjectInfo>>();
std::stack<std::unordered_multimap<GameobjectId, std::vector<DescriptionProc::TextObjectInfo>>>
	DescriptionProc::descriptionStack = std::stack<std::unordered_multimap<GameobjectId, std::vector<DescriptionProc::TextObjectInfo>>>();
DescriptionProc::TextObjectInfoSet
	DescriptionProc::connectedTextObjects = DescriptionProc::TextObjectInfoSet();
std::stack<DescriptionProc::TextObjectInfoSet>
	DescriptionProc::connectedTextObjectsStack = std::stack<DescriptionProc::TextObjectInfoSet>();
DescriptionProc::TextObjectInfoSet
	DescriptionProc::usableTextObjects = DescriptionProc::TextObjectInfoSet();
std::stack<DescriptionProc::TextObjectInfoSet>
	DescriptionProc::usableTextObjectsStack = std::stack<DescriptionProc::TextObjectInfoSet>();

bool DescriptionProc::TextObjectInfo::operator==(const TextObjectInfo &other) const {
	return id == other.id && position.x == other.position.x && position.y == other.position.y;
}
bool DescriptionProc::TextObjectInfo::operator<(const TextObjectInfo &other) {
	if (id != other.id) return id < other.id;
	if (position.x != other.position.x) return position.x < other.position.x;
	return position.y < other.position.y;
}

size_t DescriptionProc::TextObjectInfo::operator()(const TextObjectInfo &infoToHash) const {
	return ((uint64_t)infoToHash.id << 32) | ((uint64_t)infoToHash.position.x << 16) | infoToHash.position.y;
}

std::vector<DescriptionProc::GameobjectIdPair> DescriptionProc::GetDescriptionProps() {
	std::vector<DescriptionProc::GameobjectIdPair> result;

	for (auto &prop : descriptionProps) {
		result.push_back(std::make_pair(prop.second[0].id, prop.second[1].id));
	}

	return result;
}
std::unordered_set<Gameobject*> DescriptionProc::GetConnectedTextObjects() {
	std::unordered_set<Gameobject*> result;

	for (TextObjectInfo info : connectedTextObjects) {
		result.insert(GameboardProc::FindGameobjectByIdInBlock(info.position, info.id));
	}

	return result;
}
std::unordered_set<Gameobject*> DescriptionProc::GetUnusableTextObjects() {
	std::unordered_set<Gameobject*> result;

	/*for (TextObjectInfo info : unusableTextObjects) {
		result.insert(GameboardProc::FindGameobjectByIdInBlock(info.position, info.id));
	}*/
	for (TextObjectInfo info : connectedTextObjects) {
		if (usableTextObjects.find(info) == usableTextObjects.end()) {
			result.insert(GameboardProc::FindGameobjectByIdInBlock(info.position, info.id));
		}
	}

	return result;
}

void DescriptionProc::Undo() {
	if (descriptionStack.size() < 2) return;
	descriptionProps = descriptionStack.top();
	descriptionStack.pop();
	connectedTextObjects = connectedTextObjectsStack.top();
	connectedTextObjectsStack.pop();
	usableTextObjects = usableTextObjectsStack.top();
	usableTextObjectsStack.pop();
}

void DescriptionProc::Clear() {
	descriptionProps.clear();
	connectedTextObjects.clear();
	while (!descriptionStack.empty()) {
		descriptionStack.pop();
	}
}
void DescriptionProc::GetAllDescription() {
	descriptionStack.push(descriptionProps);
	connectedTextObjectsStack.push(connectedTextObjects);
	usableTextObjectsStack.push(usableTextObjects);

	descriptionProps.clear();
	connectedTextObjects.clear();
	usableTextObjects.clear();

	checkOperatorIs();

	for (auto it = descriptionProps.begin(); it != descriptionProps.end(); it++) {
		if (IsNounTextObject(it->second[1].id)) {
			GameobjectId preConvertObject = getPreviousDescriptionConvertNoneGameobject(it->first);
			if (preConvertObject == it->second[1].id) {
				usableTextObjects.insert(it->second.begin(), it->second.end());
				continue;
			}
			if (getDescriptionConvertNounGameobjectCount(it->first) != 1) {
				//unusableTextObjects.insert(it->second.begin(), it->second.end());
				it = descriptionProps.erase(it);
				if (it != descriptionProps.begin()) {
					it--;
				}
			} else {
				usableTextObjects.insert(it->second.begin(), it->second.end());
			}
		} else {
			usableTextObjects.insert(it->second.begin(), it->second.end());
		}
	}
}
void DescriptionProc::UpdatePropFromDescription() {
	GetAllDescription();
}

GameobjectId DescriptionProc::getPreviousDescriptionConvertNoneGameobject(GameobjectId gameobjectId) {
	auto gameobjectIdRange = descriptionStack.top().equal_range(gameobjectId);
	for (auto it = gameobjectIdRange.first; it != gameobjectIdRange.second; it++) {
		if (IsNounTextObject(it->second[1].id)) {
			return it->second[1].id;
		}
	}
	return GAMEOBJECT_NONE;
}
int DescriptionProc::getDescriptionConvertNounGameobjectCount(GameobjectId gameobjectId) {
	int result = 0;
	auto gameobjectIdRange = descriptionProps.equal_range(gameobjectId);
	for (auto it = gameobjectIdRange.first; it != gameobjectIdRange.second; it++) {
		if (IsNounTextObject(it->second[1].id)) {
			result++;
		}
	}
	return result;
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
			Gameobject *operatorIs = GameboardProc::FindGameobjectByIdInBlock(block.GetPosition(), GAMEOBJECT_TEXT_IS);
			if (operatorIs) {
				checkOperatorIsHorizontal(operatorIs);
				checkOperatorIsVertical(operatorIs);
			}
		}
	}
}
void DescriptionProc::checkOperatorIsHorizontal(Gameobject *gameobject) {
	Point position = gameobject->gameBoardPosition;

	if (position.x == 0 || position.x == LevelData::gameboardWidth - 1) return;

	std::unordered_map<Gameobject*, bool> mainObjects = checkMainObjectHorizontal(position.Left());
	std::unordered_map<Gameobject*, bool> subObjects = checkSubObjectHorizontal(position.Right());

	if (!mainObjects.empty() && !subObjects.empty()) {
		connectedTextObjects.insert({gameobject->gameobjectId, gameobject->gameBoardPosition});
		for (auto object : mainObjects) {
			connectedTextObjects.insert({object.first->gameobjectId, object.first->gameBoardPosition});
		}
		for (auto object : subObjects) {
			connectedTextObjects.insert({object.first->gameobjectId, object.first->gameBoardPosition});
		}
	}

	std::vector<TextObjectInfo> objects(3);
	for (auto mainObject : mainObjects) {
		for (auto subObject : subObjects) {
			bool mainObjectIsOperator = IsOperatorTextObject(mainObject.first->gameobjectId);
			bool subObjectIsOperator = IsOperatorTextObject(subObject.first->gameobjectId);
			if (!mainObjectIsOperator && !subObjectIsOperator) {
				objects[0] = { mainObject.first->gameobjectId, mainObject.first->gameBoardPosition };
				objects[1] = { subObject.first->gameobjectId, subObject.first->gameBoardPosition };
				objects[2] = { gameobject->gameobjectId, gameobject->gameBoardPosition };
				descriptionProps.insert(std::make_pair(mainObject.first->gameobjectId, objects));
			}
		}
	}
}
void DescriptionProc::checkOperatorIsVertical(Gameobject *gameobject) {
	Point position = gameobject->gameBoardPosition;

	if (position.y == 0 || position.y == LevelData::gameboardHeight - 1) return;

	std::unordered_map<Gameobject*, bool> mainObjects = checkMainObjectVertical(position.Up());
	std::unordered_map<Gameobject*, bool> subObjects = checkSubObjectVertical(position.Down());

	if (!mainObjects.empty() && !subObjects.empty()) {
		connectedTextObjects.insert({ gameobject->gameobjectId, gameobject->gameBoardPosition });
		for (auto object : mainObjects) {
			connectedTextObjects.insert({object.first->gameobjectId, object.first->gameBoardPosition});
		}
		for (auto object : subObjects) {
			connectedTextObjects.insert({object.first->gameobjectId, object.first->gameBoardPosition});
		}
	}
	
	std::vector<TextObjectInfo> objects(3);
	for (auto mainObject : mainObjects) {
		for (auto subObject : subObjects) {
			bool mainObjectIsOperator = IsOperatorTextObject(mainObject.first->gameobjectId);
			bool subObjectIsOperator = IsOperatorTextObject(subObject.first->gameobjectId);
			if (!mainObjectIsOperator && !subObjectIsOperator) {
				objects[0] = { mainObject.first->gameobjectId, mainObject.first->gameBoardPosition };
				objects[1] = { subObject.first->gameobjectId, subObject.first->gameBoardPosition };
				objects[2] = { gameobject->gameobjectId, gameobject->gameBoardPosition };
				descriptionProps.insert(std::make_pair(mainObject.first->gameobjectId, objects));
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