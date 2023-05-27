#pragma once

#include <unordered_map>
#include "object_id.h"
#include "property_id.h"

class PropertyManager {
public:
	typedef std::unordered_map<ObjectId, std::unordered_map<PropertyId, int>> ObjectProperties;
	typedef std::unordered_map<ObjectId, ObjectId> ObjectsConvert;

private:
	static ObjectProperties objectProperties;
	static ObjectsConvert objectsConvert;

	static bool canBeOffset(ObjectId objectId1, ObjectId objectId2);
	static bool propertyOffset_OpenShut(ObjectId propertyId1, ObjectId propertyId2);

	static void addTextobjectProperty(PropertyId propertyId);
	static void removeTextobjectProperty(PropertyId propertyId);

public:
	static void Clear();
	static void Reset();
	
	static ObjectProperties GetDefaultObjectProperties();
	static ObjectProperties& GetObjectProperties();
	static void SetObjectProperties(ObjectProperties &objectProperties);
	static ObjectsConvert& GetObjectsConvert();
	static void SetObjectsConvert(ObjectsConvert &objectsConvert);

	static void AddObjectProperty(ObjectId objectId, PropertyId propertyId);
	static void RemoveObjectProperty(ObjectId objectId, PropertyId propertyId);
	static int GetObjectProperty(ObjectId objectId, PropertyId propertyId);
	static bool ObjectHasProperty(ObjectId objectId, PropertyId propertyId);
	static PropertyId GetObjectColor(ObjectId objectId);

	static void AddObjectConvert(ObjectId objectId, ObjectId convertObjectId);
	static void RemoveObjectConvert(ObjectId objectId);
	static ObjectId GetObjectConvert(ObjectId objectId);
	
	static void RemoveOffsetObjects(std::vector<ObjectId> &objects1, std::vector<ObjectId> &objects2);
};