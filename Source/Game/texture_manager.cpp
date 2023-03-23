#include "stdafx.h"
#include "texture_manager.h"
#include "../Expansion/log.h"

std::unordered_map<uint64_t, game_framework::CMovingBitmap> TextureManager::textures = std::unordered_map<uint64_t, game_framework::CMovingBitmap>();

void TextureManager::LoadTexture(GameobjectId gameobjectId, PropId colorPropId, int world) {
	int typeNum = GetGameobjectTypeById(gameobjectId);
	if (typeNum == -1) {
		char message[125];
		sprintf_s(message, "type of gameobject with id '%d' not found", gameobjectId);
		logError(message);
	}

	switch (static_cast<GameobjectType>(typeNum)) {
	case OBJECT_TYPE_CHARACTER:
		loadCharacterTexture(gameobjectId, colorPropId, world);
		break;
	case OBJECT_TYPE_DIRECTIONAL:
		loadDirectionalTexture(gameobjectId, colorPropId, world);
		break;
	case OBJECT_TYPE_TILED:
		loadTiledTexture(gameobjectId, colorPropId, world);
		break;
	case OBJECT_TYPE_STATIC:
		loadStaticTexture(gameobjectId, colorPropId, world);
		break;
	case OBJECT_TYPE_TEXT:
		loadTextTexture(gameobjectId, colorPropId, world);
	}

	char message[125];
	sprintf_s(message, "loaded texture of %s with prop %d", GetGameobjectNameById(gameobjectId).c_str(), colorPropId);
	logInfo(message);
}
void TextureManager::Clear() {
	textures.clear();
}

void TextureManager::loadCharacterTexture(GameobjectId gameobjectId, PropId colorPropId, int world) {
	std::string textureDir = GetTexturePathByGameobjectId(gameobjectId) + "0/" + GetColorDirByPropId(colorPropId) + "/";
	game_framework::CMovingBitmap texture;
	std::vector<std::string> texturePaths;

	texturePaths.push_back(textureDir + "0_1.bmp");
	texturePaths.push_back(textureDir + "0_2.bmp");
	texturePaths.push_back(textureDir + "0_3.bmp");
	texturePaths.push_back(textureDir + "1_1.bmp");
	texturePaths.push_back(textureDir + "1_2.bmp");
	texturePaths.push_back(textureDir + "1_3.bmp");
	texturePaths.push_back(textureDir + "2_1.bmp");
	texturePaths.push_back(textureDir + "2_2.bmp");
	texturePaths.push_back(textureDir + "2_3.bmp");
	texturePaths.push_back(textureDir + "3_1.bmp");
	texturePaths.push_back(textureDir + "3_2.bmp");
	texturePaths.push_back(textureDir + "3_3.bmp");
	texturePaths.push_back(textureDir + "8_1.bmp");
	texturePaths.push_back(textureDir + "8_2.bmp");
	texturePaths.push_back(textureDir + "8_3.bmp");
	texturePaths.push_back(textureDir + "9_1.bmp");
	texturePaths.push_back(textureDir + "9_2.bmp");
	texturePaths.push_back(textureDir + "9_3.bmp");
	texturePaths.push_back(textureDir + "10_1.bmp");
	texturePaths.push_back(textureDir + "10_2.bmp");
	texturePaths.push_back(textureDir + "10_3.bmp");
	texturePaths.push_back(textureDir + "11_1.bmp");
	texturePaths.push_back(textureDir + "11_2.bmp");
	texturePaths.push_back(textureDir + "11_3.bmp");
	texturePaths.push_back(textureDir + "16_1.bmp");
	texturePaths.push_back(textureDir + "16_2.bmp");
	texturePaths.push_back(textureDir + "16_3.bmp");
	texturePaths.push_back(textureDir + "17_1.bmp");
	texturePaths.push_back(textureDir + "17_2.bmp");
	texturePaths.push_back(textureDir + "17_3.bmp");
	texturePaths.push_back(textureDir + "18_1.bmp");
	texturePaths.push_back(textureDir + "18_2.bmp");
	texturePaths.push_back(textureDir + "18_3.bmp");
	texturePaths.push_back(textureDir + "19_1.bmp");
	texturePaths.push_back(textureDir + "19_2.bmp");
	texturePaths.push_back(textureDir + "19_3.bmp");
	texturePaths.push_back(textureDir + "24_1.bmp");
	texturePaths.push_back(textureDir + "24_2.bmp");
	texturePaths.push_back(textureDir + "24_3.bmp");
	texturePaths.push_back(textureDir + "25_1.bmp");
	texturePaths.push_back(textureDir + "25_2.bmp");
	texturePaths.push_back(textureDir + "25_3.bmp");
	texturePaths.push_back(textureDir + "26_1.bmp");
	texturePaths.push_back(textureDir + "26_2.bmp");
	texturePaths.push_back(textureDir + "26_3.bmp");
	texturePaths.push_back(textureDir + "27_1.bmp");
	texturePaths.push_back(textureDir + "27_2.bmp");
	texturePaths.push_back(textureDir + "27_3.bmp");

	texture.LoadBitmapByString(texturePaths, 0x00FF00);

	uint64_t textureKey = ((uint64_t)gameobjectId << 32) | colorPropId;
	textures[textureKey] = texture;
}
void TextureManager::loadDirectionalTexture(GameobjectId gameobjectId, PropId colorPropId, int world) {
	std::string textureDir = GetTexturePathByGameobjectId(gameobjectId) + "0/" + GetColorDirByPropId(colorPropId) + "/";
	game_framework::CMovingBitmap texture;
	std::vector<std::string> texturePaths;

	texturePaths.push_back(textureDir + "0_1.bmp");
	texturePaths.push_back(textureDir + "0_2.bmp");
	texturePaths.push_back(textureDir + "0_3.bmp");
	texturePaths.push_back(textureDir + "8_1.bmp");
	texturePaths.push_back(textureDir + "8_2.bmp");
	texturePaths.push_back(textureDir + "8_3.bmp");
	texturePaths.push_back(textureDir + "16_1.bmp");
	texturePaths.push_back(textureDir + "16_2.bmp");
	texturePaths.push_back(textureDir + "16_3.bmp");
	texturePaths.push_back(textureDir + "24_1.bmp");
	texturePaths.push_back(textureDir + "24_2.bmp");
	texturePaths.push_back(textureDir + "24_3.bmp");

	texture.LoadBitmapByString(texturePaths, 0x00FF00);

	uint64_t textureKey = ((uint64_t)gameobjectId << 32) + colorPropId;
	textures[textureKey] = texture;
}
void TextureManager::loadTiledTexture(GameobjectId gameobjectId, PropId colorPropId, int world) {
	std::string textureDir = GetTexturePathByGameobjectId(gameobjectId) + "0/" + GetColorDirByPropId(colorPropId) + "/";
	game_framework::CMovingBitmap texture;
	std::vector<std::string> texturePaths;

	texturePaths.push_back(textureDir + "0_1.bmp");
	texturePaths.push_back(textureDir + "0_2.bmp");
	texturePaths.push_back(textureDir + "0_3.bmp");
	texturePaths.push_back(textureDir + "1_1.bmp");
	texturePaths.push_back(textureDir + "1_2.bmp");
	texturePaths.push_back(textureDir + "1_3.bmp");
	texturePaths.push_back(textureDir + "2_1.bmp");
	texturePaths.push_back(textureDir + "2_2.bmp");
	texturePaths.push_back(textureDir + "2_3.bmp");
	texturePaths.push_back(textureDir + "3_1.bmp");
	texturePaths.push_back(textureDir + "3_2.bmp");
	texturePaths.push_back(textureDir + "3_3.bmp");
	texturePaths.push_back(textureDir + "4_1.bmp");
	texturePaths.push_back(textureDir + "4_2.bmp");
	texturePaths.push_back(textureDir + "4_3.bmp");
	texturePaths.push_back(textureDir + "5_1.bmp");
	texturePaths.push_back(textureDir + "5_2.bmp");
	texturePaths.push_back(textureDir + "5_3.bmp");
	texturePaths.push_back(textureDir + "6_1.bmp");
	texturePaths.push_back(textureDir + "6_2.bmp");
	texturePaths.push_back(textureDir + "6_3.bmp");
	texturePaths.push_back(textureDir + "7_1.bmp");
	texturePaths.push_back(textureDir + "7_2.bmp");
	texturePaths.push_back(textureDir + "7_3.bmp");
	texturePaths.push_back(textureDir + "8_1.bmp");
	texturePaths.push_back(textureDir + "8_2.bmp");
	texturePaths.push_back(textureDir + "8_3.bmp");
	texturePaths.push_back(textureDir + "9_1.bmp");
	texturePaths.push_back(textureDir + "9_2.bmp");
	texturePaths.push_back(textureDir + "9_3.bmp");
	texturePaths.push_back(textureDir + "10_1.bmp");
	texturePaths.push_back(textureDir + "10_2.bmp");
	texturePaths.push_back(textureDir + "10_3.bmp");
	texturePaths.push_back(textureDir + "11_1.bmp");
	texturePaths.push_back(textureDir + "11_2.bmp");
	texturePaths.push_back(textureDir + "11_3.bmp");
	texturePaths.push_back(textureDir + "12_1.bmp");
	texturePaths.push_back(textureDir + "12_2.bmp");
	texturePaths.push_back(textureDir + "12_3.bmp");
	texturePaths.push_back(textureDir + "13_1.bmp");
	texturePaths.push_back(textureDir + "13_2.bmp");
	texturePaths.push_back(textureDir + "13_3.bmp");
	texturePaths.push_back(textureDir + "14_1.bmp");
	texturePaths.push_back(textureDir + "14_2.bmp");
	texturePaths.push_back(textureDir + "14_3.bmp");
	texturePaths.push_back(textureDir + "15_1.bmp");
	texturePaths.push_back(textureDir + "15_2.bmp");
	texturePaths.push_back(textureDir + "15_3.bmp");

	texture.LoadBitmapByString(texturePaths, 0x00FF00);

	uint64_t textureKey = ((uint64_t)gameobjectId << 32) | colorPropId;
	textures[textureKey] = texture;
}
void TextureManager::loadStaticTexture(GameobjectId gameobjectId, PropId colorPropId, int world) {
	std::string textureDir = GetTexturePathByGameobjectId(gameobjectId) + "0/" + GetColorDirByPropId(colorPropId) + "/";
	game_framework::CMovingBitmap texture;
	std::vector<std::string> texturePaths;

	texturePaths.push_back(textureDir + "0_1.bmp");
	texturePaths.push_back(textureDir + "0_2.bmp");
	texturePaths.push_back(textureDir + "0_3.bmp");

	texture.LoadBitmapByString(texturePaths, 0x00FF00);

	uint64_t textureKey = ((uint64_t)gameobjectId << 32) | colorPropId;
	textures[textureKey] = texture;
}

void TextureManager::loadTextTexture(GameobjectId gameobjectId, PropId colorPropId, int world) {
	std::string textureDir = GetTexturePathByGameobjectId(gameobjectId) + "0/";
	game_framework::CMovingBitmap texture;
	std::vector<std::string> texturePaths;

	texturePaths.push_back(textureDir + "dark/0_1.bmp");
	texturePaths.push_back(textureDir + "dark/0_2.bmp");
	texturePaths.push_back(textureDir + "dark/0_3.bmp");
	texturePaths.push_back(textureDir + "light/0_1.bmp");
	texturePaths.push_back(textureDir + "light/0_2.bmp");
	texturePaths.push_back(textureDir + "light/0_3.bmp");

	texture.LoadBitmapByString(texturePaths, 0x00FF00);

	uint64_t textureKey = ((uint64_t)gameobjectId << 32) | colorPropId;
	textures[textureKey] = texture;
}

game_framework::CMovingBitmap TextureManager::GetGameobjecTexture(GameobjectId gameobjectId, PropId colorPropId) {
	uint64_t textureKey = ((uint64_t)gameobjectId << 32) | colorPropId;

	if (textures.find(textureKey) == textures.end()) {
		char message[125];
		sprintf_s(message, "didn't load texture for %s with prop %d", GetGameobjectNameById(gameobjectId).c_str(), colorPropId);
		logError(message);
	}

	return textures[textureKey];
}