#pragma once

#include "property_id.h"

class PropertyProc {
private:
	static bool checkPropOverlap(PropId, PropId);
	static bool checkBlockPropOverlap(CPoint, PropId, PropId);
	static void checkOverlapPropFull_You_Win();
	static void checkOverlapPropBlock_Sink(CPoint);
	static void deleteOverlapPropBoth(CPoint, PropId, PropId);
	static void deleteOverlapPropSecond(CPoint, PropId, PropId);

public:
	static bool CheckHasPropInBlock(CPoint position, PropId propId);
	static void CheckAllOverlapProp();
	static void LoadTextObjectsPushProp();
	static void UpdatePropsManager();
};