#include "stdafx.h"
#include "object_type.h"
#include "texture_manager.h"
#include "../../Expansion/log.h"
#include "../../Expansion/string_proc.h"

#define TextureIndex(gameobjectId, colorId)	(((unit32_t)colorId << 32) | gameobjectId)

int TextureManager::textureSize = 0;
POINT TextureManager::textureOrigionPosition = {0, 0};
std::unordered_map<uint32_t, game_framework::CMovingBitmap> TextureManager::textures = {};
std::vector<std::string> TextureManager::textFiles = {
	"dark/0_1.bmp", "dark/0_2.bmp", "dark/0_3.bmp",
	"light/0_1.bmp", "light/0_2.bmp", "light/0_3.bmp",
};
std::vector<std::string> TextureManager::tiledFiles = {
	"0_1.bmp", "0_2.bmp", "0_3.bmp",
	"1_1.bmp", "1_2.bmp", "1_3.bmp",
	"2_1.bmp", "2_2.bmp", "2_3.bmp",
	"3_1.bmp", "3_2.bmp", "3_3.bmp",
	"4_1.bmp", "4_2.bmp", "4_3.bmp",
	"5_1.bmp", "5_2.bmp", "5_3.bmp",
	"6_1.bmp", "6_2.bmp", "6_3.bmp",
	"7_1.bmp", "7_2.bmp", "7_3.bmp",
	"8_1.bmp", "8_2.bmp", "8_3.bmp",
	"9_1.bmp", "9_2.bmp", "9_3.bmp",
	"10_1.bmp", "10_2.bmp", "10_3.bmp",
	"11_1.bmp", "11_2.bmp", "11_3.bmp",
	"12_1.bmp", "12_2.bmp", "12_3.bmp",
	"13_1.bmp", "13_2.bmp", "13_3.bmp",
	"14_1.bmp", "14_2.bmp", "14_3.bmp",
	"15_1.bmp", "15_2.bmp", "15_3.bmp",
};
std::vector<std::string> TextureManager::staticFiles = {
	"0_1.bmp", "0_2.bmp", "0_3.bmp",
};
std::vector<std::string> TextureManager::characterFiles = {
	"0_1.bmp", "0_2.bmp", "0_3.bmp",
	"1_1.bmp", "1_2.bmp", "1_3.bmp",
	"2_1.bmp", "2_2.bmp", "2_3.bmp",
	"3_1.bmp", "3_2.bmp", "3_3.bmp",
	"8_1.bmp", "8_2.bmp", "8_3.bmp",
	"9_1.bmp", "9_2.bmp", "9_3.bmp",
	"10_1.bmp", "10_2.bmp", "10_3.bmp",
	"11_1.bmp", "11_2.bmp", "11_3.bmp",
	"16_1.bmp", "16_2.bmp", "16_3.bmp",
	"17_1.bmp", "17_2.bmp", "17_3.bmp",
	"18_1.bmp", "18_2.bmp", "18_3.bmp",
	"19_1.bmp", "19_2.bmp", "19_3.bmp",
	"24_1.bmp", "24_2.bmp", "24_3.bmp",
	"25_1.bmp", "25_2.bmp", "25_3.bmp",
	"26_1.bmp", "26_2.bmp", "26_3.bmp",
	"27_1.bmp", "27_2.bmp", "27_3.bmp",
};
std::vector<std::string> TextureManager::animationFiles = {
	"0_1.bmp", "0_2.bmp", "0_3.bmp",
	"1_1.bmp", "1_2.bmp", "1_3.bmp",
	"2_1.bmp", "2_2.bmp", "2_3.bmp",
	"3_1.bmp", "3_2.bmp", "3_3.bmp",
};
std::vector<std::string> TextureManager::directionFiles = {
	"0_1.bmp", "0_2.bmp", "0_3.bmp",
	"8_1.bmp", "8_2.bmp", "8_3.bmp",
	"16_1.bmp", "16_2.bmp", "16_3.bmp",
	"24_1.bmp", "24_2.bmp", "24_3.bmp",
};
std::vector<std::string> TextureManager::animationDirectionFiles = {
	"0_1.bmp", "0_2.bmp", "0_3.bmp",
	"1_1.bmp", "1_2.bmp", "1_3.bmp",
	"2_1.bmp", "2_2.bmp", "2_3.bmp",
	"3_1.bmp", "3_2.bmp", "3_3.bmp",
	"8_1.bmp", "8_2.bmp", "8_3.bmp",
	"9_1.bmp", "9_2.bmp", "9_3.bmp",
	"10_1.bmp", "10_2.bmp", "10_3.bmp",
	"11_1.bmp", "11_2.bmp", "11_3.bmp",
	"16_1.bmp", "16_2.bmp", "16_3.bmp",
	"17_1.bmp", "17_2.bmp", "17_3.bmp",
	"18_1.bmp", "18_2.bmp", "18_3.bmp",
	"19_1.bmp", "19_2.bmp", "19_3.bmp",
	"24_1.bmp", "24_2.bmp", "24_3.bmp",
	"25_1.bmp", "25_2.bmp", "25_3.bmp",
	"26_1.bmp", "26_2.bmp", "26_3.bmp",
	"27_1.bmp", "27_2.bmp", "27_3.bmp",
};
std::unordered_map<ObjectType, std::function<std::string(TextureManager::TextureInfo&)>> TextureManager::typeToGetPath = {
	{TYPE_TEXT, TextureManager::filepathWithoutColor},
	{TYPE_TILED, TextureManager::filepathWithColor},
	{TYPE_STATIC, TextureManager::filepathWithColor},
	{TYPE_CHARACTER, TextureManager::filepathWithColor},
	{TYPE_ANIMATION, TextureManager::filepathWithColor},
	{TYPE_DIRECTION, TextureManager::filepathWithColor},
	{TYPE_ANIMATION_DIRECTION, TextureManager::filepathWithColor},
};
std::unordered_map<ObjectType, std::vector<std::string>> TextureManager::typeToFilenames = {
	{TYPE_TEXT, TextureManager::textFiles},
	{TYPE_TILED, TextureManager::tiledFiles},
	{TYPE_STATIC, TextureManager::staticFiles},
	{TYPE_CHARACTER, TextureManager::characterFiles},
	{TYPE_ANIMATION, TextureManager::animationFiles},
	{TYPE_DIRECTION, TextureManager::directionFiles},
	{TYPE_ANIMATION_DIRECTION, TextureManager::animationDirectionFiles},
};
std::unordered_map<ObjectId, uint8_t> TextureManager::objectZIndex = {
	{GAMEOBJECT_WATER, 2},
	{GAMEOBJECT_LAVA, 2},
	{GAMEOBJECT_BOG, 2},
	{GAMEOBJECT_TILE, 4},
	{GAMEOBJECT_ICE, 9},
	{GAMEOBJECT_GRASS, 10},
	{GAMEOBJECT_BRICK, 10},
	{GAMEOBJECT_FLOWER, 12},
	{GAMEOBJECT_BUBBLE, 12},
	{GAMEOBJECT_VIOLET, 12},
	{GAMEOBJECT_STUMP, 12},
	{GAMEOBJECT_WALL, 14},
	{GAMEOBJECT_HEDGE, 14},
	{GAMEOBJECT_PIPE, 14},
	{GAMEOBJECT_ALGAE, 15},
	{GAMEOBJECT_DOOR, 15},
	{GAMEOBJECT_HUSK, 15},
	{GAMEOBJECT_ROCK, 16},
	{GAMEOBJECT_SATR, 16},
	{GAMEOBJECT_LOVE, 16},
	{GAMEOBJECT_PILLAR, 16},
	{GAMEOBJECT_KEY, 16},
	{GAMEOBJECT_ROSE, 16},
	{GAMEOBJECT_COG, 16},
	{GAMEOBJECT_BOLT, 16},
	{GAMEOBJECT_REED, 16},
	{GAMEOBJECT_BOX, 16},
	{GAMEOBJECT_TREE, 16},
	{GAMEOBJECT_FLAG, 17},
	{GAMEOBJECT_SKULL, 17},
	{GAMEOBJECT_JELLY, 17},
	{GAMEOBJECT_CRAB, 17},
	{GAMEOBJECT_ROBOT, 17},
	{GAMEOBJECT_GHOST, 17},
	{GAMEOBJECT_STATUE, 17},
	{GAMEOBJECT_BABA, 18},
	{GAMEOBJECT_KEKE, 18},

	{TEXTOBJECT_IS, 20},
	{TEXTOBJECT_AND, 20},
	{TEXTOBJECT_HAS, 20},

	{GAMEOBJECT_TEXTS, 20},
	{TEXTOBJECT_TEXT, 20},
	{TEXTOBJECT_BABA, 20},
	{TEXTOBJECT_FLAG, 20},
	{TEXTOBJECT_WALL, 20},
	{TEXTOBJECT_ROCK, 20},
	{TEXTOBJECT_TILE, 20},
	{TEXTOBJECT_GRASS, 20},
	{TEXTOBJECT_WATER, 20},
	{TEXTOBJECT_SKULL, 20},
	{TEXTOBJECT_LAVA, 20},
	{TEXTOBJECT_FLOWER, 20},
	{TEXTOBJECT_BRICK, 20},
	{TEXTOBJECT_ICE, 20},
	{TEXTOBJECT_JELLY, 20},
	{TEXTOBJECT_ALGAE, 20},
	{TEXTOBJECT_CRAB, 20},
	{TEXTOBJECT_STAR, 20},
	{TEXTOBJECT_KEKE, 20},
	{TEXTOBJECT_LOVE, 20},
	{TEXTOBJECT_PILLAR, 20},
	{TEXTOBJECT_BUBBLE, 20},
	{TEXTOBJECT_KEY, 20},
	{TEXTOBJECT_DOOR, 20},
	{TEXTOBJECT_HEDGE, 20},
	{TEXTOBJECT_ROSE, 20},
	{TEXTOBJECT_VIOLET, 20},
	{TEXTOBJECT_COG, 20},
	{TEXTOBJECT_PIPE, 20},
	{TEXTOBJECT_ROBOT, 20},
	{TEXTOBJECT_BOLT, 20},
	{TEXTOBJECT_REED, 20},
	{TEXTOBJECT_BOG, 20},
	{TEXTOBJECT_BOX, 20},
	{TEXTOBJECT_HUSK, 20},
	{TEXTOBJECT_STUMP, 20},
	{TEXTOBJECT_TREE, 20},
	{TEXTOBJECT_GHOST, 20},
	{TEXTOBJECT_STATUE, 20},

	{TEXTOBJECT_YOU, 20},
	{TEXTOBJECT_WIN, 20},
	{TEXTOBJECT_STOP, 20},
	{TEXTOBJECT_PUSH, 20},
	{TEXTOBJECT_SINK, 20},
	{TEXTOBJECT_DEFEAT, 20},
	{TEXTOBJECT_MELT, 20},
	{TEXTOBJECT_HOT, 20},
	{TEXTOBJECT_MOVE, 20},
	{TEXTOBJECT_SHUT, 20},
	{TEXTOBJECT_OPEN, 20},
	{TEXTOBJECT_RED, 20},
	{TEXTOBJECT_BLUE, 20},
	{TEXTOBJECT_FLOAT, 20},
	{TEXTOBJECT_WEAK, 20},

	{OBJECT_CROSSED, 21},
};

void TextureManager::Clear() {
	textures.clear();
}

int TextureManager::GetTextureSize() {
	return textureSize;
}

POINT TextureManager::GetTextureOrogionPosition() {
	return textureOrigionPosition;
}

int TextureManager::GetZIndex(ObjectId objectId) {
	if (objectZIndex.find(objectId) == objectZIndex.end()) {
		Log::LogError("<Texture Manager> can not find object z-index whith id %d", objectId);
	}
	return objectZIndex[objectId];
}

game_framework::CMovingBitmap TextureManager::GetTexture(ObjectId objectId, PropertyId colorPropertyId) {
	if (textures.find(textureIndex(objectId, colorPropertyId)) == textures.end()) {
		Log::LogError("<Texture Manager> Can not find texture with obejct id %d and color property id %d", objectId, colorPropertyId);
	}
	return textures[textureIndex(objectId, colorPropertyId)];
}

void TextureManager::SetTextureSize(int size) {
	textureSize = size;
}

void TextureManager::SetTextureOrigionPosition(POINT position) {
	textureOrigionPosition = position;
}

void TextureManager::LoadTexture(TextureInfo info) {
	ObjectId objectId = ObjectIdProc::GetIdByName(info.objectName);
	ObjectType objectType = ObjectTypeProc::GetType(objectId);
	uint32_t index = textureIndex(objectId, info.colorId);
	textures[index] = loadBitmap(getFiles(typeToGetPath[objectType](info), typeToFilenames[objectType]));
}


uint32_t TextureManager::textureIndex(ObjectId objectId, PropertyId colorId) {
	return ((uint32_t)colorId << 16) | objectId;
}

std::string TextureManager::filepathWithColor(TextureInfo &info) {
	return "./Resources/Sprites/" +
		info.objectName + "/" +
		intToString(info.world) + "/" +
		intToString(textureSize) + "/" +
		PropertyIdProc::GetColorName(info.colorId) + "/";
}

std::string TextureManager::filepathWithoutColor(TextureInfo &info) {
	return "./Resources/Sprites/" +
		info.objectName + "/" +
		intToString(info.world) + "/" +
		intToString(textureSize) + "/";
}

std::vector<std::string> TextureManager::getFiles(std::string filepath, std::vector<std::string> &filenames) {
	std::vector<std::string> files;
	for (std::string &filename : filenames)
		files.push_back(filepath + filename);
	return files;
}

game_framework::CMovingBitmap TextureManager::loadBitmap(std::vector<std::string> &files) {
	game_framework::CMovingBitmap result;
	result.LoadBitmapByString(files, 0x00FF00);
	return result;
}