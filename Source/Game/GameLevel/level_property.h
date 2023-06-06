#pragma once

#include "object_id.h"
#include "property_manager.h"

class LevelProperty {
private:
	static PropertyManager::ObjectProperties newObjectProperties;
	static PropertyManager::ObjectsConvert newObjectsConvert;
	static std::vector<Point> deleteObjectPoints;

	static bool hasObjectDefeat;
	static bool hasObjectSink;
	static bool hasObjectMelt;
	static bool hasObjectOpen;

	static void propertyPairProcess(std::pair<ObjectId, ObjectId> &propPair);
    static void processGameobject(ObjectId textobjectId, ObjectId convertTextobjectId);
    static void processProperty(ObjectId textobjectId, ObjectId propertyTextobjectId);

	static void addTextobjectProperty(PropertyId propertyId);
	static void removeTextobjectProperty(PropertyId propertyId);

	static void addPropertyUndo();
	static void addConvertUndo();

	static bool deleteFirstOverlapProperty(Block &block, PropertyId propertyId1, PropertyId propertyId2);
	static bool deleteBothOverlapProperty(Block &block, PropertyId propertyId1, PropertyId propertyId2);

	static bool deleteFirstOverlapPropertyWithFloat(Block &block, PropertyId propertyId1, PropertyId propertyId2);
	static bool deleteBothOverlapPropertyWithFloat(Block &block, PropertyId propertyId1, PropertyId propertyId2);

	static void checkPropertySink(Block &block);
	static void checkPropertyDefeat(Block &block);
    static void checkPropertyMeltHot(Block &block);
    static void checkPropertyOpenShut(Block &block);

public:
	static std::vector<Point> GetDeleteObjectPoints();
	static void ClearDeleteObjectPoints();
	static void SetBeginProperties();
    static void SetProperties();
	static void GameobjectConvert();
	static void UpdateOverlapProperty();

	static void ClearObjectActionFlags();
	static bool HasObjectDefeat();
	static bool HasObjectSink();
	static bool HasObjectMelt();
	static bool HasObjectOpen();
};