#pragma once

#include "object_id.h"
#include "property_manager.h"

class LevelProperty {
private:
	static PropertyManager::ObjectProperties newObjectProperties;
	static PropertyManager::ObjectsConvert newObjectsConvert;

	static void propertyPairProcess(std::pair<ObjectId, ObjectId> &propPair);
    static void processGameobject(ObjectId textobjectId, ObjectId convertTextobjectId);
    static void processProperty(ObjectId textobjectId, ObjectId propertyTextobjectId);

	static void addTextobjectProperty(PropertyId propertyId);
	static void removeTextobjectProperty(PropertyId propertyId);

	static void addPropertyUndo();
	static void addConvertUndo();

	static void deleteFirstOverlapProperty(Block &block, PropertyId propertyId1, PropertyId propertyId2);
	static void deleteBothOverlapProperty(Block &block, PropertyId propertyId1, PropertyId propertyId2);

	static void deleteFirstOverlapPropertyWithFloat(Block &block, PropertyId propertyId1, PropertyId propertyId2);
	static void deleteBothOverlapPropertyWithFloat(Block &block, PropertyId propertyId1, PropertyId propertyId2);

	static void checkPropertySink(Block &block);
	static void checkPropertyDefeat(Block &block);
    static void checkPropertyMeltHot(Block &block);
    static void checkPropertyOpenShut(Block &block);

public:
	static void SetBeginProperties();
    static void SetProperties();
	static void GameobjectConvert();
	static void UpdateOverlapProperty();
};