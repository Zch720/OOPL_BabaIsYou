#pragma once

#include <unordered_map>
#include "property_id.h"
#include "gameobject_id.h"
#include "gameobject_type.h"
#include "../../Expansion/point.h"
#include "../../Library/gameutil.h"

class TextureManager {
private:
	static int textureSize;
	static Point textureOriginPosition;
	static std::string worldTextureDir;
	static std::unordered_map<uint64_t, game_framework::CMovingBitmap> textures;
	static std::unordered_map<GameobjectId, uint8_t> texturesWorld;
	
	static void setWorldDir(int world);

	static uint64_t getTexturesKey(int world, GameobjectId gameobjectId, PropId propId);
	static std::string getTextureDirWithColor(GameobjectId, PropId);
	static std::string getTextureDirWithoutColor(GameobjectId, PropId);

	static game_framework::CMovingBitmap loadTexture(std::string, std::vector<std::string>&);

public:
	static void Reset();

	static int GetTextureSize();

	static void SetTextureSize(int textureSize);
	static void SetTextureOriginPosition(int x, int y);

	static Point GetTextureOriginPosition();

	static void LoadTexture(int world, GameobjectId gameobjectId, PropId propId);

	static game_framework::CMovingBitmap GetGameobjecTexture(GameobjectId gameobjectId, PropId colorPropId);
};