#pragma once

#include <unordered_map>
#include "gameobject_id.h"
#include "gameobject_properties.h"

int GetPropIdFromTextGameobject(GameobjectId gameobjectId);

class GameobjectPropsManager {
private:
	std::unordered_map<GameobjectId, GameobjectProps> propsGroup;

public:
	GameobjectPropsManager();

	bool GetGameobjectProp(GameobjectId gameobjectId, PropId propId);
	void SetGameobjectProp(GameobjectId gameobjectId, PropId propId, bool value = true);

	void SetPropWithOtherProp(PropId targetPropId, PropId newPropId, bool value = true);

	void ClearProperties();
};