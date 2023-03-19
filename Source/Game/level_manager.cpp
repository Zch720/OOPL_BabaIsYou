#include "stdafx.h"
#include "level_manager.h"
#include <sstream>
#include "../Expansion/dataio.h"
#include "../Expansion/log.h"

std::vector<std::string> stringSplit(const std::string& str, char delim) {
	std::vector<std::string> tokens;
	std::stringstream ss(str);
	std::string token;

	while (std::getline(ss, token, delim)) {
		tokens.push_back(token);
	}

	return tokens;
}
std::string intToString(int number) {
	std::ostringstream oss;
	oss << number;
	return oss.str();
}
int stringToInt(const std::string& str) {
	std::istringstream iss(str);
	int number;
	iss >> number;
	return number;
}

void LevelManager::LoadLevel(int level) {
	std::string levelSource = loadFile("./resources/test/level/" + intToString(level));
	if (levelSource == "") {
		char message[125];
		sprintf_s(message, "Can't load level %d source file", level);
		logError(message);
	}

	std::vector<std::string> levelSourceLines = stringSplit(levelSource, '\n');
	std::vector<GameobjectInfo> gameobjectInfos;

	clearLevel();

	size_t linesCount = 0;

	if (levelSourceLines[linesCount++] != "[game board size]") {
		logError("level file format wrong!");
	}
	gameBoardWidth = stringToInt(levelSourceLines[linesCount++]);
	gameBoardHeight = stringToInt(levelSourceLines[linesCount++]);

	if (levelSourceLines[linesCount++] != "[texture origin position]") {
		logError("level file format wrong!");
	}
	textureOriginPosition.x = stringToInt(levelSourceLines[linesCount++]);
	textureOriginPosition.y = stringToInt(levelSourceLines[linesCount++]);

	if (levelSourceLines[linesCount++] != "[texture size]") {
		logError("level file format wrong!");
	}
	textureSize = stringToInt(levelSourceLines[linesCount++]);

	if (levelSourceLines[linesCount++] != "[props]") {
		logError("level file format wrong!");
	}
	for (; levelSourceLines[linesCount][0] != '['; linesCount++) {
		std::vector<std::string> prop = stringSplit(levelSourceLines[linesCount], ' ');
		GameobjectId gameobjectId = static_cast<GameobjectId>(GetGameobjectIdByName(prop[0]));
		PropId propId = static_cast<PropId>(GetPropIdByName(prop[1]));
		defaultProps.push_back(make_pair(gameobjectId, propId));
	}

	if (levelSourceLines[linesCount++] != "[objects]") {
		logError("level file format wrong!");
	}
	for (; linesCount < levelSourceLines.size(); linesCount++) {
		std::vector<std::string> object = stringSplit(levelSourceLines[linesCount], ' ');
		GameobjectInfo info = {};
		info.gameobjectId = static_cast<GameobjectId>(GetGameobjectIdByName(object[0]));
		info.position = CPoint(stringToInt(object[1]), stringToInt(object[2]));
		gameobjectInfos.push_back(info);
	}
	
	createGameBoard(gameobjectInfos);
	createMoveableRecord();

	updateProps();

	reachWinObj = false;
}

void LevelManager::MoveUp() {
	if (reachWinObj) return;

	findAllYouObjects();
	resetMoveableRecord();

	waitToMoveObjects.clear();
	for (Gameobject *gameobject : hasYouPropObjects) {
		if (checkMoveUp(gameobject->gameBoardPosition - CPoint(0, 1))) {
			waitToMoveObjects.insert(gameobject);
		}
	}

	undoBuffer.clear();
	UndoInfo undoInfo = {};
	for (Gameobject *gameobject : waitToMoveObjects) {
		undoInfo.gameobject = gameobject;
		undoInfo.position = gameobject->gameBoardPosition;
		undoInfo.undoType = UNDO_UP;
		undoBuffer.push_back(undoInfo);
		deleteGameobject(gameobject->gameBoardPosition, gameobject);
		gameobject->moveUp();
		addGameobject(gameobject->gameBoardPosition, gameobject);
	}

	updateProps();
	checkAllOverlapProp();

	if (undoBuffer.size() != 0)
		undoStack.push(undoBuffer);
}

void LevelManager::MoveDown() {
	if (reachWinObj) return;

	findAllYouObjects();
	resetMoveableRecord();

	waitToMoveObjects.clear();
	for (Gameobject *gameobject : hasYouPropObjects) {
		if (checkMoveDown(gameobject->gameBoardPosition + CPoint(0, 1))) {
			waitToMoveObjects.insert(gameobject);
		}
	}

	undoBuffer.clear();
	UndoInfo undoInfo = {};
	for (Gameobject *gameobject : waitToMoveObjects) {
		undoInfo.gameobject = gameobject;
		undoInfo.position = gameobject->gameBoardPosition;
		undoInfo.undoType = UNDO_DOWN;
		undoBuffer.push_back(undoInfo);
		deleteGameobject(gameobject->gameBoardPosition, gameobject);
		gameobject->moveDown();
		addGameobject(gameobject->gameBoardPosition, gameobject);
	}

	updateProps();
	checkAllOverlapProp();

	if (undoBuffer.size() != 0)
		undoStack.push(undoBuffer);
}

void LevelManager::MoveLeft() {
	if (reachWinObj) return;

	findAllYouObjects();
	resetMoveableRecord();

	waitToMoveObjects.clear();
	for (Gameobject *gameobject : hasYouPropObjects) {
		if (checkMoveLeft(gameobject->gameBoardPosition - CPoint(1, 0))) {
			waitToMoveObjects.insert(gameobject);
		}
	}

	undoBuffer.clear();
	UndoInfo undoInfo = {};
	for (Gameobject *gameobject : waitToMoveObjects) {
		undoInfo.gameobject = gameobject;
		undoInfo.position = gameobject->gameBoardPosition;
		undoInfo.undoType = UNDO_LEFT;
		undoBuffer.push_back(undoInfo);
		deleteGameobject(gameobject->gameBoardPosition, gameobject);
		gameobject->moveLeft();
		addGameobject(gameobject->gameBoardPosition, gameobject);
	}

	updateProps();
	checkAllOverlapProp();

	if (undoBuffer.size() != 0)
		undoStack.push(undoBuffer);
}

void LevelManager::MoveRight() {
	if (reachWinObj) return;

	findAllYouObjects();
	resetMoveableRecord();

	waitToMoveObjects.clear();
	for (Gameobject *gameobject : hasYouPropObjects) {
		if (checkMoveRight(gameobject->gameBoardPosition + CPoint(1, 0))) {
			waitToMoveObjects.insert(gameobject);
		}
	}

	undoBuffer.clear();
	UndoInfo undoInfo = {};
	for (Gameobject *gameobject : waitToMoveObjects) {
		undoInfo.gameobject = gameobject;
		undoInfo.position = gameobject->gameBoardPosition;
		undoInfo.undoType = UNDO_RIGHT;
		undoBuffer.push_back(undoInfo);
		deleteGameobject(gameobject->gameBoardPosition, gameobject);
		gameobject->moveRight();
		addGameobject(gameobject->gameBoardPosition, gameobject);
	}

	updateProps();
	checkAllOverlapProp();

	if (undoBuffer.size() != 0)
		undoStack.push(undoBuffer);
}

void LevelManager::Undo() {
	if (undoStack.empty()) return;

	std::vector<UndoInfo> infos = undoStack.top();
	undoStack.pop();

	for (UndoInfo &info : infos) {
		if (info.undoType == UNDO_UP) {
			deleteGameobject(info.gameobject->gameBoardPosition, info.gameobject);
			addGameobject(info.position, info.gameobject);
			info.gameobject->undoUp();
		}
		else if (info.undoType == UNDO_DOWN) {
			deleteGameobject(info.gameobject->gameBoardPosition, info.gameobject);
			addGameobject(info.position, info.gameobject);
			info.gameobject->undoDown();
		}
		else if (info.undoType == UNDO_LEFT) {
			deleteGameobject(info.gameobject->gameBoardPosition, info.gameobject);
			addGameobject(info.position, info.gameobject);
			info.gameobject->undoLeft();
		}
		else if (info.undoType == UNDO_RIGHT) {
			deleteGameobject(info.gameobject->gameBoardPosition, info.gameobject);
			addGameobject(info.position, info.gameobject);
			info.gameobject->undoRight();
		}
		else if (info.undoType == UNDO_DELETE) {
			genGameobject(info.position, info.gameobjectId);
		}
		else if (info.undoType == UNDO_ADD) {
			deleteGameobject(info.position, info.gameobject);
			delete info.gameobject;
		}
	}
}

bool LevelManager::IsMoving() {
	for (auto &row : gameBoard) {
		for (auto &block : row) {
			for (Gameobject *gameobject : block) {
				if (gameobject->remainStep != 0 || gameobject->undoRemainStep != 0) return true;
			}
		}
	}
	return false;
}

bool LevelManager::IsWin() {
	return reachWinObj;
}

void LevelManager::Show() {
	for (auto &row : gameBoard) {
		for (auto &block : row) {
			for (Gameobject *gameobject : block) {
				gameobject->Show();
			}
		}
	}
}

void LevelManager::clearLevel() {
	for (auto &row : gameBoard) {
		for (auto &block : row) {
			for (Gameobject *gameobject : block) {
				delete gameobject;
			}
			block.clear();
		}
		row.clear();
	}
	gameBoard.clear();

	for (auto &row : moveableRecord) {
		row.clear();
	}
	moveableRecord.clear();

	defaultProps.clear();
}

void LevelManager::createGameBoard(std::vector<GameobjectInfo> gameobjectInfos) {
	for (int i = 0; i < gameBoardHeight; i++) {
		std::vector<std::vector<Gameobject*>> row;
		for (int j = 0; j < gameBoardWidth; j++) {
			row.push_back(std::vector<Gameobject*>());
		}
		gameBoard.push_back(row);
	}

	for (GameobjectInfo &info : gameobjectInfos) {
		gameBoard[info.position.x][info.position.y].push_back(
			new Gameobject(info.gameobjectId, info.position, textureOriginPosition, textureSize)
		);
	}
}

void LevelManager::createMoveableRecord() {
	for (int i = 0; i < gameBoardHeight; i++) {
		moveableRecord.push_back(std::vector<int>(gameBoardWidth, 0));
	}
}

void LevelManager::resetMoveableRecord() {
	for (auto &row : moveableRecord) {
		for (int &val : row) {
			val = -1;
		}
	}
}

bool LevelManager::checkObjectsInBlockHasProp(CPoint position, PropId propId) {
	for (Gameobject *gameobject : gameBoard[position.x][position.y]) {
		if (propsManager.GetGameobjectProp(gameobject->gameobjectId, propId)) {
			return true;
		}
	}
	return false;
}

void LevelManager::setPropsManager() {
	propsManager.ClearProperties();

	for (auto &prop : defaultProps) {
		propsManager.SetGameobjectProp(prop.first, prop.second);
	}

	for (auto &prop : additionProps) {
		int gameobjectId = GetGameobjectByTextObject(prop.first);
		int propId = GetPropIdFromTextGameobject(prop.second);
		if (propId == -1) {
			int convertGameobjectId = GetGameobjectByTextObject(prop.second);
			replaceGameobject(static_cast<GameobjectId>(gameobjectId), static_cast<GameobjectId>(convertGameobjectId));
		}
		else {
			propsManager.SetGameobjectProp(static_cast<GameobjectId>(gameobjectId), static_cast<PropId>(propId));
		}
	}

	propsManager.SetPropWithOtherProp(PROP_YOU, PROP_PUSH);
}

void LevelManager::deleteGameobject(CPoint position, Gameobject* deleteGameobject) {
	std::vector<Gameobject*> &block = gameBoard[position.x][position.y];
	for (size_t i = 0; i < block.size(); i++) {
		if (block[i] == deleteGameobject) {
			block.erase(block.begin() + i);
			return;
		}
	}
}

void LevelManager::addGameobject(CPoint position, Gameobject* gameobject) {
	gameBoard[position.x][position.y].push_back(gameobject);
}

void LevelManager::genGameobject(CPoint position, GameobjectId gameobjectId) {
	gameBoard[position.x][position.y].push_back(
		new Gameobject(gameobjectId, position, textureOriginPosition, textureSize)
	);
}

void LevelManager::findAllYouObjects() {
	hasYouPropObjects.clear();

	for (auto &row : gameBoard) {
		for (auto &block : row) {
			for (Gameobject *gameobject : block) {
				if (propsManager.GetGameobjectProp(gameobject->gameobjectId, PROP_YOU)) {
					hasYouPropObjects.insert(gameobject);
				}
			}
		}
	}
}

bool LevelManager::checkBlockMoveObjects(CPoint position, bool aheadBlockMoveable) {
	std::unordered_set<Gameobject*> moveableObjectInBlock;

	for (Gameobject *gameobject : gameBoard[position.x][position.y]) {
		bool pushFlag = propsManager.GetGameobjectProp(gameobject->gameobjectId, PROP_PUSH);
		bool stopFlag = propsManager.GetGameobjectProp(gameobject->gameobjectId, PROP_STOP);

		if (stopFlag) {
			return moveableRecord[position.x][position.y] = 0;
		}
		if (pushFlag) {
			if (!aheadBlockMoveable)
				return moveableRecord[position.x][position.y] = 0;
			moveableObjectInBlock.insert(gameobject);
		}
	}
	waitToMoveObjects.insert(moveableObjectInBlock.begin(), moveableObjectInBlock.end());
	return moveableRecord[position.x][position.y] = 1;
}

bool LevelManager::checkMoveUp(CPoint position) {
	if (position.y == -1) return false;
	if (moveableRecord[position.x][position.y] != -1)
		return moveableRecord[position.x][position.y];

	bool hasStopProp = checkObjectsInBlockHasProp(position, PROP_STOP);
	if (hasStopProp)
		return moveableRecord[position.x][position.y] = 0;

	bool hasYouProp = checkObjectsInBlockHasProp(position, PROP_YOU);
	bool hasPushProp = checkObjectsInBlockHasProp(position, PROP_PUSH);
	if (!hasYouProp && !hasPushProp)
		return moveableRecord[position.x][position.y] = 1;

	bool aheadBlockMoveable = checkMoveUp(position - CPoint(0, 1));
	moveableRecord[position.x][position.y] = checkBlockMoveObjects(position, aheadBlockMoveable);
	return moveableRecord[position.x][position.y];
}

bool LevelManager::checkMoveDown(CPoint position) {
	if (position.y == gameBoardHeight) return false;
	if (moveableRecord[position.x][position.y] != -1)
		return moveableRecord[position.x][position.y];

	bool hasStopProp = checkObjectsInBlockHasProp(position, PROP_STOP);
	if (hasStopProp)
		return moveableRecord[position.x][position.y] = 0;

	bool hasYouProp = checkObjectsInBlockHasProp(position, PROP_YOU);
	bool hasPushProp = checkObjectsInBlockHasProp(position, PROP_PUSH);
	if (!hasYouProp && !hasPushProp)
		return moveableRecord[position.x][position.y] = 1;

	bool aheadBlockMoveable = checkMoveDown(position + CPoint(0, 1));
	moveableRecord[position.x][position.y] = checkBlockMoveObjects(position, aheadBlockMoveable);
	return moveableRecord[position.x][position.y];
}

bool LevelManager::checkMoveLeft(CPoint position) {
	if (position.x == -1) return false;
	if (moveableRecord[position.x][position.y] != -1)
		return moveableRecord[position.x][position.y];

	bool hasStopProp = checkObjectsInBlockHasProp(position, PROP_STOP);
	if (hasStopProp)
		return moveableRecord[position.x][position.y] = 0;

	bool hasYouProp = checkObjectsInBlockHasProp(position, PROP_YOU);
	bool hasPushProp = checkObjectsInBlockHasProp(position, PROP_PUSH);
	if (!hasYouProp && !hasPushProp)
		return moveableRecord[position.x][position.y] = 1;

	bool aheadBlockMoveable = checkMoveLeft(position - CPoint(1, 0));
	moveableRecord[position.x][position.y] = checkBlockMoveObjects(position, aheadBlockMoveable);
	return moveableRecord[position.x][position.y];
}

bool LevelManager::checkMoveRight(CPoint position) {
	if (position.x == gameBoardWidth) return false;
	if (moveableRecord[position.x][position.y] != -1)
		return moveableRecord[position.x][position.y];

	bool hasStopProp = checkObjectsInBlockHasProp(position, PROP_STOP);
	if (hasStopProp)
		return moveableRecord[position.x][position.y] = 0;

	bool hasYouProp = checkObjectsInBlockHasProp(position, PROP_YOU);
	bool hasPushProp = checkObjectsInBlockHasProp(position, PROP_PUSH);
	if (!hasYouProp && !hasPushProp)
		return moveableRecord[position.x][position.y] = 1;

	bool aheadBlockMoveable = checkMoveRight(position + CPoint(1, 0));
	moveableRecord[position.x][position.y] = checkBlockMoveObjects(position, aheadBlockMoveable);
	return moveableRecord[position.x][position.y];
}

void LevelManager::checkAllOverlapProp() {
	checkOverlap_YouWin();
}

void LevelManager::checkOverlap_YouWin() {
	if (checkPropOverlap(PROP_YOU, PROP_WIN)) {
		reachWinObj = true;
	}
}

bool LevelManager::checkPropOverlap(PropId propId1, PropId propId2) {
	for (int i = 0; i < gameBoardHeight; i++) {
		for (int j = 0; j < gameBoardWidth; j++) {
			if (checkPropInSameBlock(CPoint(i, j), propId1, propId2)) {
				return true;
			}
		}
	}
	return false;
}

bool LevelManager::checkPropInSameBlock(CPoint position, PropId propId1, PropId propId2) {
	bool hasProp1 = false;
	bool hasProp2 = false;
	for (Gameobject *gameobject : gameBoard[position.x][position.y]) {
		hasProp1 |= propsManager.GetGameobjectProp(gameobject->gameobjectId, propId1);
		hasProp2 |= propsManager.GetGameobjectProp(gameobject->gameobjectId, propId2);
	}
	return hasProp1 && hasProp2;
}

Gameobject* LevelManager::getNounTextObject(CPoint position) {
	for (Gameobject *gameobject : gameBoard[position.x][position.y]) {
		if (IsNounTextObject(gameobject->gameobjectId)) return gameobject;
	}
	return nullptr;
}

Gameobject* LevelManager::getPropTextObject(CPoint position) {
	for (Gameobject *gameobject : gameBoard[position.x][position.y]) {
		if (IsPropTextObject(gameobject->gameobjectId)) return gameobject;
	}
	return nullptr;
}

void LevelManager::getAllDescriptions() {
	additionProps.clear();

	for (int i = 0; i < gameBoardHeight; i++) {
		for (int j = 0; j < gameBoardWidth; j++) {
			for (size_t k = 0; k < gameBoard[i][j].size(); k++) {
				if (gameBoard[i][j][k]->gameobjectId == GAMEOBJECT_TEXT_IS) {
					checkDescription_is(CPoint(i, j));
				}
			}
		}
	}
}

void LevelManager::checkDescription_is(CPoint position) {
	if (position.x != 0 && position.x != gameBoardWidth - 1) {
		Gameobject* main_noun = getNounTextObject(position - CPoint(1, 0));
		Gameobject* sub_noun = getNounTextObject(position + CPoint(1, 0));
		Gameobject* prop = getPropTextObject(position + CPoint(1, 0));

		if (main_noun && sub_noun) {
			additionProps.push_back(make_pair(main_noun->gameobjectId, sub_noun->gameobjectId));
		}
		else if (main_noun && prop) {
			additionProps.push_back(make_pair(main_noun->gameobjectId, prop->gameobjectId));
		}
	}
	if (position.y != 0 && position.y != gameBoardHeight - 1) {
		Gameobject* main_noun = getNounTextObject(position - CPoint(0, 1));
		Gameobject* sub_noun = getNounTextObject(position + CPoint(0, 1));
		Gameobject* prop = getPropTextObject(position + CPoint(0, 1));

		if (main_noun && sub_noun) {
			additionProps.push_back(make_pair(main_noun->gameobjectId, sub_noun->gameobjectId));
		}
		else if (main_noun && prop) {
			additionProps.push_back(make_pair(main_noun->gameobjectId, prop->gameobjectId));
		}
	}
}

void LevelManager::replaceGameobject(GameobjectId originGameobject, GameobjectId convertGameobject) {
	if (originGameobject == convertGameobject) return;

	for (auto &row : gameBoard) {
		for (auto &block : row) {
			for (size_t i = 0; i < block.size(); i++) {
				if (block[i]->gameobjectId == originGameobject) {
					block.push_back(
						new Gameobject(
							convertGameobject,
							block[i]->gameBoardPosition,
							textureOriginPosition,
							textureSize
						)
					);
					delete block[i];
					block.erase(block.begin() + i);
				}
			}
		}
	}
}

void LevelManager::updateProps() {
	getAllDescriptions();
	setPropsManager();
}