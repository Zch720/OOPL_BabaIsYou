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
vector2d<Block> LevelData::gameboard = vector2d<Block>();
int LevelData::gameboardWidth = 0;
int LevelData::gameboardHeight = 0;

Point LevelData::textureOrigionPosition = Point(0, 0);

bool LevelData::touchWinObject = 0;

void LevelData::LoadLevel(int level) {
	Clear();
	level = level;
	getWorld(level);

	background = game_framework::CMovingBitmap();
	background.LoadBitmapByString({ "./resources/LevelBackground/" + intToString(level) + ".bmp" });

	std::string levelSource = loadFile("./resources/level/" + intToString(level));
	std::vector<std::string> levelSourceLines = stringSplit(levelSource, '\n');
	std::vector<GameobjectCreateInfo> gameobjectCreateInfos;

	size_t linesCount = 0;

	if (levelSourceLines[linesCount++] != "[game board size]") {
		Log::LogError("level %d source file format wrong", level);
	}
	gameboardWidth = stringToInt(levelSourceLines[linesCount++]);
	gameboardHeight = stringToInt(levelSourceLines[linesCount++]);

	if (levelSourceLines[linesCount++] != "[texture origin position]") {
		Log::LogError("level %d source file format wrong", level);
	}
	textureOrigionPosition.x = stringToInt(levelSourceLines[linesCount++]);
	textureOrigionPosition.y = stringToInt(levelSourceLines[linesCount++]);

	if (levelSourceLines[linesCount++] != "[texture size]") {
		Log::LogError("level %d source file format wrong", level);
	}
	TextureManager::textureSize = stringToInt(levelSourceLines[linesCount++]);

	if (levelSourceLines[linesCount++] != "[needed texture]") {
		Log::LogError("level %d source file format wrong", level);
	}
	TextureManager::Clear();
	for (; linesCount < levelSourceLines.size() && levelSourceLines[linesCount][0] != '['; linesCount++) {
		std::vector<std::string> textureInfo = stringSplit(levelSourceLines[linesCount], ' ');

		GameobjectId gameobjectId = static_cast<GameobjectId>(GetGameobjectIdByName(textureInfo[0]));
		PropId colorPropId = static_cast<PropId>(GetPropIdByName(textureInfo[1]));
		TextureManager::LoadTexture(gameobjectId, colorPropId, world);
	}
	TextureManager::LoadTexture(GAMEOBJECT_CROSSED, PROP_NONE, world);

	if (linesCount == levelSourceLines.size() || levelSourceLines[linesCount++] != "[objects]") {
		Log::LogError("level %d source file format wrong", level);
	}
	for (; linesCount < levelSourceLines.size(); linesCount++) {
		std::vector<std::string> objectInfo = stringSplit(levelSourceLines[linesCount], ' ');

		GameobjectId gameobjectId = static_cast<GameobjectId>(GetGameobjectIdByName(objectInfo[0]));
		gameobjectCreateInfos.push_back(
			GameobjectCreateInfo{
				gameobjectId,
				Point(stringToInt(objectInfo[1]), stringToInt(objectInfo[2])),
				static_cast<Direction>(stringToInt(objectInfo[3]))
			}
		);
	}

	createGameboard(gameobjectCreateInfos);
}
void LevelData::Clear() {
	for (auto &col : gameboard) {
		for (Block &block : col) {
			block.clear();
		}
		col.clear();
	}
	gameboard.clear();

	world = -1;
	level = -1;
	touchWinObject = false;
}

void LevelData::getWorld(int level) {
	if (level >= 2000) {
		world = -1;
	} else if (level <= 12) {
		world = 0;
	} else if (level <= 27) {
		world = 1;
	}
}

void LevelData::createGameboard(std::vector<GameobjectCreateInfo> createInfos) {
	for (int i = 0; i < gameboardWidth; i++) {
		std::vector<Block> col;
		for (int j = 0; j < gameboardHeight; j++) {
			col.push_back(Block(Point(i, j)));
		}
		gameboard.push_back(col);
	}

	for (GameobjectCreateInfo &info : createInfos) {
		if (gameboardWidth <= info.position.x || gameboardHeight <= info.position.y) {
			Log::LogError("%s at (%d, %d) create failed, out of range", GetGameobjectNameById(info.gameobjectId).c_str(), info.position.x, info.position.y);
		}
		Gameobject *gameobject = gameboard[info.position].GenGameobject(info.gameobjectId);
		gameobject->SetTextureDirection(info.textureDirection);
	}
}