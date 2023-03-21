#pragma once

#include <unordered_map>
#include "property_id.h"

class GameobjectPropsManager;

class GameobjectProps {
private:
	std::unordered_map<PropId, bool> props;

	friend GameobjectPropsManager;

public:
	GameobjectProps();
};