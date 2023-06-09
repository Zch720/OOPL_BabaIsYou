#pragma once

#include "block.h"
#include "../../Library/gameutil.h"
#include "../../Expansion/vector2d.hpp"
#include "../style.h"

class LevelData {
public:
	struct GenObjectInfo {
		ObjectId objectId;
		Direction textureDirection;
	};

private:
	typedef std::vector<std::string> Datas;
	typedef std::function<void(ObjectBase&)> ObjectProcFunc;

	static game_framework::CMovingBitmap background;

	static std::string worldTitle;
	static std::string levelTitle;
	static Style worldMainStyle;

	static vector2d<Block> gameboard;
	static int genIdCounter;
	static bool isWin;

	static void createGameboard(int width, int height);

	static ObjectBase *getNewObject(ObjectType objectType);

	static std::vector<Datas> splitLevelDatas(std::string &origionData);
	static void loadLevel_checkTitle(std::string title, std::string targetTitle);
	static void loadLevel_Background(int level);
	static void loadLevel_Title(Datas &data);
	static void loadLevel_Style(Datas &data);
	static void loadLevel_GameboardSize(Datas &data);
	static void loadLevel_TextureOrigionPosition(Datas &data);
	static void loadLevel_TextureSize(Datas &data);
	static void loadLevel_NeededTextures(Datas &data);
	static void loadLevel_Objects(Datas &data);

	static int objectConnectStateCheck(ObjectInfo &info, Point offset, int connectValue);

public:
	static void Clear();

	static void Reset();
	static void LoadLevel(int level);

	static bool IsWin();
	static bool IsInsideGameboard(POINT position);
	static bool IsBlockEmpty(POINT position);
	static bool IsPropertyOverlapBlock(POINT position, PropertyId propertyId1, PropertyId propertyId2);
	static bool IsPropertyOverlap(PropertyId propertyId1, PropertyId propertyId2);

	static bool HasYouObjectInGameboard();
	static bool HasTextobjectInBlock(POINT position);
	
	static std::string GetWorldTitle();
	static std::string GetLevelTitle();
	static std::string GetFullTitle();
	static Style GetWorldMainStyle();

	static ObjectBase& GetTextobjectInBlock(POINT position);
	static ObjectBase& GetBlockObject(POINT position, int genId);
	static ObjectBase& GetBlockObject(ObjectInfo objectInfo);
	static int GetGameboardWidth();
	static int GetGameboardHeight();
	static game_framework::CMovingBitmap& GetBackground();
	static int GetGameobjectConnectState(ObjectInfo objectInfo);
	static std::vector<ObjectId> GetBlockObjectIds(POINT position);
	
	static ObjectBase& GetFirstObjectWithoutGenIdWithoutFloat(POINT position, int genId);
	static ObjectBase& GetFirstObjectWithObjectIdWithoutFloat(POINT position, ObjectId objectId);
	static ObjectBase& GetFirstObjectWithoutObjectIdWithoutFloat(POINT position, ObjectId objectId);
	static ObjectBase& GetFirstObjectWithPropertyWithoutFloat(POINT position, PropertyId propertyId);
	static ObjectBase& GetFirstObjectWithoutPropertyWithoutFloat(POINT position, PropertyId propertyId);

	static ObjectBase& GetFirstObjectWithoutGenIdWithFloat(POINT position, int genId);
	static ObjectBase& GetFirstObjectWithObjectIdWithFloat(POINT position, ObjectId objectId);
	static ObjectBase& GetFirstObjectWithoutObjectIdWithFloat(POINT position, ObjectId objectId);
	static ObjectBase& GetFirstObjectWithPropertyWithFloat(POINT position, PropertyId propertyId);
	static ObjectBase& GetFirstObjectWithoutPropertyWithFloat(POINT position, PropertyId propertyId);

	static void SetIsWin(bool isWin);

	static ObjectInfo GenObjectWithGenId(POINT position, GenObjectInfo genInfo, int genId);
	static ObjectInfo GenNewObject(POINT position, GenObjectInfo genInfo);
	static void DeleteObject(POINT position, int genId);
	static void MoveObject(ObjectInfo info, POINT position);
	static void ReplaceObject(ObjectInfo info, ObjectId convertObjectId);
	static void RemoveEmptyObjects();

	static void GameboardForeach(vector2d<Block>::ElementProcFunc procFunc);
	static void BlockObjectForeach(POINT position, ObjectProcFunc procFunc);
	static void AllObjectForeach(ObjectProcFunc procFunc);
};