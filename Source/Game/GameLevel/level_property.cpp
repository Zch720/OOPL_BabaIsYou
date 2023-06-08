#include "stdafx.h"
#include <algorithm>
#include "textobject_id.h"
#include "level_data.h"
#include "level_property.h"
#include "level_description.h"
#include "level_undo.h"

PropertyManager::ObjectProperties LevelProperty::newObjectProperties = {};
PropertyManager::ObjectsConvert LevelProperty::newObjectsConvert = {};
PropertyManager::ObjectsHas LevelProperty::newObjectsHas = {};
std::vector<Point> LevelProperty::deleteObjectPoints = {};
std::unordered_set<int> LevelProperty::newObjectGenIdFromObject = {};

bool LevelProperty::hasObjectDefeat = false;
bool LevelProperty::hasObjectSink = false;
bool LevelProperty::hasObjectMelt = false;
bool LevelProperty::hasObjectOpen = false;

std::vector<Point> LevelProperty::GetDeleteObjectPoints() {
	return deleteObjectPoints;
}

void LevelProperty::ClearDeleteObjectPoints() {
	deleteObjectPoints.clear();
}

void LevelProperty::SetBeginProperties() {
    std::vector<std::pair<ObjectId, ObjectId>> descriptionsIs = LevelDescription::GetDescriptionsIs();
    std::vector<std::pair<ObjectId, ObjectId>> descriptionsHas = LevelDescription::GetDescriptionsHas();
    newObjectProperties = PropertyManager::GetDefaultObjectProperties();
    newObjectsConvert.clear();
    newObjectsHas.clear();
    for (std::pair<ObjectId, ObjectId> &propPair : descriptionsIs) {
        propertyPairProcess(propPair);
    }
    for (std::pair<ObjectId, ObjectId> &propPair : descriptionsHas) {
        processHas(propPair.first, propPair.second);
    }
    PropertyManager::SetObjectProperties(newObjectProperties);
    PropertyManager::SetObjectsConvert(newObjectsConvert);
    PropertyManager::SetObjectsHas(newObjectsHas);
}

void LevelProperty::SetProperties() {
    std::vector<std::pair<ObjectId, ObjectId>> descriptionsIs = LevelDescription::GetDescriptionsIs();
    std::vector<std::pair<ObjectId, ObjectId>> descriptionsHas = LevelDescription::GetDescriptionsHas();
    newObjectProperties = PropertyManager::GetDefaultObjectProperties();
    newObjectsConvert.clear();
    newObjectsHas.clear();
    for (std::pair<ObjectId, ObjectId> &propPair : descriptionsIs) {
        propertyPairProcess(propPair);
    }
    for (std::pair<ObjectId, ObjectId> &propPair : descriptionsHas) {
        processHas(propPair.first, propPair.second);
    }
    addPropertyUndo();
    addConvertUndo();
    addHasUndo();
    PropertyManager::SetObjectProperties(newObjectProperties);
    PropertyManager::SetObjectsConvert(newObjectsConvert);
    PropertyManager::SetObjectsHas(newObjectsHas);
}

void LevelProperty::UpdateOverlapProperty() {
	deleteObjectPoints.clear();
    newObjectGenIdFromObject.clear();
	LevelData::SetIsWin(LevelData::IsPropertyOverlap(PROPERTY_YOU, PROPERTY_WIN));
	LevelData::GameboardForeach([](Block &block) {
        checkPropertyWeak(block);
		checkPropertySink(block);
		checkPropertyDefeat(block);
        checkPropertyMeltHot(block);
        checkPropertyOpenShut(block);
	});
    LevelData::RemoveEmptyObjects();
}

void LevelProperty::ClearObjectActionFlags() {
    hasObjectDefeat = false;
    hasObjectSink = false;
    hasObjectMelt = false;
    hasObjectOpen = false;
}

bool LevelProperty::HasObjectDefeat() {
    return hasObjectDefeat;
}

bool LevelProperty::HasObjectSink() {
    return hasObjectSink;
}

bool LevelProperty::HasObjectMelt() {
    return hasObjectMelt;
}

bool LevelProperty::HasObjectOpen() {
    return hasObjectOpen;
}

void LevelProperty::propertyPairProcess(std::pair<ObjectId, ObjectId> &propPair) {
    if (TextobjectIdProc::IsGameobjectTextobject(propPair.second)) {
        processGameobject(propPair.first, propPair.second);
    } else {
        processProperty(propPair.first, propPair.second);
    }
}

void LevelProperty::processGameobject(ObjectId textobjectId, ObjectId convertTextobjectId) {
    ObjectId gameobjectId = TextobjectIdProc::GetGameobjectId(textobjectId);
    ObjectId convertGameobjectId = TextobjectIdProc::GetGameobjectId(convertTextobjectId);
    if (newObjectsConvert.find(gameobjectId) != newObjectsConvert.end()) {
        if (PropertyManager::GetObjectConvert(gameobjectId) != convertGameobjectId) return;
    }
    newObjectsConvert[gameobjectId] = convertGameobjectId;
}

void LevelProperty::processProperty(ObjectId textobjectId, ObjectId propertyTextobjectId) {
    ObjectId gameobjectId = TextobjectIdProc::GetGameobjectId(textobjectId);
    PropertyId propertyId = TextobjectIdProc::GetPropertyId(propertyTextobjectId);
    if (gameobjectId == GAMEOBJECT_TEXTS) addTextobjectProperty(propertyId);
    else newObjectProperties[gameobjectId][propertyId] += 1;
}

void LevelProperty::processHas(ObjectId textobjectId, ObjectId hasTextobjectId) {
    ObjectId gameobjectId = TextobjectIdProc::GetGameobjectId(textobjectId);
    ObjectId hasGameobjectId = TextobjectIdProc::GetGameobjectId(hasTextobjectId);
    newObjectsHas[gameobjectId].push_back(hasGameobjectId);
    std::sort(newObjectsHas[gameobjectId].begin(), newObjectsHas[gameobjectId].end());
}

void LevelProperty::addTextobjectProperty(PropertyId propertyId) {
    newObjectProperties[GAMEOBJECT_TEXTS][propertyId] += 1;
    for (auto &objectProperty : newObjectProperties) {
        if (ObjectIdProc::IsTextobjectId(objectProperty.first)) {
            objectProperty.second[propertyId] += 1;
        }
    }
}

void LevelProperty::removeTextobjectProperty(PropertyId propertyId) {
    newObjectProperties[GAMEOBJECT_TEXTS][propertyId] -= 1;
    for (auto &objectProperty : newObjectProperties) {
        if (ObjectIdProc::IsTextobjectId(objectProperty.first)) {
            objectProperty.second[propertyId] -= 1;
        }
    }
}

void LevelProperty::addPropertyUndo() {
    PropertyManager::ObjectProperties &objectProperties = PropertyManager::GetObjectProperties();
    for (auto &objectProperty : objectProperties) {
        if (newObjectProperties.find(objectProperty.first) == newObjectProperties.end()) {
            for (auto &property : objectProperty.second) {
                for (int i = 0; i < property.second; i++)
                    LevelUndo::AddPropertyUndo(LevelUndo::UNDO_REMOVE_PROPERTY, objectProperty.first, property.first);
            }
            continue;
        }
        for (auto &property : objectProperty.second) {
            if (newObjectProperties[objectProperty.first][property.first] != property.second) {
                for (int i = 0; i < property.second - newObjectProperties[objectProperty.first][property.first]; i++)
                    LevelUndo::AddPropertyUndo(LevelUndo::UNDO_REMOVE_PROPERTY, objectProperty.first, property.first);
                for (int i = 0; i < newObjectProperties[objectProperty.first][property.first] - property.second; i++)
                    LevelUndo::AddPropertyUndo(LevelUndo::UNDO_ADD_PROPERTY, objectProperty.first, property.first);
            }
        }
    }
    for (auto &newObjectProperty : newObjectProperties) {
        if (objectProperties.find(newObjectProperty.first) == objectProperties.end()) {
            for (auto &property : newObjectProperty.second) {
                for (int i = 0; i < property.second; i++)
                    LevelUndo::AddPropertyUndo(LevelUndo::UNDO_ADD_PROPERTY, newObjectProperty.first, property.first);
            }
        }
    }
}

void LevelProperty::addConvertUndo() {
    PropertyManager::ObjectsConvert &objectsConvert = PropertyManager::GetObjectsConvert();
    for (auto &objectConvert : objectsConvert) {
        if (newObjectsConvert.find(objectConvert.first) == newObjectsConvert.end()) {
            LevelUndo::AddConvertUndo(LevelUndo::UNDO_REMOVE_CONVERT, objectConvert.first, objectConvert.second);
            continue;
        }
        if (newObjectsConvert[objectConvert.first] != objectConvert.second) {
            LevelUndo::AddConvertUndo(LevelUndo::UNDO_CHANGE_CONVERT, objectConvert.first, objectConvert.second);
        }
    }
    for (auto &newObjectConvert : newObjectsConvert) {
        if (objectsConvert.find(newObjectConvert.first) == objectsConvert.end()) {
            LevelUndo::AddConvertUndo(LevelUndo::UNDO_ADD_CONVERT, newObjectConvert.first, newObjectConvert.second);
        }
    }
}

void LevelProperty::addHasUndo() {
    PropertyManager::ObjectsHas &objectsHas = PropertyManager::GetObjectsHas();
    for (auto &objectHas : objectsHas) {
        if (newObjectsHas.find(objectHas.first) == newObjectsHas.end()) {
            for (auto &has : objectHas.second) {
                LevelUndo::AddHasObjectUndo(LevelUndo::UNDO_REMOVE_HAS_OBJECT, objectHas.first, has);
            }
            continue;
        }
        size_t oldIndex = 0, newIndex = 0;
        for (; oldIndex < objectHas.second.size() && newIndex < newObjectsHas[objectHas.first].size();) {
            if (objectHas.second[oldIndex] == newObjectsHas[objectHas.first][newIndex]) {
                oldIndex++;
                newIndex++;
            } else if (objectHas.second[oldIndex] < newObjectsHas[objectHas.first][newIndex]) {
                LevelUndo::AddHasObjectUndo(LevelUndo::UNDO_REMOVE_HAS_OBJECT, objectHas.first, objectHas.second[oldIndex]);
                oldIndex++;
            } else {
                LevelUndo::AddHasObjectUndo(LevelUndo::UNDO_ADD_HAS_OBJECT, objectHas.first, newObjectsHas[objectHas.first][newIndex]);
                newIndex++;
            }
        }
        for (; oldIndex < objectHas.second.size(); oldIndex++) {
            LevelUndo::AddHasObjectUndo(LevelUndo::UNDO_REMOVE_HAS_OBJECT, objectHas.first, objectHas.second[oldIndex]);
        }
        for (; newIndex < newObjectsHas[objectHas.first].size(); newIndex++) {
            LevelUndo::AddHasObjectUndo(LevelUndo::UNDO_ADD_HAS_OBJECT, objectHas.first, newObjectsHas[objectHas.first][newIndex]);
        }
    }
    for (auto &newObjectHas : newObjectsHas) {
        if (objectsHas.find(newObjectHas.first) == objectsHas.end()) {
            for (auto &has : newObjectHas.second) {
                LevelUndo::AddHasObjectUndo(LevelUndo::UNDO_ADD_HAS_OBJECT, newObjectHas.first, has);
            }
        }
    }
}

void LevelProperty::GameobjectConvert() {
    LevelData::AllObjectForeach([](ObjectBase &object) {
        ObjectId convertGameobjectId = PropertyManager::GetObjectConvert(object.GetObjectId());
        if (convertGameobjectId == OBJECT_NONE) return;
        if (object.GetObjectId() == convertGameobjectId) return;
        LevelData::ReplaceObject(object.GetInfo(), convertGameobjectId);
        LevelUndo::AddObjectUndo(LevelUndo::UNDO_REPLACE, object.GetInfo());
    });
}

bool LevelProperty::deleteFirstOverlapProperty(Block &block, PropertyId propertyId1, PropertyId propertyId2) {
    bool result = false;
	if (!block.HasPropertyIdWithoutFloat(propertyId2)) return false;
    while (block.HasPropertyIdWithoutFloat(propertyId1)) {
        result = true;
        ObjectInfo object1Info = LevelData::GetFirstObjectWithPropertyWithoutFloat(block.GetBlockPosition(), propertyId1).GetInfo();
		deleteObjectPoints.push_back(object1Info.position);
        genDispearObjectHasObjects(object1Info);
        LevelUndo::AddObjectUndo(LevelUndo::UNDO_DELETE, object1Info);
        LevelData::DeleteObject(object1Info.position, object1Info.genId);
    }
    return result;
}

 bool LevelProperty::deleteBothOverlapProperty(Block &block, PropertyId propertyId1, PropertyId propertyId2) {
    bool result = false;
    while (block.HasPropertyIdWithoutFloat(propertyId1) && block.HasPropertyIdWithoutFloat(propertyId2)) {
        result = true;
        ObjectInfo object1Info = LevelData::GetFirstObjectWithPropertyWithoutFloat(block.GetBlockPosition(), propertyId1).GetInfo();
        ObjectInfo object2Info = LevelData::GetFirstObjectWithPropertyWithoutFloat(block.GetBlockPosition(), propertyId2).GetInfo();
		deleteObjectPoints.push_back(object1Info.position);
        genDispearObjectHasObjects(object1Info);
        LevelUndo::AddObjectUndo(LevelUndo::UNDO_DELETE, object1Info);
        LevelData::DeleteObject(object1Info.position, object1Info.genId);
        if (object1Info.genId != object2Info.genId) {
			deleteObjectPoints.push_back(object2Info.position);
            genDispearObjectHasObjects(object2Info);
            LevelUndo::AddObjectUndo(LevelUndo::UNDO_DELETE, object2Info);
            LevelData::DeleteObject(object2Info.position, object2Info.genId);
        }
    }
    return result;
}

bool LevelProperty::deleteFirstOverlapPropertyWithFloat(Block &block, PropertyId propertyId1, PropertyId propertyId2) {
    bool result = false;
    if (!block.HasPropertyIdWithFloat(propertyId2)) return false;
    while (block.HasPropertyIdWithFloat(propertyId1)) {
        result = true;
        ObjectInfo object1Info = LevelData::GetFirstObjectWithPropertyWithFloat(block.GetBlockPosition(), propertyId1).GetInfo();
		deleteObjectPoints.push_back(object1Info.position);
        genDispearObjectHasObjects(object1Info);
        LevelUndo::AddObjectUndo(LevelUndo::UNDO_DELETE, object1Info);
        LevelData::DeleteObject(object1Info.position, object1Info.genId);
    }
    return result;
}

bool LevelProperty::deleteBothOverlapPropertyWithFloat(Block &block, PropertyId propertyId1, PropertyId propertyId2) {
    bool result = false;
    while (block.HasPropertyIdWithFloat(propertyId1) && block.HasPropertyIdWithFloat(propertyId2)) {
        result = true;
        ObjectInfo object1Info = LevelData::GetFirstObjectWithPropertyWithFloat(block.GetBlockPosition(), propertyId1).GetInfo();
        ObjectInfo object2Info = LevelData::GetFirstObjectWithPropertyWithFloat(block.GetBlockPosition(), propertyId2).GetInfo();
		deleteObjectPoints.push_back(object1Info.position);
        genDispearObjectHasObjects(object1Info);
        LevelUndo::AddObjectUndo(LevelUndo::UNDO_DELETE, object1Info);
        LevelData::DeleteObject(object1Info.position, object1Info.genId);
        if (object1Info.genId != object2Info.genId) {
			deleteObjectPoints.push_back(object2Info.position);
            genDispearObjectHasObjects(object2Info);
            LevelUndo::AddObjectUndo(LevelUndo::UNDO_DELETE, object2Info);
            LevelData::DeleteObject(object2Info.position, object2Info.genId);
        }
    }
    return result;
}

void LevelProperty::checkPropertyWeak(Block &block) {
	while (block.HasPropertyIdWithoutFloat(PROPERTY_WEAK) && block.GetObjectsSizeWithoutFloat() > 1) {
	    ObjectInfo weakObjectInfo = LevelData::GetFirstObjectWithPropertyWithoutFloat(block.GetBlockPosition(), PROPERTY_WEAK).GetInfo();
        if (newObjectGenIdFromObject.find(weakObjectInfo.genId) != newObjectGenIdFromObject.end()) break;
		deleteObjectPoints.push_back(weakObjectInfo.position);
        genDispearObjectHasObjects(weakObjectInfo);
        LevelUndo::AddObjectUndo(LevelUndo::UNDO_DELETE, weakObjectInfo);
        LevelData::DeleteObject(weakObjectInfo.position, weakObjectInfo.genId);
    }
    while (block.HasPropertyIdWithFloat(PROPERTY_WEAK) && block.GetObjectsSizeWithFloat() > 1) {
        ObjectInfo weakObjectInfo = LevelData::GetFirstObjectWithPropertyWithFloat(block.GetBlockPosition(), PROPERTY_WEAK).GetInfo();
        if (newObjectGenIdFromObject.find(weakObjectInfo.genId) != newObjectGenIdFromObject.end()) break;
		deleteObjectPoints.push_back(weakObjectInfo.position);
        genDispearObjectHasObjects(weakObjectInfo);
        LevelUndo::AddObjectUndo(LevelUndo::UNDO_DELETE, weakObjectInfo);
        LevelData::DeleteObject(weakObjectInfo.position, weakObjectInfo.genId);
    }
}

void LevelProperty::checkPropertySink(Block &block) {
	while (block.HasPropertyIdWithoutFloat(PROPERTY_SINK) && block.GetObjectsSizeWithoutFloat() > 1) {
        hasObjectSink = true;
	    ObjectInfo sinkObjectInfo = LevelData::GetFirstObjectWithPropertyWithoutFloat(block.GetBlockPosition(), PROPERTY_SINK).GetInfo();
        ObjectInfo sinkedObjectInfo = LevelData::GetFirstObjectWithoutGenIdWithoutFloat(block.GetBlockPosition(), sinkObjectInfo.genId).GetInfo();
		deleteObjectPoints.push_back(sinkObjectInfo.position);
		deleteObjectPoints.push_back(sinkedObjectInfo.position);
        genDispearObjectHasObjects(sinkObjectInfo);
        genDispearObjectHasObjects(sinkedObjectInfo);
        LevelUndo::AddObjectUndo(LevelUndo::UNDO_DELETE, sinkObjectInfo);
        LevelUndo::AddObjectUndo(LevelUndo::UNDO_DELETE, sinkedObjectInfo);
        LevelData::DeleteObject(sinkObjectInfo.position, sinkObjectInfo.genId);
        LevelData::DeleteObject(sinkedObjectInfo.position, sinkedObjectInfo.genId);
    }
    while (block.HasPropertyIdWithFloat(PROPERTY_SINK) && block.GetObjectsSizeWithFloat() > 1) {
        hasObjectSink = true;
        ObjectInfo sinkObjectInfo = LevelData::GetFirstObjectWithPropertyWithFloat(block.GetBlockPosition(), PROPERTY_SINK).GetInfo();
        ObjectInfo sinkedObjectInfo = LevelData::GetFirstObjectWithoutGenIdWithFloat(block.GetBlockPosition(), sinkObjectInfo.genId).GetInfo();
		deleteObjectPoints.push_back(sinkObjectInfo.position);
		deleteObjectPoints.push_back(sinkedObjectInfo.position);
        genDispearObjectHasObjects(sinkObjectInfo);
        genDispearObjectHasObjects(sinkedObjectInfo);
        LevelUndo::AddObjectUndo(LevelUndo::UNDO_DELETE, sinkObjectInfo);
        LevelUndo::AddObjectUndo(LevelUndo::UNDO_DELETE, sinkedObjectInfo);
        LevelData::DeleteObject(sinkObjectInfo.position, sinkObjectInfo.genId);
        LevelData::DeleteObject(sinkedObjectInfo.position, sinkedObjectInfo.genId);
    }
}

void LevelProperty::checkPropertyDefeat(Block &block) {
	hasObjectDefeat |= deleteFirstOverlapProperty(block, PROPERTY_YOU, PROPERTY_DEFEAT);
	hasObjectDefeat |= deleteFirstOverlapPropertyWithFloat(block, PROPERTY_YOU, PROPERTY_DEFEAT);
}

void LevelProperty::checkPropertyMeltHot(Block &block) {
    hasObjectMelt |= deleteFirstOverlapProperty(block, PROPERTY_MELT, PROPERTY_HOT);
    hasObjectMelt |= deleteFirstOverlapPropertyWithFloat(block, PROPERTY_MELT, PROPERTY_HOT);
}

void LevelProperty::checkPropertyOpenShut(Block &block) {
    hasObjectOpen |= deleteBothOverlapProperty(block, PROPERTY_OPEN, PROPERTY_SHUT);
    hasObjectOpen |= deleteBothOverlapPropertyWithFloat(block, PROPERTY_OPEN, PROPERTY_SHUT);
}

void LevelProperty::genDispearObjectHasObjects(ObjectInfo &info) {
    std::vector<ObjectId> hasObjects = newObjectsHas[info.objectId];
    for (ObjectId objectId : hasObjects) {
        LevelData::GenObjectInfo genInfo = {
            objectId,
            info.textureDirection
        };
        ObjectInfo newObject = LevelData::GenNewObject(info.position, genInfo);
        LevelUndo::AddObjectUndo(LevelUndo::UNDO_GEN, newObject);
        newObjectGenIdFromObject.insert(newObject.genId);
    }
}