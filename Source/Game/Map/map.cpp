#include "stdafx.h"
#include "map.h"
#include "../../Expansion/log.h"
#include "../../Expansion/dataio.h"
#include "../../Expansion/string_proc.h"

void Map::CreateWorldVector() {
	for (int i = 0; i < worldVectorWidth; i++) {
		std::vector<Mapobject> width(worldVectorHeight);
		worldVector.push_back(width);
	}
}

void Map::ClearWorld() {
	worldVector.clear();
}

void Map::LoadWorld(int world) {
	ClearWorld();

	worldBackground.LoadBitmapByString({"./resources/map/" + intToString(world) + "/world_background_1.bmp", "resources/map/" + intToString(world) + "/world_background_2.bmp", "resources/map/" + intToString(world) + "/world_background_3.bmp"});
	worldBackground.SetTopLeft(70, 55);
	worldBackground.SetAnimation(250, false);
	std::string worldSource = loadFile("./resources/map/" + intToString(world) + ".txt");
	std::vector<std::string> worldSourceLines = stringSplit(worldSource, '\n');

	size_t linesCount = 0;

	if (worldSourceLines[linesCount++] != "[game board size]") {
		Log::LogError("world %d source file format wrong", world);
	}
	worldVectorWidth = stringToInt(worldSourceLines[linesCount++]);
	worldVectorHeight = stringToInt(worldSourceLines[linesCount++]);

	CreateWorldVector();

	if (worldSourceLines[linesCount++] != "[texture origin position]") {
		Log::LogError("world %d source file format wrong", world);
	}
	textureOrigionPosition.x = stringToInt(worldSourceLines[linesCount++]);
	textureOrigionPosition.y = stringToInt(worldSourceLines[linesCount++]);

	if (worldSourceLines[linesCount++] != "[box]") {
		Log::LogError("world %d source file format wrong", world);
	}
	std::vector<std::string> boxInfo = stringSplit(worldSourceLines[linesCount++], ' ');
	MapobjectId mapobjectId = static_cast<MapobjectId>(GetMapobjectIdByName(boxInfo[0]));
	Point mapobjectPosition(stringToInt(boxInfo[1]), stringToInt(boxInfo[2]));
	if (worldVectorWidth <= mapobjectPosition.x || worldVectorHeight <= mapobjectPosition.y) {
		Log::LogError("%s at (%d, %d) create failed, out of range", GetMapobjectNameById(mapobjectId).c_str(), boxInfo[1], boxInfo[2]);
	}
	box = Mapobject(mapobjectId, world);
	box.mapobjectPosition = mapobjectPosition;
	box.LoadTexture(world, textureOrigionPosition);


	if (worldSourceLines[linesCount++] != "[objects]") {
		Log::LogError("world %d source file format wrong", world);
	}
	for (; linesCount < worldSourceLines.size(); linesCount++) {
		std::vector<std::string> objectInfo = stringSplit(worldSourceLines[linesCount], ' ');

		MapobjectId mapobjectId = static_cast<MapobjectId>(GetMapobjectIdByName(objectInfo[0]));
		Point mapobjectPosition(stringToInt(objectInfo[1]), stringToInt(objectInfo[2]));
		if (worldVectorWidth <= mapobjectPosition.x || worldVectorHeight <= mapobjectPosition.y) {
			Log::LogError("%s at (%d, %d) create failed, out of range", GetMapobjectNameById(mapobjectId).c_str(), objectInfo[1], objectInfo[2]);
		}
		Mapobject loadMapobject(mapobjectId, world);
		loadMapobject.mapobjectPosition = mapobjectPosition;
		loadMapobject.levelIndex = stringToInt(objectInfo[3]);
		loadMapobject.LoadTexture(world, textureOrigionPosition);
		worldVector[mapobjectPosition] = loadMapobject;
	}
}

void Map::Show() {
	worldBackground.ShowBitmap();
	worldVector.foreach([](Mapobject &mapobject) {
		mapobject.Show();
	});
	box.Show();
}

int  Map::CheckIndex() {
	Mapobject checkedobject = worldVector[box.mapobjectPosition];
	if (checkedobject.mapobjectId == NONE) {
		return -1000;
	}
	return checkedobject.levelIndex;
}

Point Map::GetBoxPosition() {
	return box.mapobjectPosition;
}

void Map::SetBoxPosition(Point boxPosition) {
	box.mapobjectPosition = boxPosition;
}

void Map::MoveUp() {
	if (box.mapobjectPosition.y > 0) {
		box.mapobjectPosition.y -= 1;
		if (CheckIndex() != -1000) {
			box.mapobjectPosition.y += 1;
			box.MoveUp(textureOrigionPosition);
		}
		else {
			box.mapobjectPosition.y += 1;
		}
	}
}

void Map::MoveDown() {
	if (box.mapobjectPosition.y < worldVectorHeight - 1) {
		box.mapobjectPosition.y += 1;
		if (CheckIndex() != -1000) {
			box.mapobjectPosition.y -= 1;
			box.MoveDown(textureOrigionPosition);
		}
		else {
			box.mapobjectPosition.y -= 1;
		}
	}
}

void Map::MoveLeft() {
	if (box.mapobjectPosition.x > 0) {
		box.mapobjectPosition.x -= 1;
		if (CheckIndex() != -1000) {
			box.mapobjectPosition.x += 1;
			box.MoveLeft(textureOrigionPosition);
		}
		else {
			box.mapobjectPosition.x += 1;
		}
	}
}

void Map::MoveRight() {
	if (box.mapobjectPosition.x < worldVectorWidth - 1) {
		box.mapobjectPosition.x += 1;
		if (CheckIndex() != -1000) {
			box.mapobjectPosition.x -= 1;
			box.MoveRight(textureOrigionPosition);
		}
		else {
			box.mapobjectPosition.x -= 1;
		}
	}
}