#include "stdafx.h"
#include "property_manager.h"
#include "texture_manager.h"
#include "level_data.h"
#include "game_level_config.h"
#include "../../Expansion/dataio.h"
#include "../../Expansion/string_proc.h"
#include "../../Expansion/log.h"

game_framework::CMovingBitmap LevelData::background = game_framework::CMovingBitmap();
vector2d<Block> LevelData::gameboard = {};
int LevelData::genIdCounter = 0;
bool LevelData::isWin = false;

void LevelData::Clear() {
	gameboard.clear();
	delete &background;
}

void LevelData::Reset() {
	gameboard.clear();
	genIdCounter = 1;
	isWin = false;
}

void LevelData::LoadLevel(int level) {
	std::string origionData = loadFile("./resources/level/" + intToString(level) + ".level");
	std::vector<Datas> levelDatas = splitLevelDatas(origionData);
	
	Reset();
	loadLevel_Background(level);
	loadLevel_GameboardSize(levelDatas[GAMEBOARD_SIZE_TITLE_INDEX]);
	loadLevel_TextureOrigionPosition(levelDatas[TEXTURE_ORIGION_POSITION_TITLE_INDEX]);
	loadLevel_TextureSize(levelDatas[TEXTURE_SIZE_TITLE_INDEX]);
	loadLevel_NeededTextures(levelDatas[NEEDED_TEXTURES_TITLE_INDEX]);
	loadLevel_Objects(levelDatas[OBJECTS_TITLE_INDEX]);
}

bool LevelData::IsWin() {
	return isWin;
}

bool LevelData::IsInsideGameboard(POINT position) {
	return (
		0 <= position.x && (size_t)position.x < gameboard.GetWidth() &&
		0 <= position.y && (size_t)position.y < gameboard.GetHeight()
	);
}

bool LevelData::IsPropertyOverlapBlock(POINT position, PropertyId propertyId1, PropertyId propertyId2) {
	return gameboard[position].IsPropertyOverlap(propertyId1, propertyId2);
}

bool LevelData::IsPropertyOverlap(PropertyId propertyId1, PropertyId propertyId2) {
	bool result = false;
	gameboard.foreach([&result, propertyId1, propertyId2](Block &block) {
		if (result) return;
		result |= block.IsPropertyOverlap(propertyId1, propertyId2);
	});
	return result;
}

bool LevelData::HasTextobjectInBlock(POINT position) {
	return gameboard[position].HasTextobject();
}

ObjectBase& LevelData::GetTextobjectInBlock(POINT position) {
	return *(gameboard[position].GetTextobject());
}

ObjectBase& LevelData::GetBlockObject(POINT position, int genId) {
	return *(gameboard[position].GetBlockObject(genId));
}

ObjectBase& LevelData::GetBlockObject(ObjectInfo objectInfo) {
	return *(gameboard[objectInfo.position].GetBlockObject(objectInfo.genId));
}

int LevelData::GetGameboardWidth() {
	return gameboard.GetWidth();
}

int LevelData::GetGameboardHeight() {
	return gameboard.GetHeight();
}

game_framework::CMovingBitmap& LevelData::GetBackground() {
	return background;
}

int LevelData::GetGameobjectConnectState(ObjectInfo info) {
	int result = 0;

	result += objectConnectStateCheck(info, Point().Up(), CONNECT_UP);
	result += objectConnectStateCheck(info, Point().Left(), CONNECT_LEFT);
	result += objectConnectStateCheck(info, Point().Down(), CONNECT_DOWN);
	result += objectConnectStateCheck(info, Point().Right(), CONNECT_RIGHT);

	return result;
}

std::vector<ObjectId> LevelData::GetBlockObjectIds(POINT position) {
	std::vector<ObjectId> result;
	for (ObjectBase *object : gameboard[position].objects) {
		result.push_back(object -> GetObjectId());
	}
	return result;
}

ObjectBase& LevelData::GetFirstObjectWithoutGenIdWithoutFloat(POINT position, int genId) {
	return *(gameboard[position].GetFirstObjectWithoutGenIdWithoutFloat(genId));
}

ObjectBase& LevelData::GetFirstObjectWithObjectIdWithoutFloat(POINT position, ObjectId objectId) {
	return *(gameboard[position].GetFirstObjectWithObjectIdWithoutFloat(objectId));
}

ObjectBase& LevelData::GetFirstObjectWithoutObjectIdWithoutFloat(POINT position, ObjectId objectId) {
	return *(gameboard[position].GetFirstObjectWithoutObjectIdWithoutFloat(objectId));
}

ObjectBase& LevelData::GetFirstObjectWithPropertyWithoutFloat(POINT position, PropertyId propertyId) {
	return *(gameboard[position].GetFirstObjectWithPropertyWithoutFloat(propertyId));
}

ObjectBase& LevelData::GetFirstObjectWithoutPropertyWithoutFloat(POINT position, PropertyId propertyId) {
	return *(gameboard[position].GetFirstObjectWithoutPropertyWithoutFloat(propertyId));
}

ObjectBase& LevelData::GetFirstObjectWithoutGenIdWithFloat(POINT position, int genId) {
	return *(gameboard[position].GetFirstObjectWithoutGenIdWithFloat(genId));
}

ObjectBase& LevelData::GetFirstObjectWithObjectIdWithFloat(POINT position, ObjectId objectId) {
	return *(gameboard[position].GetFirstObjectWithObjectIdWithFloat(objectId));
}

ObjectBase& LevelData::GetFirstObjectWithoutObjectIdWithFloat(POINT position, ObjectId objectId) {
	return *(gameboard[position].GetFirstObjectWithoutObjectIdWithFloat(objectId));
}

ObjectBase& LevelData::GetFirstObjectWithPropertyWithFloat(POINT position, PropertyId propertyId) {
	return *(gameboard[position].GetFirstObjectWithPropertyWithFloat(propertyId));
}

ObjectBase& LevelData::GetFirstObjectWithoutPropertyWithFloat(POINT position, PropertyId propertyId) {
	return *(gameboard[position].GetFirstObjectWithoutPropertyWithFloat(propertyId));
}

void LevelData::SetIsWin(bool isWin) {
	LevelData::isWin = isWin;
}

void LevelData::GenObjectWithGenId(POINT position, GenObjectInfo genInfo, int genId) {
	ObjectBase *object = getNewObject(ObjectTypeProc::GetType(genInfo.objectId));
	object -> SetGenId(genId);
	object -> SetPosition(position);
	object -> SetObjectId(genInfo.objectId);
	object -> SetTextureDirection(genInfo.textureDirection);
	object -> LoadTexture();
	gameboard[position].AddObject(object);
}

void LevelData::GenNewObject(POINT position, GenObjectInfo genInfo) {
	GenObjectWithGenId(position, genInfo, genIdCounter++);
}

void LevelData::DeleteObject(POINT position, int genId) {
	ObjectBase *object = gameboard[position].GetBlockObject(genId);
	gameboard[position].RemoveObject(genId);
	delete object;
}

void LevelData::MoveObject(ObjectInfo info, POINT newPosition) {
	ObjectBase *object = gameboard[info.position].GetBlockObject(info.genId);
	gameboard[info.position].RemoveObject(info.genId);
	gameboard[newPosition].AddObject(object);
}

void LevelData::ReplaceObject(ObjectInfo objectInfo, ObjectId convertObjectId) {
	gameboard[objectInfo.position].RemoveObject(objectInfo.genId);
	GenObjectWithGenId(objectInfo.position, {convertObjectId, objectInfo.textureDirection}, objectInfo.genId);
}

void LevelData::GameboardForeach(vector2d<Block>::ElementProcFunc procFunc) {
	gameboard.foreach(procFunc);
}
	
void LevelData::createGameboard(int width, int height) {
	for (int i = 0; i < width; i++) {
		std::vector<Block> col;
		for (int j = 0; j < height; j++) {
			col.push_back(Block({i, j}));
		}
		gameboard.push_back(col);
	}
}

ObjectBase* LevelData::getNewObject(ObjectType objectType) {
	if (objectType == TYPE_TEXT) return new TextObject();
	else if (objectType == TYPE_TILED) return  new TiledObject();
	else if (objectType == TYPE_STATIC) return new StaticObject();
	else if (objectType == TYPE_CHARACTER) return new CharacterObject();
	else if (objectType == TYPE_ANIMATION) return new AnimationObject();
	else if (objectType == TYPE_DIRECTION) return new DirectionObject();
	else if (objectType == TYPE_ANIMATION_DIRECTION) return new AnimationDirectionObject();
	return nullptr;
}

std::vector<LevelData::Datas> LevelData::splitLevelDatas(std::string &origionData) {
	Datas lines = stringSplit(origionData, '\n');
	std::vector<Datas> result;
	
	size_t begin = 0;
	for (size_t i = 1; i < lines.size(); i++) {
		if (lines[i][0] == '[') {
			result.push_back(Datas(lines.begin() + begin, lines.begin() + i));
			begin = i;
		}
	}
	result.push_back(Datas(lines.begin() + begin, lines.end()));
	
	if (result.size() != 5) {
		Log::LogError("<Level Data> Level file format wrong, there is only %d blocks in file", result.size());
	}
	return result;
}

void LevelData::loadLevel_checkTitle(std::string title, std::string targetTitle) {
	if (title != targetTitle) {
		Log::LogError("<Level Data> Level title wrong, \'%s\'", targetTitle.c_str());
	}
}

void LevelData::loadLevel_Background(int level) {
	background = game_framework::CMovingBitmap();
	background.LoadBitmapByString({ "./resources/LevelBackground/" + intToString(level) + ".bmp" });
}

void LevelData::loadLevel_GameboardSize(Datas &data) {
	loadLevel_checkTitle(data[0], "[game board size]");
	createGameboard(stringToInt(data[1]), stringToInt(data[2]));
}

void LevelData::loadLevel_TextureOrigionPosition(Datas &data) {
	loadLevel_checkTitle(data[0], "[texture origin position]");
	TextureManager::SetTextureOrigionPosition({stringToInt(data[1]), stringToInt(data[2])});
}

void LevelData::loadLevel_TextureSize(Datas &data) {
	loadLevel_checkTitle(data[0], "[texture size]");
	TextureManager::SetTextureSize(stringToInt(data[1]));
}

void LevelData::loadLevel_NeededTextures(Datas &data) {
	loadLevel_checkTitle(data[0], "[needed texture]");
	TextureManager::Clear();
	for (size_t i = 1; i < data.size(); i++) {
		Datas textureInfo = stringSplit(data[i], ' ');
		int world = stringToInt(textureInfo[2]);
		PropertyId colorPropertyId = PropertyIdProc::GetIdByName(textureInfo[1]);
		TextureManager::LoadTexture({world, colorPropertyId, textureInfo[0]});
		PropertyManager::AddObjectProperty(ObjectIdProc::GetIdByName(textureInfo[0]), PROPERTY_PUSH);
	}
	TextureManager::LoadTexture({0, PROPERTY_NONE, "crossed"});
}

void LevelData::loadLevel_Objects(Datas &data) {
	loadLevel_checkTitle(data[0], "[objects]");
	for (size_t i = 1; i < data.size(); i++) {
		Datas objectInfo = stringSplit(data[i], ' ');
		ObjectId objectId = ObjectIdProc::GetIdByName(objectInfo[0]);
		POINT position{stringToInt(objectInfo[1]), stringToInt(objectInfo[2])};
		Direction textureDirection = static_cast<Direction>(stringToInt(objectInfo[3]));
		GenNewObject(position, {objectId, textureDirection});
	}
}

void LevelData::BlockObjectForeach(POINT position, ObjectProcFunc procFunc) {
	for (ObjectBase *object : gameboard[position].objects) {
		procFunc(*object);
	}
}

void LevelData::AllObjectForeach(ObjectProcFunc procFunc) {
	gameboard.foreach([procFunc](Block &block) {
		block.foreach(procFunc);
	});
}

int LevelData::objectConnectStateCheck(ObjectInfo &info, Point offset, int connectValue) {
	POINT targetPosition = info.position + offset;
	if (!IsInsideGameboard(targetPosition)) return connectValue;
	if (!gameboard[targetPosition].HasObjectId(info.objectId)) return 0;
	return connectValue;
}