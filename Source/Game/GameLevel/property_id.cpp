#include "stdafx.h"
#include "property_id.h"
#include "../../Expansion/log.h"

int GetPropIdByName(std::string propName) {
	if (propName == "prop_you") {
		return PROP_YOU;
	}
	if (propName == "prop_push") {
		return PROP_PUSH;
	}
	if (propName == "prop_stop") {
		return PROP_STOP;
	}
	if (propName == "prop_win") {
		return PROP_WIN;
	}
	if (propName == "prop_sink") {
		return PROP_SINK;
	}
	if (propName == "prop_defeat") {
		return PROP_DEFEAT;
	}
	if (propName == "prop_melt") {
		return PROP_MELT;
	}
	if (propName == "prop_none") {
		return PROP_NONE;
	}
	
	char messageBuffer[215];
	sprintf_s(messageBuffer, "Error when get prop id by prop name. Didn't has property named \"%s\"", propName.c_str());
	logError(messageBuffer);
	return -1;
}

std::string GetColorDirByPropId(PropId propId) {
	switch (propId) {
	case PROP_NONE:
		return "default";
	default:
		return "default";
	}
}