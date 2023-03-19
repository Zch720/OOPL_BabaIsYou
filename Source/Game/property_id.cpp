#include "stdafx.h"
#include "property_id.h"
#include "../Expansion/log.h"

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
	
	char messageBuffer[215];
	sprintf_s(messageBuffer, "Error when get prop id by prop name. Didn't has property named \"%s\"", propName.c_str());
	logError(messageBuffer);
	return -1;
}