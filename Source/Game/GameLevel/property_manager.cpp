#include "stdafx.h"
#include <algorithm>
#include "property_manager.h"
#include "../../Expansion/log.h"

PropertyManager::ObjectProperties PropertyManager::objectProperties = {};
PropertyManager::ObjectsConvert PropertyManager::objectsConvert = {};
PropertyManager::ObjectsHas PropertyManager::objectsHas = {};
std::vector<std::string> PropertyManager::propertyRules = {};
std::vector<std::string> PropertyManager::convertRules = {};
std::vector<std::string> PropertyManager::hasRules = {};
std::vector<std::string> PropertyManager::rules = {};

std::vector<std::string> PropertyManager::GetRules() {
	calculatePropertyRules();
	calculateConvertRules();
	calculateHasRules();
	rules.clear();
	rules.insert(rules.end(), propertyRules.begin(), propertyRules.end());
	rules.insert(rules.end(), convertRules.begin(), convertRules.end());
	rules.insert(rules.end(), hasRules.begin(), hasRules.end());
	return rules;
}

PropertyManager::ObjectProperties PropertyManager::GetDefaultObjectProperties() {
	ObjectProperties result = objectProperties;
	for (auto &objectProperty : result) {
		objectProperty.second.clear();
		if (ObjectIdProc::IsTextobjectId(objectProperty.first)) {
			objectProperty.second[PROPERTY_PUSH] = 1;
		}
	}
	return result;
}
PropertyManager::ObjectProperties& PropertyManager::GetObjectProperties() {
	return objectProperties;
}
void PropertyManager::SetObjectProperties(ObjectProperties &objectProperties) {
	PropertyManager::objectProperties = objectProperties;
}
PropertyManager::ObjectsConvert& PropertyManager::GetObjectsConvert() {
	return objectsConvert;
}
void PropertyManager::SetObjectsConvert(ObjectsConvert &objectsConvert) {
	PropertyManager::objectsConvert = objectsConvert;
}
PropertyManager::ObjectsHas& PropertyManager::GetObjectsHas() {
	return objectsHas;
}
void PropertyManager::SetObjectsHas(ObjectsHas &objectsHas) {
	PropertyManager::objectsHas = objectsHas;
}

void PropertyManager::Clear() {
	objectProperties.clear();
	objectsConvert.clear();
	objectsHas.clear();
}
void PropertyManager::Reset() {
	for (auto &objectProperty : objectProperties) {
		objectProperty.second.clear();
		if (ObjectIdProc::IsTextobjectId(objectProperty.first)) {
			objectProperty.second[PROPERTY_PUSH] = 1;
		}
	}
}
	
void PropertyManager::AddObjectProperty(ObjectId objectId, PropertyId propertyId) {
	if (objectId == GAMEOBJECT_TEXTS) addTextobjectProperty(propertyId);
	else objectProperties[objectId][propertyId] += 1;
}
void PropertyManager::RemoveObjectProperty(ObjectId objectId, PropertyId propertyId) {
	if (objectId == GAMEOBJECT_TEXTS) removeTextobjectProperty(propertyId);
	else objectProperties[objectId][propertyId] -= 1;
}
int PropertyManager::GetObjectProperty(ObjectId objectId, PropertyId propertyId) {
	return objectProperties[objectId][propertyId];
}
bool PropertyManager::ObjectHasProperty(ObjectId objectId, PropertyId propertyId) {
	return objectProperties[objectId][propertyId] != 0;
}
PropertyId PropertyManager::GetObjectColor(ObjectId objectId) {
	if (objectProperties[objectId][PROPERTY_RED] != 0) return PROPERTY_RED;
	if (objectProperties[objectId][PROPERTY_BLUE] != 0) return PROPERTY_BLUE;
	return PROPERTY_NONE;
}

void PropertyManager::RemoveOffsetObjects(std::vector<ObjectId> &objects1, std::vector<ObjectId> &objects2) {
	for (size_t i = 0; i < objects1.size(); i++) {
		for (size_t j = 0; j < objects2.size(); j++) {
			if (canBeOffset(objects1[i], objects2[j])) {
				objects1.erase(objects1.begin() + i);
				objects2.erase(objects2.begin() + j);
				i--;
				break;
			}
		}
	}
}

void PropertyManager::AddObjectConvert(ObjectId objectId, ObjectId convertObjectId) {
	objectsConvert[objectId] = convertObjectId;
}

void PropertyManager::RemoveObjectConvert(ObjectId objectId) {
	objectsConvert.erase(objectId);
}

ObjectId PropertyManager::GetObjectConvert(ObjectId objectId) {
	if (objectsConvert.find(objectId) == objectsConvert.end()) return OBJECT_NONE;
	return objectsConvert[objectId];
}

void PropertyManager::AddObjectHas(ObjectId objectId, ObjectId hasObjectId) {
	objectsHas[objectId].push_back(hasObjectId);
}

void PropertyManager::RemoveObjectHas(ObjectId objectId, ObjectId hasObjectId) {
	auto &hasObjects = objectsHas[objectId];
	hasObjects.erase(std::remove(hasObjects.begin(), hasObjects.end(), hasObjectId), hasObjects.end());
}

bool PropertyManager::ObjectHasObject(ObjectId objectId, ObjectId hasObjectId) {
	auto &hasObjects = objectsHas[objectId];
	return std::find(hasObjects.begin(), hasObjects.end(), hasObjectId) != hasObjects.end();
}

std::vector<ObjectId> PropertyManager::GetObjectHas(ObjectId objectId) {
	return objectsHas[objectId];
}

bool PropertyManager::canBeOffset(ObjectId objectId1, ObjectId objectId2) {
	return propertyOffset_OpenShut(objectId1, objectId2);
}

bool PropertyManager::propertyOffset_OpenShut(ObjectId propertyId1, ObjectId propertyId2) {
	return (ObjectHasProperty(propertyId1, PROPERTY_OPEN) && ObjectHasProperty(propertyId2, PROPERTY_SHUT)) ||
		(ObjectHasProperty(propertyId1, PROPERTY_SHUT) && ObjectHasProperty(propertyId2, PROPERTY_OPEN));
}

void PropertyManager::addTextobjectProperty(PropertyId propertyId) {
	objectProperties[GAMEOBJECT_TEXTS][propertyId] += 1;
	for (auto &objectProperty : objectProperties) {
		if (ObjectIdProc::IsTextobjectId(objectProperty.first)) {
			objectProperty.second[propertyId] += 1;
		}
	}
}

void PropertyManager::removeTextobjectProperty(PropertyId propertyId) {
	objectProperties[GAMEOBJECT_TEXTS][propertyId] -= 1;
	for (auto &objectProperty : objectProperties) {
		if (ObjectIdProc::IsTextobjectId(objectProperty.first)) {
			objectProperty.second[propertyId] -= 1;
		}
	}
}

void PropertyManager::calculatePropertyRules() {
	propertyRules.clear();
	for (auto &objectProperty : objectProperties) {
		for (auto &property : objectProperty.second) {
			if (property.second > 0) {
				if (ObjectIdProc::IsTextobjectId(objectProperty.first)) continue;
				std::string objectName = ObjectIdProc::GetNameById(objectProperty.first);
				std::string propertyName = PropertyIdProc::GetNameById(property.first).substr(5);
				std::transform(objectName.begin(), objectName.end(), objectName.begin(), ::toupper);
				std::transform(propertyName.begin(), propertyName.end(), propertyName.begin(), ::toupper);
				propertyRules.push_back(objectName + " IS " + propertyName);
			}
		}
	}
}

void PropertyManager::calculateConvertRules() {
	convertRules.clear();
	for (auto &objectConvert : objectsConvert) {
		std::string objectName = ObjectIdProc::GetNameById(objectConvert.first);
		std::string convertObjectName = ObjectIdProc::GetNameById(objectConvert.second);
		std::transform(objectName.begin(), objectName.end(), objectName.begin(), ::toupper);
		std::transform(convertObjectName.begin(), convertObjectName.end(), convertObjectName.begin(), ::toupper);
		convertRules.push_back(objectName + " IS " + convertObjectName);
	}
}

void PropertyManager::calculateHasRules() {
	hasRules.clear();
	for (auto &objectHas : objectsHas) {
		std::string objectName = ObjectIdProc::GetNameById(objectHas.first);
		std::transform(objectName.begin(), objectName.end(), objectName.begin(), ::toupper);
		for (auto &hasObjectId : objectHas.second) {
			std::string hasObjectName = ObjectIdProc::GetNameById(hasObjectId);
			std::transform(hasObjectName.begin(), hasObjectName.end(), hasObjectName.begin(), ::toupper);
			hasRules.push_back(objectName + " HAS " + hasObjectName);
		}
	}
}