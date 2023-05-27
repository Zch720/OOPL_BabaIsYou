#pragma once

#include <stack>
#include <vector>
#include "objects.h"
#include "../../Expansion/point.h"
#include "../../Expansion/direction.h"

class LevelUndo {
public:
    enum ObjectUndoType {
        UNDO_MOVE_UP,
        UNDO_MOVE_DOWN,
        UNDO_MOVE_LEFT,
        UNDO_MOVE_RIGHT,
        UNDO_REPLACE,
        UNDO_GEN,
        UNDO_DELETE,
    };

    enum PropertyUndoType {
        UNDO_ADD_PROPERTY,
        UNDO_REMOVE_PROPERTY,
        UNDO_ADD_CONVERT,
        UNDO_CHANGE_CONVERT,
        UNDO_REMOVE_CONVERT,
    };

private:
    struct ObjectUndoInfo {
        ObjectUndoType type;
        int genId;
        Point position;
        ObjectId objectId;
        Direction textureDirection;
    };

    struct PropertyUndoInfo {
        PropertyUndoType type;
        ObjectId objectId;
        ObjectId convertObjectId = OBJECT_NONE;
        PropertyId propertyId = PROPERTY_NONE;
    };

    typedef std::vector<ObjectUndoInfo> ObjectUndoInfos;
    typedef std::vector<PropertyUndoInfo> PropertyUndoInfos;

    static std::stack<ObjectUndoInfos> objectUndoStack;
    static std::stack<PropertyUndoInfos> propertyUndoStack;
    static ObjectUndoInfos objectUndoInfosBuffer;
    static PropertyUndoInfos propertyUndoInfosBuffer;

    static ObjectUndoInfo objectInfoToUndoInfo(ObjectInfo &objectInfo);

    static void objectUndo();
    static void undoMoveUp(ObjectUndoInfo &undoInfo);
    static void undoMoveDown(ObjectUndoInfo &undoInfo);
    static void undoMoveLeft(ObjectUndoInfo &undoInfo);
    static void undoMoveRight(ObjectUndoInfo &undoInfo);
    static void undoReplace(ObjectUndoInfo &undoInfo);
    static void undoGen(ObjectUndoInfo &undoInfo);
    static void undoDelete(ObjectUndoInfo &undoInfo);

    static void propertyUndo();
    static void undoAddProperty(PropertyUndoInfo &undoInfo);
    static void undoRemoveProperty(PropertyUndoInfo &undoInfo);
    static void undoAddConvert(PropertyUndoInfo &undoInfo);
    static void undoChangeConvert(PropertyUndoInfo &undoInfo);
    static void undoRemoveConvert(PropertyUndoInfo &undoInfo);

public:
    static void Reset();
    static void AddBufferToObjectUndo();

    static bool HasObjectUndo();
    
    static void AddObjectUndo(ObjectUndoType undoType, ObjectInfo &objectInfo);
    static void AddPropertyUndo(PropertyUndoType undoType, ObjectId objectId, PropertyId peoprtyId);
    static void AddConvertUndo(PropertyUndoType undoType, ObjectId objectId, ObjectId convertObjectId);

    static bool CanUndo();
    static void Undo();
};