#include "stdafx.h"
#include "texture_manager.h"
#include "../../Expansion/log.h"
#include "../../Expansion/string_proc.h"

#define REMOVE_COLOR		0x00FF00

int TextureManager::world = -1;
int TextureManager::textureSize = 0;
std::string TextureManager::worldTextureDir = "";
std::unordered_map<uint64_t, game_framework::CMovingBitmap> TextureManager::textures = std::unordered_map<uint64_t, game_framework::CMovingBitmap>();

std::vector<std::string> characterTextureFiles = {
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
std::vector<std::string> directinalTextureFiles = {
	"0_1.bmp", "0_2.bmp", "0_3.bmp",
	"8_1.bmp", "8_2.bmp", "8_3.bmp",
	"16_1.bmp", "16_2.bmp", "16_3.bmp",
	"24_1.bmp", "24_2.bmp", "24_3.bmp",
};
std::vector<std::string> tiledTextureFiles = {
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
std::vector<std::string> staticTextureFiles = {
	"0_1.bmp", "0_2.bmp", "0_3.bmp",
};
std::vector<std::string> textTextureFiles = {
	"dark/0_1.bmp", "dark/0_2.bmp", "dark/0_3.bmp",
	"light/0_1.bmp", "light/0_2.bmp", "light/0_3.bmp",
};


int TextureManager::GetTextureSize() {
	return TextureManager::textureSize;
}

void TextureManager::SetDirInfo(int world, int textureSize) {
	TextureManager::world = world;
	TextureManager::textureSize = textureSize;
	TextureManager::worldTextureDir = intToString(world) + "/" + intToString(textureSize) + "/";
}

void TextureManager::LoadTexture(GameobjectId gameobjectId, PropId colorPropId) {
	if (textures.find(getTexturesKey(gameobjectId, colorPropId)) != textures.end()) return;

	int typeNum = GetGameobjectTypeById(gameobjectId);
	if (typeNum == -1) {
		Log::LogError("type of gameobject with id '%d' not found", gameobjectId);
	}

	switch (static_cast<GameobjectType>(typeNum)) {
	case OBJECT_TYPE_CHARACTER:
		textures[getTexturesKey(gameobjectId, colorPropId)] =
			loadTexture(getTextureDirWithColor(gameobjectId, colorPropId), characterTextureFiles);
		break;
	case OBJECT_TYPE_DIRECTIONAL:
		textures[getTexturesKey(gameobjectId, colorPropId)] =
			loadTexture(getTextureDirWithColor(gameobjectId, colorPropId), directinalTextureFiles);
		break;
	case OBJECT_TYPE_TILED:
		textures[getTexturesKey(gameobjectId, colorPropId)] =
			loadTexture(getTextureDirWithColor(gameobjectId, colorPropId), tiledTextureFiles);
		break;
	case OBJECT_TYPE_STATIC:
		textures[getTexturesKey(gameobjectId, colorPropId)] =
			loadTexture(getTextureDirWithColor(gameobjectId, colorPropId), staticTextureFiles);
		break;
	case OBJECT_TYPE_TEXT:
		textures[getTexturesKey(gameobjectId, colorPropId)] =
			loadTexture(getTextureDirWithoutColor(gameobjectId, colorPropId), textTextureFiles);
		break;
	}

	Log::LogInfo("loaded texture of %s with prop %d", GetGameobjectNameById(gameobjectId).c_str(), colorPropId);
}

uint64_t TextureManager::getTexturesKey(GameobjectId gameobjectId, PropId propId) {
	return ((uint64_t)world << 48) | ((uint64_t)textureSize << 32) | ((uint64_t)gameobjectId << 16) | propId;
}

std::string TextureManager::getTextureDirWithColor(GameobjectId gameobjectId, PropId colorPropId) {
	return GetTexturePathByGameobjectId(gameobjectId)
		+ TextureManager::worldTextureDir
		+ GetColorDirByPropId(colorPropId) + "/";
}
std::string TextureManager::getTextureDirWithoutColor(GameobjectId gameobjectId, PropId colorPropId) {
	return GetTexturePathByGameobjectId(gameobjectId)
		+ TextureManager::worldTextureDir;
}

game_framework::CMovingBitmap TextureManager::loadTexture(std::string textureDir, std::vector<std::string> &files) {
	game_framework::CMovingBitmap texture;
	std::vector<std::string> texturePaths;

	for (std::string file : files) {
		texturePaths.push_back(textureDir + file);
	}

	texture.LoadBitmapByString(texturePaths, REMOVE_COLOR);
	return texture;
}

game_framework::CMovingBitmap TextureManager::GetGameobjecTexture(GameobjectId gameobjectId, PropId colorPropId) {
	auto it = textures.find(getTexturesKey(gameobjectId, colorPropId));

	if (it == textures.end()) {
		Log::LogError("didn't load texture for %s with prop %d", GetGameobjectNameById(gameobjectId).c_str(), colorPropId);
	}

	return it->second;
}