#pragma once

#include <unordered_map>
#include "gameobject_id.h"
#include "gameobject_properties.h"

int GetPropIdFromTextGameobject(GameobjectId gameobjectId);

class GameobjectPropsManager {
private:
	static std::unordered_map<GameobjectId, GameobjectProps> propsGroup;

public:
	static bool GetGameobjectProp(GameobjectId gameobjectId, PropId propId);
	static void SetGameobjectProp(GameobjectId gameobjectId, PropId propId, bool value = true);

	static int GetColorProp(GameobjectId gameobjectId);

	static void SetPropWithOtherProp(PropId targetPropId, PropId newPropId, bool value = true);

	static void ClearProperties();
	static void ClearPropertiesWithoutTextPush();
};