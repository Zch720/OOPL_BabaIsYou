#include "stdafx.h"
#include "level_data.h"
#include "gameobject_id.h"
#include "texture_manager.h"
#include "../../Expansion/log.h"
#include "../../Expansion/dataio.h"
#include "../../Expansion/string_proc.h"

int LevelData::world = 0;
int LevelData::level = 0;

game_framework::CMovingBitmap LevelData::background = game_framework::CMovingBitmap();
int LevelData::gameboardWidth = 0;
int LevelData::gameboardHeight = 0;
bool LevelData::touchWinObject = 0;

vector2d<Block> LevelData::Gameboard = vector2d<Block>();

void LevelData::LoadLevel(int level) {
	Clear();
	LevelData::level = level;
	getWorld(level);

	loadBackground();
	loadResourceDatas();
}
void LevelData::Clear() {
	Gameboard.clear();
	world = -1;
	level = -1;
	touchWinObject = false;
}

void LevelData::SetTouchWin(bool value) {
	touchWinObject = value;
}

int LevelData::GetGameboardWidth() {
	return gameboardWidth;
}
int LevelData::GetGameboardHeight() {
	return gameboardHeight;
}
bool LevelData::GetTouchWin() {
	return touchWinObject;
}

void LevelData::ShowBackground() {
	background.ShowBitmap();
}

bool LevelData::IsPointInGameboard(POINT point) {
	return (
		-1 < point.x && point.x < gameboardWidth &&
		-1 < point.y && point.y < gameboardHeight
	);
}

void LevelData::getWorld(int level) {
	if (level <= 12) {
		world = 0;
	} else if (level <= 27) {
		world = 1;
	}
}

void LevelData::checkSourceFileTitle(std::vector<std::string>::iterator &line, std::string title) {
	if (*line != title) {
		Log::LogError("level %d source file title wrong, '%s'", level, title);
	}
}

void LevelData::loadResourceDatas() {
	std::string sources = loadFile("./resources/level/" + intToString(level) + ".level");
	std::vector<std::string> levelResource = stringSplit(sources, '\n');
	std::vector<std::string>::iterator line = levelResource.begin();
	loadGameboardSize(line);
	loadTextureOriginPosition(line);
	loadTextureSize(line);
	loadNeededTextures(line);
	loadObjects(line, levelResource.end());
}
void LevelData::loadBackground() {
	background = game_framework::CMovingBitmap();
	background.LoadBitmapByString({ "./resources/LevelBackground/" + intToString(level) + ".bmp" });
}
void LevelData::loadGameboardSize(std::vector<std::string>::iterator &line) {
	checkSourceFileTitle(line++, "[game board size]");
	gameboardWidth = stringToInt(*(line++));
	gameboardHeight = stringToInt(*(line++));
}
void LevelData::loadTextureOriginPosition(std::vector<std::string>::iterator &line) {
	checkSourceFileTitle(line++, "[texture origin position]");
	int x = stringToInt(*(line++));
	int y = stringToInt(*(line++));
	TextureManager::SetTextureOriginPosition(x, y);
}
void LevelData::loadTextureSize(std::vector<std::string>::iterator &line) {
	checkSourceFileTitle(line++, "[texture size]");
	int textureSize = stringToInt(*(line++));
	TextureManager::SetDirInfo(world, textureSize);
}
void LevelData::loadNeededTextures(std::vector<std::string>::iterator &line) {
	checkSourceFileTitle(line++, "[needed texture]");
	for (; (*line)[0] != '['; line++) {
		std::vector<std::string> textureInfo = stringSplit(*line, ' ');
		GameobjectId gameobjectId = static_cast<GameobjectId>(GetGameobjectIdByName(textureInfo[0]));
		PropId colorPropId = static_cast<PropId>(GetPropIdByName(textureInfo[1]));
		TextureManager::LoadTexture(gameobjectId, colorPropId);
	}
	TextureManager::LoadTexture(GAMEOBJECT_CROSSED, PROP_NONE);
}
void LevelData::loadObjects(std::vector<std::string>::iterator &line, std::vector<std::string>::iterator &linesEnd) {
	checkSourceFileTitle(line++, "[objects]");
	std::vector<GameobjectCreateInfo> gameobjectCreateInfos;
	for (; line != linesEnd; line++) {
		std::vector<std::string> objectInfo = stringSplit(*line , ' ');
		GameobjectId gameobjectId = static_cast<GameobjectId>(GetGameobjectIdByName(objectInfo[0]));
		Point position(stringToInt(objectInfo[1]), stringToInt(objectInfo[2]));
		Direction direction = static_cast<Direction>(stringToInt(objectInfo[3]));
		gameobjectCreateInfos.push_back(GameobjectCreateInfo{ gameobjectId, position, direction });
	}

	createGameboard();
	createGameobjects(gameobjectCreateInfos);
}

void LevelData::createGameboard() {
	for (int i = 0; i < gameboardWidth; i++) {
		std::vector<Block> col;
		for (int j = 0; j < gameboardHeight; j++) {
			col.push_back(Block(Point(i, j)));
		}
		Gameboard.push_back(col);
	}
}

void LevelData::createGameobjects(std::vector<GameobjectCreateInfo> createInfos) {
	for (GameobjectCreateInfo &info : createInfos) {
		if (gameboardWidth <= info.position.x || gameboardHeight <= info.position.y) {
			Log::LogError("%s at (%d, %d) create failed, out of range", GetGameobjectNameById(info.gameobjectId).c_str(), info.position.x, info.position.y);
		}
		Gameobject *gameobject = Gameboard[info.position].GenGameobject(info.gameobjectId);
		gameobject->SetTextureDirection(info.textureDirection);
	}
}