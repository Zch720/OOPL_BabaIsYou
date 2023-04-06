#pragma once

#include "property_id.h"
#include "../../Expansion/point.h"

class PropertyProc {
private:
	static bool checkPropOverlap(PropId, PropId);
	static bool checkBlockPropOverlap(Point, PropId, PropId);
	static void checkOverlapPropFull_You_Win();
	static void checkOverlapPropBlock_Sink(Point);
	static void deleteOverlapPropBoth(Point, PropId, PropId);
	static void deleteOverlapPropSecond(Point, PropId, PropId);

public:
	static bool CheckHasPropInBlock(Point position, PropId propId);
	static void CheckAllOverlapProp();
	static void LoadTextObjectsPushProp();
	static void UpdatePropsManager();
};