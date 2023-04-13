#pragma once

#include <unordered_map>
#include "property_id.h"
#include "gameobject_id.h"
#include "gameobject_type.h"
#include "../../Library/gameutil.h"

class TextureManager {
private:
	static std::unordered_map<uint64_t, game_framework::CMovingBitmap> textures;

	static void loadCharacterTexture(GameobjectId, PropId, int);
	static void loadDirectionalTexture(GameobjectId, PropId, int);
	static void loadTiledTexture(GameobjectId, PropId, int);
	static void loadStaticTexture(GameobjectId, PropId, int);
	static void loadTextTexture(GameobjectId, PropId, int);

public:
	static int textureSize;

	static void LoadTexture(GameobjectId gameobjectId, PropId propId, int world);
	static void Clear();

	static game_framework::CMovingBitmap GetGameobjecTexture(GameobjectId gameobjectId, PropId colorPropId);
};