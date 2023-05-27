#include "stdafx.h"
#include <algorithm>
#include "property_manager.h"
#include "level_data.h"
#include "level_undo.h"

std::stack<LevelUndo::ObjectUndoInfos> LevelUndo::objectUndoStack = {};
std::stack<LevelUndo::PropertyUndoInfos> LevelUndo::propertyUndoStack = {};
LevelUndo::ObjectUndoInfos LevelUndo::objectUndoInfosBuffer = {};
LevelUndo::PropertyUndoInfos LevelUndo::propertyUndoInfosBuffer = {};

void LevelUndo::Reset() {
    while (!objectUndoStack.empty()) {
        objectUndoStack.pop();
    }
    while (!propertyUndoStack.empty()) {
        propertyUndoStack.pop();
    }
}

void LevelUndo::AddBufferToObjectUndo() {
    if (objectUndoInfosBuffer.size() == 0) return;
    objectUndoStack.push(objectUndoInfosBuffer);
    objectUndoInfosBuffer.clear();
    propertyUndoStack.push(propertyUndoInfosBuffer);
    propertyUndoInfosBuffer.clear();
}

bool LevelUndo::CanUndo() {
    return !objectUndoStack.empty();
}

bool LevelUndo::HasObjectUndo() {
    return !objectUndoInfosBuffer.empty();
}

void LevelUndo::AddObjectUndo(ObjectUndoType undoType, ObjectInfo &objectInfo) {
    ObjectUndoInfo undoInfo = objectInfoToUndoInfo(objectInfo);
    undoInfo.type = undoType;
    objectUndoInfosBuffer.push_back(undoInfo);
}

void LevelUndo::AddPropertyUndo(PropertyUndoType undoType, ObjectId objectId, PropertyId propertyId) {
    PropertyUndoInfo undoInfo;
    undoInfo.type = undoType;
    undoInfo.objectId = objectId;
    undoInfo.propertyId = propertyId;
    propertyUndoInfosBuffer.push_back(undoInfo);
}

void LevelUndo::AddConvertUndo(PropertyUndoType undoType, ObjectId objectId, ObjectId convertObjectId) {
    PropertyUndoInfo undoInfo;
    undoInfo.type = undoType;
    undoInfo.objectId = objectId;
    undoInfo.convertObjectId = convertObjectId;
    propertyUndoInfosBuffer.push_back(undoInfo);
}

void LevelUndo::Undo() {
    objectUndo();
    propertyUndo();
}

LevelUndo::ObjectUndoInfo LevelUndo::objectInfoToUndoInfo(ObjectInfo &objectInfo) {
    ObjectUndoInfo undoInfo;
    undoInfo.genId = objectInfo.genId;
    undoInfo.position = objectInfo.position;
    undoInfo.objectId = objectInfo.objectId;
    undoInfo.textureDirection = objectInfo.textureDirection;
    return undoInfo;
}

void LevelUndo::objectUndo() {
    ObjectUndoInfos undoInfos = objectUndoStack.top();
    objectUndoStack.pop();
    for (auto undoInfoIt = undoInfos.rbegin(); undoInfoIt != undoInfos.rend(); undoInfoIt++) {
        if (undoInfoIt -> type == UNDO_MOVE_UP) undoMoveUp(*undoInfoIt);
        else if (undoInfoIt -> type == UNDO_MOVE_DOWN) undoMoveDown(*undoInfoIt);
        else if (undoInfoIt -> type == UNDO_MOVE_LEFT) undoMoveLeft(*undoInfoIt);
        else if (undoInfoIt -> type == UNDO_MOVE_RIGHT) undoMoveRight(*undoInfoIt);
        else if (undoInfoIt -> type == UNDO_REPLACE) undoReplace(*undoInfoIt);
        else if (undoInfoIt -> type == UNDO_GEN) undoGen(*undoInfoIt);
        else if (undoInfoIt -> type == UNDO_DELETE) undoDelete(*undoInfoIt);
    }
}

void LevelUndo::undoMoveUp(ObjectUndoInfo &undoInfo) {
    ObjectBase &object = LevelData::GetBlockObject(undoInfo.position.Up(), undoInfo.genId);
    LevelData::MoveObject(object.GetInfo(), undoInfo.position);
    object.UndoMoveUp(undoInfo.textureDirection);
}

void LevelUndo::undoMoveDown(ObjectUndoInfo &undoInfo) {
    ObjectBase &object = LevelData::GetBlockObject(undoInfo.position.Down(), undoInfo.genId);
    LevelData::MoveObject(object.GetInfo(), undoInfo.position);
    object.UndoMoveDown(undoInfo.textureDirection);
}

void LevelUndo::undoMoveLeft(ObjectUndoInfo &undoInfo) {
    ObjectBase &object = LevelData::GetBlockObject(undoInfo.position.Left(), undoInfo.genId);
    LevelData::MoveObject(object.GetInfo(), undoInfo.position);
    object.UndoMoveLeft(undoInfo.textureDirection);
}

void LevelUndo::undoMoveRight(ObjectUndoInfo &undoInfo) {
    ObjectBase &object = LevelData::GetBlockObject(undoInfo.position.Right(), undoInfo.genId);
    LevelData::MoveObject(object.GetInfo(), undoInfo.position);
    object.UndoMoveRight(undoInfo.textureDirection);
}

void LevelUndo::undoReplace(ObjectUndoInfo &undoInfo) {
    ObjectBase &object = LevelData::GetBlockObject(undoInfo.position, undoInfo.genId);
    LevelData::ReplaceObject(object.GetInfo(), undoInfo.objectId);
}

void LevelUndo::undoGen(ObjectUndoInfo &undoInfo) {
    LevelData::DeleteObject(undoInfo.position, undoInfo.genId);
}

void LevelUndo::undoDelete(ObjectUndoInfo &undoInfo) {
    LevelData::GenObjectWithGenId(undoInfo.position, {undoInfo.objectId, undoInfo.textureDirection}, undoInfo.genId);
}

void LevelUndo::propertyUndo() {
    PropertyUndoInfos undoInfos = propertyUndoStack.top();
    propertyUndoStack.pop();
    for (auto undoInfoIt = undoInfos.rbegin(); undoInfoIt != undoInfos.rend(); undoInfoIt++) {
        if (undoInfoIt -> type == UNDO_ADD_PROPERTY) undoAddProperty(*undoInfoIt);
        else if (undoInfoIt -> type == UNDO_REMOVE_PROPERTY) undoRemoveProperty(*undoInfoIt);
        else if (undoInfoIt -> type == UNDO_ADD_CONVERT) undoAddConvert(*undoInfoIt);
        else if (undoInfoIt -> type == UNDO_CHANGE_CONVERT) undoChangeConvert(*undoInfoIt);
        else if (undoInfoIt -> type == UNDO_REMOVE_CONVERT) undoRemoveConvert(*undoInfoIt);
    }
}

void LevelUndo::undoAddProperty(PropertyUndoInfo &undoInfo) {
    PropertyManager::RemoveObjectProperty(undoInfo.objectId, undoInfo.propertyId);
}

void LevelUndo::undoRemoveProperty(PropertyUndoInfo &undoInfo) {
    PropertyManager::AddObjectProperty(undoInfo.objectId, undoInfo.propertyId);
}

void LevelUndo::undoAddConvert(PropertyUndoInfo &undoInfo) {
    PropertyManager::RemoveObjectConvert(undoInfo.objectId);
}

void LevelUndo::undoChangeConvert(PropertyUndoInfo &undoInfo) {
    PropertyManager::AddObjectConvert(undoInfo.objectId, undoInfo.convertObjectId);
}

void LevelUndo::undoRemoveConvert(PropertyUndoInfo &undoInfo) {
    PropertyManager::AddObjectConvert(undoInfo.objectId, undoInfo.convertObjectId);
}