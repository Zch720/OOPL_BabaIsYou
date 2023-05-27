#include "stdafx.h"
#include "property_manager.h"
#include "../../Expansion/log.h"

PropertyManager::ObjectProperties PropertyManager::objectProperties = {};
PropertyManager::ObjectsConvert PropertyManager::objectsConvert = {};

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

void PropertyManager::Clear() {
	objectProperties.clear();
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