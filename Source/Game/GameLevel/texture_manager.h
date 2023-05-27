#pragma once

#include <functional>
#include <vector>
#include <unordered_map>
#include "../../Library/gameutil.h"
#include "object_id.h"
#include "textobject_id.h"
#include "property_id.h"
#include "object_type.h"

class TextureManager {
public:
	struct TextureInfo {
		int world;
		PropertyId colorId;
		std::string objectName;
	};

private:
	static int textureSize;
	static POINT textureOrigionPosition;
	static std::vector<std::string> textFiles;
	static std::vector<std::string> tiledFiles;
	static std::vector<std::string> staticFiles;
	static std::vector<std::string> characterFiles;
	static std::vector<std::string> animationFiles;
	static std::vector<std::string> directionFiles;
	static std::vector<std::string> animationDirectionFiles;
	static std::unordered_map<uint32_t, game_framework::CMovingBitmap> textures;
	static std::unordered_map<ObjectType, std::function<std::string(TextureInfo&)>> typeToGetPath;
	static std::unordered_map<ObjectType, std::vector<std::string>> typeToFilenames;
	static std::unordered_map<ObjectId, uint8_t> objectZIndex;

	static inline uint32_t textureIndex(ObjectId objectId, PropertyId colorId);
	static inline std::string filepathWithColor(TextureInfo &info);
	static inline std::string filepathWithoutColor(TextureInfo &info);
	static std::vector<std::string> getFiles(std::string filepath, std::vector<std::string> &filenames);
	static game_framework::CMovingBitmap loadBitmap(std::vector<std::string> &files);

public:
	static void Clear();

	static int GetTextureSize();
	static POINT GetTextureOrogionPosition();
	static int GetZIndex(ObjectId objectId);
	static game_framework::CMovingBitmap GetTexture(ObjectId objectId, PropertyId colorPropertyId);

	static void SetTextureSize(int textureSize);
	static void SetTextureOrigionPosition(POINT position);

	static void LoadTexture(TextureInfo info);
};