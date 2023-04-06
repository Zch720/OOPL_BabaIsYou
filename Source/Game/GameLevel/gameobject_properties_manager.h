#pragma once

#include <unordered_map>
#include <unordered_set>
#include "gameobject_id.h"
#include "gameobject_properties.h"

int GetPropIdFromTextGameobject(GameobjectId gameobjectId);

class GameobjectPropsManager {
private:
	static std::unordered_map<GameobjectId, GameobjectProps> propsGroup;

public:
	static bool GetGameobjectProp(GameobjectId gameobjectId, PropId propId);
	static void SetGameobjectProp(GameobjectId gameobjectId, PropId propId, bool value = true);
	static std::unordered_set<PropId> GetAllGameobjectProps(GameobjectId gameobjectId);

	static int GetColorProp(GameobjectId gameobjectId);

	static void SetPropWithOtherProp(PropId targetPropId, PropId newPropId, bool value = true);

	static bool CheckPropCanBeOffset(PropId propId1, PropId propId2);
	static bool CheckPropCanBeOffset(GameobjectId gameobjectId1, GameobjectId gameobjectId2);
	static bool CheckPropCanBeOffset(GameobjectId gameobjectId, std::vector<PropId> propIdArray);
	static bool CheckPropCanBeOffset(GameobjectId gameobjectId, std::vector<GameobjectId> gameobjectIdArray);
	static bool CheckPropCanBeOffset(GameobjectId gameobjectId, std::unordered_set<PropId> propIdSet);
	static bool CheckPropCanBeOffset(GameobjectId gameobjectId, std::unordered_set<GameobjectId> gameobjectIdSet);

	static void ClearProperties();
	static void ClearPropertiesWithoutTextPush();
};