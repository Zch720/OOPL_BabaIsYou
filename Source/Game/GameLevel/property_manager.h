#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "object_id.h"
#include "property_id.h"

class PropertyManager {
public:
	typedef std::unordered_map<ObjectId, std::unordered_map<PropertyId, int>> ObjectProperties;
	typedef std::unordered_map<ObjectId, ObjectId> ObjectsConvert;
	typedef std::unordered_map<ObjectId, std::vector<ObjectId>> ObjectsHas;

private:
	static ObjectProperties objectProperties;
	static ObjectsConvert objectsConvert;
	static ObjectsHas objectsHas;
	static std::vector<std::string> propertyRules;
	static std::vector<std::string> convertRules;
	static std::vector<std::string> hasRules;
	static std::vector<std::string> rules;

	static void removeObjectIdWithWeak(std::vector<ObjectId> &objectIds);
	static bool canBeOffset(ObjectId objectId1, ObjectId objectId2);
	static bool propertyOffset_OpenShut(ObjectId propertyId1, ObjectId propertyId2);

	static void addTextobjectProperty(PropertyId propertyId);
	static void removeTextobjectProperty(PropertyId propertyId);

	static void calculatePropertyRules();
	static void calculateConvertRules();
	static void calculateHasRules();

public:
	static void Clear();
	static void Reset();

	static std::vector<std::string> GetRules();
	
	static ObjectProperties GetDefaultObjectProperties();
	static ObjectProperties& GetObjectProperties();
	static void SetObjectProperties(ObjectProperties &objectProperties);
	static ObjectsConvert& GetObjectsConvert();
	static void SetObjectsConvert(ObjectsConvert &objectsConvert);
	static ObjectsHas& GetObjectsHas();
	static void SetObjectsHas(ObjectsHas &objectsHas);

	static void AddObjectProperty(ObjectId objectId, PropertyId propertyId);
	static void RemoveObjectProperty(ObjectId objectId, PropertyId propertyId);
	static int GetObjectProperty(ObjectId objectId, PropertyId propertyId);
	static bool ObjectHasProperty(ObjectId objectId, PropertyId propertyId);
	static PropertyId GetObjectColor(ObjectId objectId);

	static void AddObjectConvert(ObjectId objectId, ObjectId convertObjectId);
	static void RemoveObjectConvert(ObjectId objectId);
	static ObjectId GetObjectConvert(ObjectId objectId);

	static void AddObjectHas(ObjectId objectId, ObjectId hasObjectId);
	static void RemoveObjectHas(ObjectId objectId, ObjectId hasObjectId);
	static bool ObjectHasObject(ObjectId objectId, ObjectId hasObjectId);
	static std::vector<ObjectId> GetObjectHas(ObjectId objectId);
	
	static void RemoveOffsetObjects(std::vector<ObjectId> &objects1, std::vector<ObjectId> &objects2);
};