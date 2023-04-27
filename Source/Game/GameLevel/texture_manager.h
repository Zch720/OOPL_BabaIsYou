#pragma once

#include <unordered_map>
#include "property_id.h"
#include "gameobject_id.h"
#include "gameobject_type.h"
#include "../../Expansion/point.h"
#include "../../Library/gameutil.h"

class TextureManager {
private:
	static int world;
	static int textureSize;
	static Point textureOriginPosition;
	static std::string worldTextureDir;
	static std::unordered_map<uint64_t, game_framework::CMovingBitmap> textures;

	static uint64_t getTexturesKey(GameobjectId gameobjectId, PropId propId);
	static std::string getTextureDirWithColor(GameobjectId, PropId);
	static std::string getTextureDirWithoutColor(GameobjectId, PropId);

	static game_framework::CMovingBitmap loadTexture(std::string, std::vector<std::string>&);

public:
	static int GetTextureSize();

	static void SetDirInfo(int world, int textureSize);
	static void SetTextureOriginPosition(int x, int y);

	static Point GetTextureOriginPosition();

	static void LoadTexture(GameobjectId gameobjectId, PropId propId);

	static game_framework::CMovingBitmap GetGameobjecTexture(GameobjectId gameobjectId, PropId colorPropId);
};