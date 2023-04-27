#include "stdafx.h"
#include "level_description_proc.h"
#include "level_data.h"
#include "level_gameboard_proc.h"
#include "gameobject_properties_manager.h"
#include <algorithm>

// DescriptionProc TextObjectInfo
namespace std {
	template<> struct hash<DescriptionProc::TextObjectInfo> {
		size_t operator()(const DescriptionProc::TextObjectInfo &info) const noexcept {
			return info(info);
		}
	};
}

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
DescriptionProc::TextObjectInfo DescriptionProc::TextObjectInfo::FromGameobjectInfo(const GameobjectInfo &gameobjectInfo) {
	return {gameobjectInfo.id, gameobjectInfo.position};
}


// DescriptionProc DescriptionInfo
DescriptionProc::DescriptionInfo::DescriptionInfo() {
	textObjectInfos = std::vector<TextObjectInfo>(7);
}

void DescriptionProc::DescriptionInfo::SetMainTextObject(TextObjectInfo info) {
	textObjectInfos[MAIN_OBJECT_INDEX] = info;
}
void DescriptionProc::DescriptionInfo::SetSubTextObject(TextObjectInfo info) {
	textObjectInfos[SUB_OBJECT_INDEX] = info;
}
void DescriptionProc::DescriptionInfo::SetCenterConnectTextObject(TextObjectInfo info) {
	textObjectInfos[CENTER_CONNECT_OBJECT_INDEX] = info;
}
void DescriptionProc::DescriptionInfo::SetMainPrefixObject(TextObjectInfo info) {
	textObjectInfos[MAIN_PREFIX_OBJECT_INDEX] = info;
}
void DescriptionProc::DescriptionInfo::SetSubPrefixObject(TextObjectInfo info) {
	textObjectInfos[SUB_PREFIX_OBJECT_INDEX] = info;
}
void DescriptionProc::DescriptionInfo::SetMainConnectObject(TextObjectInfo info) {
	textObjectInfos[MAIN_CONNECT_OBJECT_INDEX] = info;
}
void DescriptionProc::DescriptionInfo::SetSubConnectObject(TextObjectInfo info) {
	textObjectInfos[SUB_CONNECT_OBJECT_INDEX] = info;
}

std::vector<DescriptionProc::TextObjectInfo> DescriptionProc::DescriptionInfo::GetAllObjects() {
	std::vector<TextObjectInfo> result;
	for (TextObjectInfo &info : textObjectInfos) {
		if (info.id == GAMEOBJECT_NONE) continue;
		result.push_back(info);
	}
	return result;
}
DescriptionProc::TextObjectInfo DescriptionProc::DescriptionInfo::GetMainTextObject() {
	return textObjectInfos[MAIN_OBJECT_INDEX];
}
DescriptionProc::TextObjectInfo DescriptionProc::DescriptionInfo::GetSubTextObject() {
	return textObjectInfos[SUB_OBJECT_INDEX];
}
DescriptionProc::TextObjectInfo DescriptionProc::DescriptionInfo::GetCenterConnectTextObject() {
	return textObjectInfos[CENTER_CONNECT_OBJECT_INDEX];
}
DescriptionProc::TextObjectInfo DescriptionProc::DescriptionInfo::GetMainPrefixObject() {
	return textObjectInfos[MAIN_PREFIX_OBJECT_INDEX];
}
DescriptionProc::TextObjectInfo DescriptionProc::DescriptionInfo::GetSubPrefixObject() {
	return textObjectInfos[SUB_PREFIX_OBJECT_INDEX];
}
DescriptionProc::TextObjectInfo DescriptionProc::DescriptionInfo::GetMainConnectObject() {
	return textObjectInfos[MAIN_CONNECT_OBJECT_INDEX];
}
DescriptionProc::TextObjectInfo DescriptionProc::DescriptionInfo::GetSubConnectObject() {
	return textObjectInfos[SUB_CONNECT_OBJECT_INDEX];
}

bool DescriptionProc::DescriptionInfo::IsMainTextObjectUsable() {
	return textObjectInfos[MAIN_OBJECT_INDEX].id != GAMEOBJECT_NONE;
}
bool DescriptionProc::DescriptionInfo::IsSubTextObjectUsable() {
	return textObjectInfos[SUB_OBJECT_INDEX].id != GAMEOBJECT_NONE;
}
bool DescriptionProc::DescriptionInfo::IsCenterConnectTextObjectUsable() {
	return textObjectInfos[CENTER_CONNECT_OBJECT_INDEX].id != GAMEOBJECT_NONE;
}
bool DescriptionProc::DescriptionInfo::IsMainPrefixObjectUsable() {
	return textObjectInfos[MAIN_PREFIX_OBJECT_INDEX].id != GAMEOBJECT_NONE;
}
bool DescriptionProc::DescriptionInfo::IsSubPrefixObjectUsable() {
	return textObjectInfos[SUB_PREFIX_OBJECT_INDEX].id != GAMEOBJECT_NONE;
}
bool DescriptionProc::DescriptionInfo::IsMainConnectObjectUsable() {
	return textObjectInfos[MAIN_CONNECT_OBJECT_INDEX].id != GAMEOBJECT_NONE;
}
bool DescriptionProc::DescriptionInfo::IsSubConnectObjectUsable() {
	return textObjectInfos[SUB_CONNECT_OBJECT_INDEX].id != GAMEOBJECT_NONE;
}

DescriptionProc::DescriptionInfo DescriptionProc::DescriptionInfo::operator+(const DescriptionInfo &other) {
	DescriptionInfo result;
	for (int i = 0; i < 7; i++) {
		if (this->textObjectInfos[i].id == GAMEOBJECT_NONE) {
			result.textObjectInfos[i] = other.textObjectInfos[i];
		} else {
			result.textObjectInfos[i] = this->textObjectInfos[i];
		}
	}
	return result;
}


// DescriptionProc
std::unordered_multimap<GameobjectId, DescriptionProc::DescriptionInfo>
	DescriptionProc::descriptionsBuffer = std::unordered_multimap<GameobjectId, DescriptionProc::DescriptionInfo>();
std::unordered_multimap<GameobjectId, DescriptionProc::DescriptionInfo>
	DescriptionProc::descriptions = std::unordered_multimap<GameobjectId, DescriptionProc::DescriptionInfo>();
std::stack<std::unordered_multimap<GameobjectId, DescriptionProc::DescriptionInfo>>
	DescriptionProc::descriptionsStack = std::stack<std::unordered_multimap<GameobjectId, DescriptionProc::DescriptionInfo>>();
DescriptionProc::TextObjectInfoSet
	DescriptionProc::connectedTextObjects = DescriptionProc::TextObjectInfoSet();

std::vector<DescriptionProc::GameobjectIdPair> DescriptionProc::GetDescriptionProps() {
	std::vector<DescriptionProc::GameobjectIdPair> result;
	for (auto &description : descriptions) {
		result.push_back(std::make_pair(description.second.GetMainTextObject().id, description.second.GetSubTextObject().id));
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
	TextObjectInfoSet usableTextObjects = getUsableTextObjects();
	for (TextObjectInfo info : connectedTextObjects) {
		if (usableTextObjects.find(info) == usableTextObjects.end()) {
			result.insert(GameboardProc::FindGameobjectByIdInBlock(info.position, info.id));
		}
	}
	return result;
}

void DescriptionProc::Undo() {
	if (descriptionsStack.size() < 2) return;
	setUndoBuffers();
	getAllIsDescription();
}

void DescriptionProc::Clear() {
	descriptionsBuffer.clear();
	descriptions.clear();
	while (!descriptionsStack.empty()) {
		descriptionsStack.pop();
	}
	connectedTextObjects.clear();
}
void DescriptionProc::CalculateAllDescription() {
	clearBuffers();
	checkOperatorIs();
}

DescriptionProc::TextObjectInfoSet DescriptionProc::getUsableTextObjects() {
	TextObjectInfoSet result;
	std::vector<TextObjectInfo> descriptionObjectTexts;
	for (auto &description : descriptions) {
		descriptionObjectTexts = description.second.GetAllObjects();
		result.insert(descriptionObjectTexts.begin(), descriptionObjectTexts.end());
	}
	return result;
}

void DescriptionProc::clearBuffers() {
	descriptionsBuffer.clear();
	descriptionsStack.push(descriptions);
	descriptions.clear();
	connectedTextObjects.clear();
}
void DescriptionProc::setUndoBuffers() {
	descriptions = descriptionsStack.top();
	descriptionsStack.pop();
	descriptionsBuffer.clear();
	connectedTextObjects.clear();
}

GameobjectId DescriptionProc::getPreviousDescriptionConvertNoneGameobject(GameobjectId gameobjectId) {
	GameobjectId result = GAMEOBJECT_NONE;
	auto gameobjectIdRange = descriptionsStack.top().equal_range(gameobjectId);
	for (auto descriptionData = gameobjectIdRange.first; descriptionData != gameobjectIdRange.second; descriptionData++) {
		if (IsNounTextObject(descriptionData->second.GetSubTextObject().id))
			result = descriptionData->second.GetSubTextObject().id;
	}
	return result;
}
int DescriptionProc::getDescriptionConvertNounGameobjectCount(GameobjectId gameobjectId) {
	int result = 0;
	auto gameobjectIdRange = descriptionsBuffer.equal_range(gameobjectId);
	for (auto descriptionData = gameobjectIdRange.first; descriptionData != gameobjectIdRange.second; descriptionData++) {
		if (IsNounTextObject(descriptionData->second.GetSubTextObject().id)) result++;
	}
	return result;
}

DescriptionProc::TextObjectInfo DescriptionProc::getNounTextInBlock(Point position) {
	for (Gameobject *gameobject : LevelData::Gameboard[position]) {
		if (IsNounTextObject(gameobject->GetInfo().id)) {
			return TextObjectInfo::FromGameobjectInfo(gameobject->GetInfo());
		}
	}
	return {};
}
DescriptionProc::TextObjectInfo DescriptionProc::getPropTextInBlock(Point position) {
	for (Gameobject *gameobject : LevelData::Gameboard[position]) {
		if (IsPropTextObject(gameobject->GetInfo().id)) {
			return TextObjectInfo::FromGameobjectInfo(gameobject->GetInfo());
		}
	}
	return {};
}
void DescriptionProc::checkOperatorIs() {
	getAllIsDescription();
	for (auto &description : descriptionsBuffer) {
		if (checkOperatorIsUsable(description.second)) {
			descriptions.insert(description);
		}
	}
}
void DescriptionProc::getAllIsDescription() {
	LevelData::Gameboard.foreach([](Block &block) {
		Gameobject *operatorIs = block.FindGameobjectById(GAMEOBJECT_TEXT_IS);
		if (operatorIs) {
			checkOperatorIsHorizontal(TextObjectInfo{ GAMEOBJECT_TEXT_IS, block.GetPosition() });
			checkOperatorIsVertical(TextObjectInfo{ GAMEOBJECT_TEXT_IS, block.GetPosition() });
		}
	});
}
bool DescriptionProc::isPreConvertObject(GameobjectId origin, GameobjectId convert) {
	GameobjectId preConvertObject = getPreviousDescriptionConvertNoneGameobject(origin);
	return preConvertObject == convert;
}
bool DescriptionProc::onlyHasOneConvertObject(GameobjectId gameobjectId) {
	return getDescriptionConvertNounGameobjectCount(gameobjectId) == 1;
}
bool DescriptionProc::checkGameobjectCanConvert(GameobjectId origin, GameobjectId convert) {
	return onlyHasOneConvertObject(origin) || isPreConvertObject(origin, convert);
}
bool DescriptionProc::checkOperatorIsUsable(DescriptionInfo &info) {
	if (IsNounTextObject(info.GetSubTextObject().id)) {
		if (!checkGameobjectCanConvert(info.GetMainTextObject().id, info.GetSubTextObject().id)) {
			return false;
		}
	}
	return true;
}
void DescriptionProc::addDescriptionIsToConnectedTextObjects(DescriptionInfoGroup &mainObjects, TextObjectInfo &centerObject, DescriptionInfoGroup &subObjects) {
	if (mainObjects.empty() || subObjects.empty()) return;
	connectedTextObjects.insert(centerObject);
	std::vector<TextObjectInfo> textObjects;
	auto addToConnectedObjects = [&](DescriptionInfo &info) {
		textObjects = info.GetAllObjects();
		connectedTextObjects.insert(textObjects.begin(), textObjects.end());
	};
	std::for_each(mainObjects.begin(), mainObjects.end(), addToConnectedObjects);
	std::for_each(subObjects.begin(), subObjects.end(), addToConnectedObjects);
}
void DescriptionProc::getDescriptionIs(DescriptionInfoGroup &mainObjects, TextObjectInfo &centerObject, DescriptionInfoGroup &subObjects) {
	DescriptionInfo descriptionInfo;
	for (auto mainObject : mainObjects) {
		for (auto subObject : subObjects) {
			descriptionInfo = mainObject + subObject;
			descriptionInfo.SetCenterConnectTextObject(centerObject);
			descriptionsBuffer.insert(std::make_pair(descriptionInfo.GetMainTextObject().id, descriptionInfo));
		}
	}
}
void DescriptionProc::checkOperatorIsHorizontal(TextObjectInfo &isTextObject) {
	DescriptionInfoGroup mainObjects = getHorizontalMainObjects(isTextObject.position.Left());
	DescriptionInfoGroup subObjects = getHorizontalSubObjects(isTextObject.position.Right());
	addDescriptionIsToConnectedTextObjects(mainObjects, isTextObject, subObjects);
	getDescriptionIs(mainObjects, isTextObject, subObjects);
}
void DescriptionProc::checkOperatorIsVertical(TextObjectInfo &isTextObject) {
	DescriptionInfoGroup mainObjects = getVerticalMainObjects(isTextObject.position.Up());
	DescriptionInfoGroup subObjects = getVerticalSubObjects(isTextObject.position.Down());
	addDescriptionIsToConnectedTextObjects(mainObjects, isTextObject, subObjects);
	getDescriptionIs(mainObjects, isTextObject, subObjects);
}

bool DescriptionProc::blockUsable(Point position) {
	return LevelData::IsPointInGameboard(position) && LevelData::Gameboard[position].HasTextGameobject();
}

bool DescriptionProc::addMainTextObject(DescriptionInfoGroup &result, Point position) {
	TextObjectInfo nounObject = getNounTextInBlock(position);
	DescriptionInfo info;
	if (nounObject.id != GAMEOBJECT_NONE) {
		info.SetMainTextObject(nounObject);
		result.push_back(info);
	}
	return nounObject.id != GAMEOBJECT_NONE;
}
bool DescriptionProc::addSubTextObject(DescriptionInfoGroup &result, Point position) {
	TextObjectInfo nounObject = getNounTextInBlock(position);
	TextObjectInfo propObject = getPropTextInBlock(position);
	DescriptionInfo info;
	if (nounObject.id != GAMEOBJECT_NONE) {
		info.SetSubTextObject(nounObject);
		result.push_back(info);
	}
	else if (propObject.id != GAMEOBJECT_NONE) {
		info.SetSubTextObject(propObject);
		result.push_back(info);
	}
	return nounObject.id != GAMEOBJECT_NONE || propObject.id != GAMEOBJECT_NONE;
}
bool DescriptionProc::addAndMainTextObject(DescriptionInfo &info, Point position) {
	Gameobject *operatorAnd = GameboardProc::FindGameobjectByIdInBlock(position, GAMEOBJECT_TEXT_AND);
	if (operatorAnd) {
		info.SetMainConnectObject(TextObjectInfo::FromGameobjectInfo(operatorAnd->GetInfo()));
	}
	return operatorAnd != nullptr;
}
bool DescriptionProc::addAndSubTextObject(DescriptionInfo &info, Point position) {
	Gameobject *operatorAnd = GameboardProc::FindGameobjectByIdInBlock(position, GAMEOBJECT_TEXT_AND);
	if (operatorAnd) {
		info.SetSubConnectObject(TextObjectInfo::FromGameobjectInfo(operatorAnd->GetInfo()));
	}
	return operatorAnd != nullptr;
}

DescriptionProc::DescriptionInfoGroup DescriptionProc::getHorizontalMainObjects(Point position) {
	if (!blockUsable(position)) return DescriptionInfoGroup();
	DescriptionInfoGroup result = getAndHorizontalMainObjects(position.Left());
	if (!addMainTextObject(result, position)) return DescriptionInfoGroup();
	return result;
}
DescriptionProc::DescriptionInfoGroup DescriptionProc::getAndHorizontalMainObjects(Point position) {
	if (!blockUsable(position)) return DescriptionInfoGroup();
	DescriptionInfoGroup result = getHorizontalMainObjects(position.Left());
	if (result.empty() || !addAndSubTextObject(*(result.end() - 1), position)) return DescriptionInfoGroup();
	return result;
}

DescriptionProc::DescriptionInfoGroup DescriptionProc::getHorizontalSubObjects(Point position) {
	if (!blockUsable(position)) return DescriptionInfoGroup();
	DescriptionInfoGroup result = getAndHorizontalSubObjects(position.Right());
	if (!addSubTextObject(result, position)) return DescriptionInfoGroup();
	return result;
}
DescriptionProc::DescriptionInfoGroup DescriptionProc::getAndHorizontalSubObjects(Point position) {
	if (!blockUsable(position)) return DescriptionInfoGroup();
	DescriptionInfoGroup result = getHorizontalSubObjects(position.Right());
	if (result.empty() || !addAndSubTextObject(*(result.end() - 1), position)) return DescriptionInfoGroup();
	return result;
}

DescriptionProc::DescriptionInfoGroup DescriptionProc::getVerticalMainObjects(Point position) {
	if (!blockUsable(position)) return DescriptionInfoGroup();
	DescriptionInfoGroup result = getAndVerticalMainObjects(position.Up());
	if (!addMainTextObject(result, position)) return DescriptionInfoGroup();
	return result;
}
DescriptionProc::DescriptionInfoGroup DescriptionProc::getAndVerticalMainObjects(Point position) {
	if (!blockUsable(position)) return DescriptionInfoGroup();
	DescriptionInfoGroup result = getVerticalMainObjects(position.Up());
	if (result.empty() || !addAndSubTextObject(*(result.end() - 1), position)) return DescriptionInfoGroup();
	return result;
}

DescriptionProc::DescriptionInfoGroup DescriptionProc::getVerticalSubObjects(Point position) {
	if (!blockUsable(position)) return DescriptionInfoGroup();
	DescriptionInfoGroup result = getAndVerticalSubObjects(position.Down());
	if (!addSubTextObject(result, position)) return DescriptionInfoGroup();
	return result;
}
DescriptionProc::DescriptionInfoGroup DescriptionProc::getAndVerticalSubObjects(Point position) {
	if (!blockUsable(position)) return DescriptionInfoGroup();
	DescriptionInfoGroup result = getVerticalSubObjects(position.Down());
	if (result.empty() || !addAndSubTextObject(*(result.end() - 1), position)) return DescriptionInfoGroup();
	return result;
}