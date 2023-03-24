#include "stdafx.h"
#include "level_manager.h"
#include "texture_manager.h"
#include "../Expansion/dataio.h"
#include "../Expansion/string_proc.h"
#include "../Expansion/log.h"


LevelManager::LevelManager() {}
LevelManager::~LevelManager() {
	if (gameBoard.size() == 0) return;
	clearLevel();
}

void LevelManager::LoadLevel(int level) {
	clearLevel();

	char formatWrongMessage[128];
	sprintf_s(formatWrongMessage, "level %d source file format wrong", level);

	std::string levelSource = loadFile("./resources/level/" + intToString(level));
	std::vector<std::string> levelSourceLines = stringSplit(levelSource, '\n');
	std::vector<GameobjectCreateInfo> gameobjectCreateInfos;
	std::unordered_set<GameobjectId> gameobjectIdRecord;
	int world = getWorld(level);

	size_t linesCount = 0;

	if (levelSourceLines[linesCount++] != "[game board size]") {
		logError(formatWrongMessage);
	}
	gameBoardWidth = stringToInt(levelSourceLines[linesCount++]);
	gameBoardHeight = stringToInt(levelSourceLines[linesCount++]);

	if (levelSourceLines[linesCount++] != "[texture origin position]") {
		logError(formatWrongMessage);
	}
	textureOrigionPosition.x = stringToInt(levelSourceLines[linesCount++]);
	textureOrigionPosition.y = stringToInt(levelSourceLines[linesCount++]);

	if (levelSourceLines[linesCount++] != "[texture size]") {
		logError(formatWrongMessage);
	}
	textureSize = stringToInt(levelSourceLines[linesCount++]);

	if (levelSourceLines[linesCount++] != "[needed texture]") {
		logError(formatWrongMessage);
	}
	TextureManager::Clear();
	for (; linesCount < levelSourceLines.size() && levelSourceLines[linesCount][0] != '['; linesCount++) {
		std::vector<std::string> textureInfo = stringSplit(levelSourceLines[linesCount], ' ');

		GameobjectId gameobjectId = static_cast<GameobjectId>(GetGameobjectIdByName(textureInfo[0]));
		PropId colorPropId = static_cast<PropId>(GetPropIdByName(textureInfo[1]));
		TextureManager::LoadTexture(gameobjectId, colorPropId, world);
	}

	if (linesCount == levelSourceLines.size() || levelSourceLines[linesCount++] != "[objects]") {
		logError(formatWrongMessage);
	}
	for (; linesCount < levelSourceLines.size(); linesCount++) {
		std::vector<std::string> objectInfo = stringSplit(levelSourceLines[linesCount], ' ');

		GameobjectId gameobjectId = static_cast<GameobjectId>(GetGameobjectIdByName(objectInfo[0]));
		gameobjectIdRecord.insert(gameobjectId);
		gameobjectCreateInfos.push_back(
			GameobjectCreateInfo{
				gameobjectId,
				CPoint(stringToInt(objectInfo[1]), stringToInt(objectInfo[2])),
				static_cast<Direction>(stringToInt(objectInfo[3]))
			}
		);
	}

	createGameboard(gameobjectCreateInfos);
	createBlockMoveableRecord();

	loadTextObjectsPushProp(gameobjectIdRecord);

	updateProps();

	updateGameobjectTextureColor();
}

void LevelManager::MoveUp() {
	if (touchWinObject) return;

	std::unordered_set<Gameobject*> hasYouPropGameobject = findAllYouGameobject();

	resetBlockMoveableRecord();
	moveableGameobjects.clear();
	undoBuffer.clear();

	for (Gameobject *gameobject : hasYouPropGameobject) {
		if (checkMoveUp(gameobject->gameBoardPosition - CPoint(0, 1))) {
			moveableGameobjects.insert(gameobject);
		}
	}

	for (Gameobject *gameobject : moveableGameobjects) {
		undoBuffer.push_back(
			UndoInfo{
				UNDO_MOVE_UP,
				gameobject->gameobjectId,
				gameobject->textureDirection,
				gameobject->gameBoardPosition
			}
		);
		removeGameobject(gameobject);
		gameobject->moveUp();
		addGameobject(gameobject->gameBoardPosition, gameobject);
	}

	updateProps();
	checkAllOverlapProp();

	updateGameobjectTextureColor();

	if (undoBuffer.size() != 0) {
		undoRecord.push(undoBuffer);
	}
}
void LevelManager::MoveDown() {
	if (touchWinObject) return;

	std::unordered_set<Gameobject*> hasYouPropGameobject = findAllYouGameobject();

	resetBlockMoveableRecord();
	moveableGameobjects.clear();
	undoBuffer.clear();

	for (Gameobject *gameobject : hasYouPropGameobject) {
		if (checkMoveDown(gameobject->gameBoardPosition + CPoint(0, 1))) {
			moveableGameobjects.insert(gameobject);
		}
	}

	for (Gameobject *gameobject : moveableGameobjects) {
		undoBuffer.push_back(
			UndoInfo{
				UNDO_MOVE_DOWN,
				gameobject->gameobjectId,
				gameobject->textureDirection,
				gameobject->gameBoardPosition
			}
		);
		removeGameobject(gameobject);
		gameobject->moveDown();
		addGameobject(gameobject->gameBoardPosition, gameobject);
	}

	updateProps();
	checkAllOverlapProp();

	updateGameobjectTextureColor();

	if (undoBuffer.size() != 0) {
		undoRecord.push(undoBuffer);
	}
}
void LevelManager::MoveLeft() {
	if (touchWinObject) return;

	std::unordered_set<Gameobject*> hasYouPropGameobject = findAllYouGameobject();

	resetBlockMoveableRecord();
	moveableGameobjects.clear();
	undoBuffer.clear();

	for (Gameobject *gameobject : hasYouPropGameobject) {
		if (checkMoveLeft(gameobject->gameBoardPosition - CPoint(1, 0))) {
			moveableGameobjects.insert(gameobject);
		}
	}

	for (Gameobject *gameobject : moveableGameobjects) {
		undoBuffer.push_back(
			UndoInfo{
				UNDO_MOVE_LEFT,
				gameobject->gameobjectId,
				gameobject->textureDirection,
				gameobject->gameBoardPosition
			}
		);
		removeGameobject(gameobject);
		gameobject->moveLeft();
		addGameobject(gameobject->gameBoardPosition, gameobject);
	}

	updateProps();
	checkAllOverlapProp();

	updateGameobjectTextureColor();

	if (undoBuffer.size() != 0) {
		undoRecord.push(undoBuffer);
	}
}
void LevelManager::MoveRight() {
	if (touchWinObject) return;

	std::unordered_set<Gameobject*> hasYouPropGameobject = findAllYouGameobject();

	resetBlockMoveableRecord();
	moveableGameobjects.clear();
	undoBuffer.clear();

	for (Gameobject *gameobject : hasYouPropGameobject) {
		if (checkMoveRight(gameobject->gameBoardPosition + CPoint(1, 0))) {
			moveableGameobjects.insert(gameobject);
		}
	}

	for (Gameobject *gameobject : moveableGameobjects) {
		undoBuffer.push_back(
			UndoInfo{
				UNDO_MOVE_RIGHT,
				gameobject->gameobjectId,
				gameobject->textureDirection,
				gameobject->gameBoardPosition
			}
		);
		removeGameobject(gameobject);
		gameobject->moveRight();
		addGameobject(gameobject->gameBoardPosition, gameobject);
	}

	updateProps();
	checkAllOverlapProp();

	updateGameobjectTextureColor();

	if (undoBuffer.size() != 0) {
		undoRecord.push(undoBuffer);
	}
}
void LevelManager::Undo() {
	if (undoRecord.empty()) return;

	std::vector<UndoInfo> infos = undoRecord.top();
	undoRecord.pop();

	reverse(infos.begin(), infos.end());

	for (UndoInfo &info : infos) {
		if (info.type == UNDO_MOVE_UP) {
			Gameobject *undoObject = findGameobjectInBlockById(info.position - CPoint(0, 1), info.gameobjectId);
			if (undoObject == nullptr) {
				logError("can't find undo gameobject");
			}

			removeGameobject(undoObject);
			undoObject->undoUp(info.direction);
			addGameobject(undoObject->gameBoardPosition, undoObject);
		}
		else if (info.type == UNDO_MOVE_DOWN) {
			Gameobject *undoObject = findGameobjectInBlockById(info.position + CPoint(0, 1), info.gameobjectId);
			if (undoObject == nullptr) {
				logError("can't find undo gameobject");
			}

			removeGameobject(undoObject);
			undoObject->undoDown(info.direction);
			addGameobject(undoObject->gameBoardPosition, undoObject);
		}
		else if (info.type == UNDO_MOVE_LEFT) {
			Gameobject *undoObject = findGameobjectInBlockById(info.position - CPoint(1, 0), info.gameobjectId);
			if (undoObject == nullptr) {
				logError("can't find undo gameobject");
			}

			removeGameobject(undoObject);
			undoObject->undoLeft(info.direction);
			addGameobject(undoObject->gameBoardPosition, undoObject);
		}
		else if (info.type == UNDO_MOVE_RIGHT) {
			Gameobject *undoObject = findGameobjectInBlockById(info.position + CPoint(1, 0), info.gameobjectId);
			if (undoObject == nullptr) {
				logError("can't find undo gameobject");
			}

			removeGameobject(undoObject);
			undoObject->undoRight(info.direction);
			addGameobject(undoObject->gameBoardPosition, undoObject);
		}
		else if (info.type == UNDO_DELETE) {
			genGameobject(info.position, info.gameobjectId, false);
		}
		else if (info.type == UNDO_GEN) {
			Gameobject *undoObject = findGameobjectInBlockById(info.position, info.gameobjectId);
			if (undoObject == nullptr) {
				logError("can't find undo gameobject");
			}

			deleteGameobject(undoObject, false);
		}
	}

	updateProps();
	checkAllOverlapProp();

	updateGameobjectTextureColor();
}

bool LevelManager::IsMoving() {
	for (auto &col : gameBoard) {
		for (auto &block : col) {
			for (Gameobject *gameobject : block) {
				if (gameobject->moveRemainStep != 0) {
					return true;
				}
			}
		}
	}
	return false;
}
bool LevelManager::IsWin() {
	return touchWinObject;
}

void LevelManager::Show() {
	// show gameobject didn't move
	for (auto &col : gameBoard) {
		for (auto &block : col) {
			for (Gameobject *gameobject : block) {
				if (gameobject->moveRemainStep != 0) continue;
				if (gameobject->gameobjectType == OBJECT_TYPE_TILED) {
					gameobject->show(textureAnimationCount, getGameobjectConnectStatus(gameobject));
				}
				else if (gameobject->gameobjectType == OBJECT_TYPE_TEXT) {
					if (connectedTextObject.find(gameobject) != connectedTextObject.end()) {
						gameobject->show(textureAnimationCount, 1);
					}
					else {
						gameobject->show(textureAnimationCount, 0);
					}
				}
				else {
					gameobject->show(textureAnimationCount);
				}
			}
		}
	}

	// show gameobject is moving
	for (auto &col : gameBoard) {
		for (auto &block : col) {
			for (Gameobject *gameobject : block) {
				if (gameobject->moveRemainStep == 0) continue;
				if (gameobject->gameobjectType == OBJECT_TYPE_TILED) {
					gameobject->show(textureAnimationCount, getGameobjectConnectStatus(gameobject));
				}
				else if (gameobject->gameobjectType == OBJECT_TYPE_TEXT) {
					if (connectedTextObject.find(gameobject) != connectedTextObject.end()) {
						gameobject->show(textureAnimationCount, 1);
					}
					else {
						gameobject->show(textureAnimationCount, 0);
					}
				}
				else {
					gameobject->show(textureAnimationCount);
				}
			}
		}
	}

	if (nextTextureWaitTime-- == 0) {
		textureAnimationCount = (textureAnimationCount + 1) % 3;
		nextTextureWaitTime = TEXTURE_ANIMATION_WAIT_TIME;
	}
}


void LevelManager::clearLevel() {
	touchWinObject = false;
	propsManager.ClearProperties();

	for (auto &col : gameBoard) {
		for (auto &block : col) {
			for (Gameobject *gameobject : block) {
				delete gameobject;
			}
			block.clear();
		}
		col.clear();
	}
	gameBoard.clear();

	for (auto &col : blockMoveableRecord) {
		col.clear();
	}
	blockMoveableRecord.clear();
}
int LevelManager::getWorld(int level) {
	return 0;
}
void LevelManager::createGameboard(std::vector<GameobjectCreateInfo> createInfos) {
	for (int i = 0; i < gameBoardWidth; i++) {
		std::vector<std::vector<Gameobject*>> col;
		for (int j = 0; j < gameBoardHeight; j++) {
			col.push_back(std::vector<Gameobject*>());
		}
		gameBoard.push_back(col);
	}

	for (GameobjectCreateInfo &info : createInfos) {
		if (gameBoardWidth <= info.position.x || gameBoardHeight <= info.position.y) {
			char message[128];
			sprintf_s(message, "%s at (%d, %d) create failed, out of range", GetGameobjectNameById(info.gameobjectId).c_str(), info.position.x, info.position.y);
			logError(message);
		}
		Gameobject *gameobject = new Gameobject(info.gameobjectId, info.position, textureSize);
		gameobject->textureDirection = info.textureDirection;
		gameBoard[info.position.x][info.position.y].push_back(gameobject);
	}
}
void LevelManager::createBlockMoveableRecord() {
	for (int i = 0; i < gameBoardWidth; i++) {
		blockMoveableRecord.push_back(std::vector<int8_t>(gameBoardHeight, 0));
	}
}
void LevelManager::resetBlockMoveableRecord() {
	for (auto &col : blockMoveableRecord) {
		for (int8_t &val : col) {
			val = -1;
		}
	}
}


bool LevelManager::checkHasGameobjectInBlock(CPoint position, GameobjectId gameobjectId) {
	for (Gameobject *gameobject : gameBoard[position.x][position.y]) {
		if (gameobject->gameobjectId == gameobjectId) {
			return true;
		}
	}
	return false;
}
int LevelManager::getGameobjectConnectStatus(Gameobject* gameobject) {
	GameobjectId gameobjectId = gameobject->gameobjectId;
	CPoint position = gameobject->gameBoardPosition;
	int result = 0;

	if (position.x != gameBoardWidth - 1 && checkHasGameobjectInBlock(position + CPoint(1, 0), gameobjectId)) {
		result += 1;
	}
	if (position.y != 0 && checkHasGameobjectInBlock(position - CPoint(0, 1), gameobjectId)) {
		result += 2;
	}
	if (position.x != 0 && checkHasGameobjectInBlock(position - CPoint(1, 0), gameobjectId)) {
		result += 4;
	}
	if (position.y != gameBoardHeight - 1 && checkHasGameobjectInBlock(position + CPoint(0, 1), gameobjectId)) {
		result += 8;
	}

	return result;
}
Gameobject* LevelManager::findGameobjectInBlockById(CPoint position, GameobjectId gameobjectId) {
	for (Gameobject *gameobject : gameBoard[position.x][position.y]) {
		if (gameobject->gameobjectId == gameobjectId) {
			return gameobject;
		}
	}
	return nullptr;
}
Gameobject* LevelManager::findGameobjectInBlockByProp(CPoint position, PropId propId) {
	for (Gameobject *gameobject : gameBoard[position.x][position.y]) {
		if (propsManager.GetGameobjectProp(gameobject->gameobjectId, propId)) {
			return gameobject;
		}
	}
	return nullptr;
}
std::unordered_set<Gameobject*> LevelManager::findAllYouGameobject() {
	std::unordered_set<Gameobject*> result;

	for (auto &col : gameBoard) {
		for (auto &block : col) {
			for (Gameobject *gameobject : block) {
				if (propsManager.GetGameobjectProp(gameobject->gameobjectId, PROP_YOU)) {
					result.insert(gameobject);
				}
			}
		}
	}

	return result;
}
void LevelManager::genGameobject(CPoint position , GameobjectId gameobjectId, bool addToBuffer) {
	Gameobject *gameobject = new Gameobject(gameobjectId, position, textureSize);
	gameBoard[position.x][position.y].push_back(gameobject);
	gameobject->setTextureWithColor(
		textureOrigionPosition,
		static_cast<PropId>(propsManager.GetColorProp(gameobjectId))
	);
	if (addToBuffer) {
		undoBuffer.push_back(
			UndoInfo{
				UNDO_GEN,
				gameobjectId,
				DIRECTION_RIGHT,
				position
			}
		);
	}
}
void LevelManager::deleteGameobject(Gameobject* gameobject, bool addToBuffer) {
	CPoint position = gameobject->gameBoardPosition;
	std::vector<Gameobject*> &block = gameBoard[position.x][position.y];
	for (size_t i = 0; i < block.size(); i++) {
		if (block[i] == gameobject) {
			if (addToBuffer) {
				undoBuffer.push_back(
					UndoInfo{
						UNDO_DELETE,
						gameobject->gameobjectId,
						gameobject->textureDirection,
						gameobject->gameBoardPosition
					}
				);
			}

			delete gameobject;
			block.erase(block.begin() + i);
			return;
		}
	}
	logWarning("one of gameobject can't delete");
}
void LevelManager::addGameobject(CPoint position, Gameobject* gameobject) {
	gameBoard[position.x][position.y].push_back(gameobject);
}
void LevelManager::removeGameobject(Gameobject* gameobject) {
	CPoint position = gameobject->gameBoardPosition;
	std::vector<Gameobject*> &block = gameBoard[position.x][position.y];
	for (size_t i = 0; i < block.size(); i++) {
		if (block[i] == gameobject) {
			block.erase(block.begin() + i);
			return;
		}
	}
	logWarning("one of gameobject can't remove");
}
void LevelManager::replaceGameobject(GameobjectId originGameobjectId, GameobjectId convertGameobjectId) {
	if (originGameobjectId == convertGameobjectId) return;

	for (auto &col : gameBoard) {
		for (auto &block : col) {
			for (auto gameobject = block.begin(); gameobject != block.end();) {
				if ((*gameobject)->gameobjectId == originGameobjectId) {
					genGameobject((*gameobject)->gameBoardPosition, convertGameobjectId);
					deleteGameobject((*gameobject));
				}
				else {
					gameobject++;
				}
			}
		}
	}
}
void LevelManager::updateGameobjectTextureColor() {
	for (auto &col : gameBoard) {
		for (auto &block : col) {
			for (Gameobject *gameobject : block) {
				gameobject->setTextureWithColor(
					textureOrigionPosition,
					static_cast<PropId>(propsManager.GetColorProp(gameobject->gameobjectId))
				);
			}
		}
	}
}


bool LevelManager::checkMoveableObjects(CPoint position, bool aheadBlockMoveable) {
	//std::unordered_set<Gameobject*> moveableBuffer;
	
	for (Gameobject *gameobject : gameBoard[position.x][position.y]) {
		bool pushProp = propsManager.GetGameobjectProp(gameobject->gameobjectId, PROP_PUSH);

		if (pushProp) {
			if (!aheadBlockMoveable)
				return blockMoveableRecord[position.x][position.y] = 0;
			//moveableBuffer.insert(gameobject);
			moveableGameobjects.insert(gameobject);
		}
	}
	//moveableGameobjects.insert(moveableBuffer.begin(), moveableBuffer.end());
	return blockMoveableRecord[position.x][position.y] = 1;
}
bool LevelManager::checkMoveUp(CPoint position) {
	if (position.y == -1) return false;
	if (blockMoveableRecord[position.x][position.y] != -1) {
		return blockMoveableRecord[position.x][position.y];
	}

	bool stopProp = checkHasPropInBlock(position, PROP_STOP);
	if (stopProp) {
		return blockMoveableRecord[position.x][position.y] = 0;
	}

	bool youProp = checkHasPropInBlock(position, PROP_YOU);
	bool pushprop = checkHasPropInBlock(position, PROP_PUSH);
	if (!youProp && !pushprop) {
		return blockMoveableRecord[position.x][position.y] = 1;
	}

	bool aheadBlockMoveable = checkMoveUp(position - CPoint(0, 1));
	blockMoveableRecord[position.x][position.y] = checkMoveableObjects(position, aheadBlockMoveable);
	return blockMoveableRecord[position.x][position.y];
}
bool LevelManager::checkMoveDown(CPoint position) {
	if (position.y == gameBoardHeight) return false;
	if (blockMoveableRecord[position.x][position.y] != -1) {
		return blockMoveableRecord[position.x][position.y];
	}

	bool stopProp = checkHasPropInBlock(position, PROP_STOP);
	if (stopProp) {
		return blockMoveableRecord[position.x][position.y] = 0;
	};

	bool youProp = checkHasPropInBlock(position, PROP_YOU);
	bool pushprop = checkHasPropInBlock(position, PROP_PUSH);
	if (!youProp && !pushprop) {
		return blockMoveableRecord[position.x][position.y] = 1;
	}

	bool aheadBlockMoveable = checkMoveDown(position + CPoint(0, 1));
	blockMoveableRecord[position.x][position.y] = checkMoveableObjects(position, aheadBlockMoveable);

	return blockMoveableRecord[position.x][position.y];
}
bool LevelManager::checkMoveLeft(CPoint position) {
	if (position.x == -1) return false;
	if (blockMoveableRecord[position.x][position.y] != -1) {
		return blockMoveableRecord[position.x][position.y];
	}

	bool stopProp = checkHasPropInBlock(position, PROP_STOP);
	if (stopProp) {
		return blockMoveableRecord[position.x][position.y] = 0;
	};

	bool youProp = checkHasPropInBlock(position, PROP_YOU);
	bool pushprop = checkHasPropInBlock(position, PROP_PUSH);
	if (!youProp && !pushprop) {
		return blockMoveableRecord[position.x][position.y] = 1;
	}

	bool aheadBlockMoveable = checkMoveLeft(position - CPoint(1, 0));
	blockMoveableRecord[position.x][position.y] = checkMoveableObjects(position, aheadBlockMoveable);
	return blockMoveableRecord[position.x][position.y];
}
bool LevelManager::checkMoveRight(CPoint position) {
	if (position.x == gameBoardWidth) return false;
	if (blockMoveableRecord[position.x][position.y] != -1) {
		return blockMoveableRecord[position.x][position.y];
	}

	bool stopProp = checkHasPropInBlock(position, PROP_STOP);
	if (stopProp) {
		return blockMoveableRecord[position.x][position.y] = 0;
	};

	bool youProp = checkHasPropInBlock(position, PROP_YOU);
	bool pushprop = checkHasPropInBlock(position, PROP_PUSH);
	if (!youProp && !pushprop) {
		return blockMoveableRecord[position.x][position.y] = 1;
	}

	bool aheadBlockMoveable = checkMoveRight(position + CPoint(1, 0));
	blockMoveableRecord[position.x][position.y] = checkMoveableObjects(position, aheadBlockMoveable);
	return blockMoveableRecord[position.x][position.y];
}


bool LevelManager::checkHasPropInBlock(CPoint position , PropId propId) {
	for (Gameobject *gameobject : gameBoard[position.x][position.y]) {
		if (propsManager.GetGameobjectProp(gameobject->gameobjectId, propId)) {
			return true;
		}
	}
	return false;
}
bool LevelManager::checkPropOverlap(PropId propId1, PropId propId2) {
	for (int i = 0; i < gameBoardWidth; i++) {
		for (int j = 0; j < gameBoardHeight; j++) {
			if (checkBlockPropOverlap(CPoint(i, j), propId1, propId2)) {
				return true;
			}
		}
	}
	return false;
}
bool LevelManager::checkBlockPropOverlap(CPoint position, PropId propId1, PropId propId2) {
	bool hasProp1 = false;
	bool hasProp2 = false;
	for (Gameobject *gameobject : gameBoard[position.x][position.y]) {
		hasProp1 |= propsManager.GetGameobjectProp(gameobject->gameobjectId, propId1);
		hasProp2 |= propsManager.GetGameobjectProp(gameobject->gameobjectId, propId2);
	}
	return hasProp1 && hasProp2;
}
void LevelManager::checkAllOverlapProp() {
	checkOverlapPropFull_You_Win();

	for (int i = 0; i < gameBoardWidth; i++) {
		for (int j = 0; j < gameBoardHeight; j++) {
			CPoint position(i, j);

			checkOverlapPropBlock_Sink(position);
			checkOverlapPropBlock_Defeat_You(position);
			checkOverlapPropBlock_Hot_Melt(position);
		}
	}
}
void LevelManager::checkOverlapPropFull_You_Win() {
	touchWinObject = checkPropOverlap(PROP_YOU, PROP_WIN);
}
void LevelManager::checkOverlapPropBlock_Sink(CPoint position) {
	Gameobject *sinkGameobject = findGameobjectInBlockByProp(position, PROP_SINK);
	if (!sinkGameobject) return;

	Gameobject *pushGameobject = findGameobjectInBlockByProp(position, PROP_PUSH);
	if (pushGameobject) {
		deleteGameobject(sinkGameobject);
		deleteGameobject(pushGameobject);
		return;
	}

	Gameobject *youGameobject = findGameobjectInBlockByProp(position, PROP_YOU);
	if (youGameobject) {
		deleteGameobject(sinkGameobject);
		deleteGameobject(youGameobject);
	}
}
void LevelManager::checkOverlapPropBlock_Defeat_You(CPoint position) {
	Gameobject *defeatGameobject = findGameobjectInBlockByProp(position, PROP_DEFEAT);
	Gameobject *youGameobject = findGameobjectInBlockByProp(position, PROP_YOU);

	if (defeatGameobject && youGameobject) {
		deleteGameobject(youGameobject);
	}
}
void LevelManager::checkOverlapPropBlock_Hot_Melt(CPoint position) {
	Gameobject *hotGameobject = findGameobjectInBlockByProp(position, PROP_HOT);
	Gameobject *meltGameobject = findGameobjectInBlockByProp(position, PROP_MELT);

	if (hotGameobject && meltGameobject) {
		deleteGameobject(hotGameobject);
		deleteGameobject(meltGameobject);
	}
}
void LevelManager::loadTextObjectsPushProp(std::unordered_set<GameobjectId> gameobjectIds) {
	for (GameobjectId id : gameobjectIds) {
		if (IsTextObject(id)) {
			propsManager.SetGameobjectProp(id, PROP_PUSH);
		}
	}
}
void LevelManager::updateProps() {
	connectedTextObject.clear();
	getAllDescriptions();
	updatePropsManager();
}
void LevelManager::updatePropsManager() {
	propsManager.ClearPropertiesWithoutTextPush();

	for (auto &prop : descriptionProps) {
		GameobjectId gameobjectId = static_cast<GameobjectId>(GetGameobjectByTextObject(prop.first));
		int propIdNum = GetPropIdFromTextGameobject(prop.second);
		if (propIdNum == -1) {
			GameobjectId convertGameobjectId = static_cast<GameobjectId>(GetGameobjectByTextObject(prop.second));
			replaceGameobject(gameobjectId, convertGameobjectId);
		}
		else {
			PropId propId = static_cast<PropId>(propIdNum);
			propsManager.SetGameobjectProp(gameobjectId, propId);
		}
	}

	propsManager.SetPropWithOtherProp(PROP_YOU, PROP_STOP);
}


Gameobject* LevelManager::getNounTextObjectInBlock(CPoint position) {
	for (Gameobject *gameobject : gameBoard[position.x][position.y]) {
		if (IsNounTextObject(gameobject->gameobjectId))
			return gameobject;
	}
	return nullptr;
}
Gameobject* LevelManager::getPropTextObjectInBlock(CPoint position) {
	for (Gameobject *gameobject : gameBoard[position.x][position.y]) {
		if (IsPropTextObject(gameobject->gameobjectId))
			return gameobject;
	}
	return nullptr;
}
void LevelManager::getAllDescriptions() {
	descriptionProps.clear();

	for (auto &col : gameBoard) {
		for (auto &block : col) {
			for (Gameobject *gameobject : block) {
				if (gameobject->gameobjectId == GAMEOBJECT_TEXT_IS) {
					checkDescription_is(gameobject);
				}
			}
		}
	}
}
void LevelManager::checkDescription_is(Gameobject* gameobject) {
	CPoint position = gameobject->gameBoardPosition;

	// check horizontal 'is' description
	if (position.x != 0 && position.x != gameBoardWidth - 1) {
		Gameobject *main_noun = getNounTextObjectInBlock(position - CPoint(1, 0));
		Gameobject *sub_noun = getNounTextObjectInBlock(position + CPoint(1, 0));
		Gameobject *prop = getPropTextObjectInBlock(position + CPoint(1, 0));

		if (main_noun && sub_noun) {
			descriptionProps.push_back(make_pair(main_noun->gameobjectId, sub_noun->gameobjectId));
			connectedTextObject.insert(gameobject);
			connectedTextObject.insert(main_noun);
			connectedTextObject.insert(sub_noun);
		}
		else if (main_noun && prop) {
			descriptionProps.push_back(make_pair(main_noun->gameobjectId, prop->gameobjectId));
			connectedTextObject.insert(gameobject);
			connectedTextObject.insert(main_noun);
			connectedTextObject.insert(prop);
		}
	}

	// check vertical 'is' description
	if (position.y != 0 && position.y != gameBoardHeight - 1) {
		Gameobject *main_noun = getNounTextObjectInBlock(position - CPoint(0, 1));
		Gameobject *sub_noun = getNounTextObjectInBlock(position + CPoint(0, 1));
		Gameobject *prop = getPropTextObjectInBlock(position + CPoint(0, 1));

		if (main_noun && sub_noun) {
			descriptionProps.push_back(make_pair(main_noun->gameobjectId, sub_noun->gameobjectId));
			connectedTextObject.insert(gameobject);
			connectedTextObject.insert(main_noun);
			connectedTextObject.insert(sub_noun);
		}
		else if (main_noun && prop) {
			descriptionProps.push_back(make_pair(main_noun->gameobjectId, prop->gameobjectId));
			connectedTextObject.insert(gameobject);
			connectedTextObject.insert(main_noun);
			connectedTextObject.insert(prop);
		}
	}
}