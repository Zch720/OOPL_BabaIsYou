#include "stdafx.h"
#include <algorithm>
#include "object_id.h"
#include "property_manager.h"
#include "texture_manager.h"
#include "block.h"
#include "../../Expansion/log.h"

Block::Block(POINT position) {
	blockPosition = position;
}

Block::~Block() {
	for (ObjectBase *object : objects) {
		delete object;
	}
}

bool Block::IsPropertyOverlap(PropertyId propertyId1, PropertyId propertyId2) {
	bool hasProperty1 = false;
	bool hasProperty2 = false;
	bool hasProperty1WithFloat = false;
	bool hasProperty2WithFloat = false;
	for (ObjectBase *object : objects) {
		hasProperty1 |= object -> HasProperty(propertyId1) && (!object -> HasProperty(PROPERTY_FLOAT));
		hasProperty2 |= object -> HasProperty(propertyId2) && (!object -> HasProperty(PROPERTY_FLOAT));
		hasProperty1WithFloat |= object -> HasProperty(propertyId1) && object -> HasProperty(PROPERTY_FLOAT);
		hasProperty2WithFloat |= object -> HasProperty(propertyId2) && object -> HasProperty(PROPERTY_FLOAT);
	}
	return (hasProperty1 && hasProperty2) || (hasProperty1WithFloat && hasProperty2WithFloat);
}

bool Block::HasObjectId(ObjectId objectId) {
	for (ObjectBase *object : objects) {
		if (object -> GetObjectId() == objectId) {
			return true;
		}
	}
	return false;
}

bool Block::HasTextobject() {
	for (ObjectBase *object : objects) {
		if (ObjectIdProc::IsTextobjectId(object -> GetObjectId())) {
			return true;
		}
	}
	return false;
}

bool Block::HasPropertyIdWithoutFloat(PropertyId propertyId) {
	for (ObjectBase *object : objects) {
		if ((object -> HasProperty(propertyId)) && !(object -> HasProperty(PROPERTY_FLOAT))) {
			return true;
		}
	}
	return false;
}

bool Block::HasPropertyIdWithFloat(PropertyId propertyId) {
	for (ObjectBase *object : objects) {
		if ((object -> HasProperty(propertyId)) && (object -> HasProperty(PROPERTY_FLOAT))) {
			return true;
		}
	}
	return false;
}

size_t Block::GetObjectsSize() {
	return objects.size();
}

size_t Block::GetObjectsSizeWithFloat() {
	size_t size = 0;
	for (ObjectBase *object : objects) {
		if (object -> HasProperty(PROPERTY_FLOAT)) {
			size++;
		}
	}
	return size;
}

size_t Block::GetObjectsSizeWithoutFloat() {
	size_t size = 0;
	for (ObjectBase *object : objects) {
		if (!object -> HasProperty(PROPERTY_FLOAT)) {
			size++;
		}
	}
	return size;
}

ObjectBase* Block::GetTextobject() {
	for (ObjectBase *object : objects) {
		if (ObjectIdProc::IsTextobjectId(object -> GetObjectId())) {
			return object;
		}
	}
	Log::LogError("<Block> can't find text object at position (%d, %d)", blockPosition.x, blockPosition.y);
	return nullptr;
}

POINT Block::GetBlockPosition() {
	return blockPosition;
}

ObjectBase* Block::GetBlockObject(int genId) {
	for (ObjectBase *object : objects) {
		if (object -> GetGenId() == genId) {
			return object;
		}
	}
	Log::LogError("<Block> can't find object with genId %d at position (%d, %d)", genId, blockPosition.x, blockPosition.y);
	return nullptr;
}

ObjectBase* Block::GetFirstObjectWithoutFloat() {
	for (ObjectBase *object : objects) {
		if (!object -> HasProperty(PROPERTY_FLOAT)) {
			return object;
		}
	}
	Log::LogError("<Block> can't find any object at position (%d, %d)", blockPosition.x, blockPosition.y);
	return nullptr;
}

ObjectBase* Block::GetFirstObjectWithoutGenIdWithoutFloat(int genId) {
	for (ObjectBase *object : objects) {
		if (object -> GetGenId() != genId && !object -> HasProperty(PROPERTY_FLOAT)) {
			return object;
		}
	}
	Log::LogError("<Block> can't find object without genId %d at position (%d, %d)", genId, blockPosition.x, blockPosition.y);
	return nullptr;
}

ObjectBase* Block::GetFirstObjectWithObjectIdWithoutFloat(ObjectId objectId) {
	for (ObjectBase *object : objects) {
		if (object -> GetObjectId() == objectId && !object -> HasProperty(PROPERTY_FLOAT)) {
			return object;
		}
	}
	Log::LogError("<Block> can't find object with objectId %s at position (%d, %d)", ObjectIdProc::GetNameById(objectId), blockPosition.x, blockPosition.y);
	return nullptr;
}

ObjectBase* Block::GetFirstObjectWithoutObjectIdWithoutFloat(ObjectId objectId) {
	for (ObjectBase *object : objects) {
		if (object -> GetObjectId() != objectId && !object -> HasProperty(PROPERTY_FLOAT)) {
			return object;
		}
	}
	Log::LogError("<Block> can't find object without objectId %s at position (%d, %d)", ObjectIdProc::GetNameById(objectId), blockPosition.x, blockPosition.y);
	return nullptr;
}

ObjectBase* Block::GetFirstObjectWithPropertyWithoutFloat(PropertyId propertyId) {
	for (ObjectBase *object : objects) {
		if (object -> HasProperty(propertyId) && !object -> HasProperty(PROPERTY_FLOAT)) {
			return object;
		}
	}
	Log::LogError("<Block> can't find object with property %s at position (%d, %d)", PropertyIdProc::GetNameById(propertyId), blockPosition.x, blockPosition.y);
	return nullptr;
}

ObjectBase* Block::GetFirstObjectWithoutPropertyWithoutFloat(PropertyId propertyId) {
	for (ObjectBase *object : objects) {
		if (!object -> HasProperty(propertyId) && !object -> HasProperty(PROPERTY_FLOAT)) {
			return object;
		}
	}
	Log::LogError("<Block> can't find object without property %s at position (%d, %d)", PropertyIdProc::GetNameById(propertyId), blockPosition.x, blockPosition.y);
	return nullptr;
}

ObjectBase* Block::GetFirstObjectWithFloat() {
	for (ObjectBase *object : objects) {
		if (object -> HasProperty(PROPERTY_FLOAT)) {
			return object;
		}
	}
	Log::LogError("<Block> can't find any float object at position (%d, %d)", blockPosition.x, blockPosition.y);
	return nullptr;
}

ObjectBase* Block::GetFirstObjectWithoutGenIdWithFloat(int genId) {
	for (ObjectBase *object : objects) {
		if (object -> GetGenId() != genId && object -> HasProperty(PROPERTY_FLOAT)) {
			return object;
		}
	}
	Log::LogError("<Block> can't find float object without genId %d at position (%d, %d)", genId, blockPosition.x, blockPosition.y);
	return nullptr;
}

ObjectBase* Block::GetFirstObjectWithObjectIdWithFloat(ObjectId objectId) {
	if (!PropertyManager::ObjectHasProperty(objectId, PROPERTY_FLOAT)) {
		Log::LogError("<Block> can't find float object with objectId %s at position (%d, %d)", ObjectIdProc::GetNameById(objectId), blockPosition.x, blockPosition.y);
		return nullptr;
	}

	for (ObjectBase *object : objects) {
		if (object -> GetObjectId() == objectId) {
			return object;
		}
	}

	Log::LogError("<Block> can't find float object with objectId %s at position (%d, %d)", ObjectIdProc::GetNameById(objectId), blockPosition.x, blockPosition.y);
	return nullptr;
}

ObjectBase* Block::GetFirstObjectWithoutObjectIdWithFloat(ObjectId objectId) {
	for (ObjectBase *object : objects) {
		if (object -> GetObjectId() != objectId && object -> HasProperty(PROPERTY_FLOAT)) {
			return object;
		}
	}
	Log::LogError("<Block> can't find float object without objectId %s at position (%d, %d)", ObjectIdProc::GetNameById(objectId), blockPosition.x, blockPosition.y);
	return nullptr;
}

ObjectBase* Block::GetFirstObjectWithPropertyWithFloat(PropertyId propertyId) {
	for (ObjectBase *object : objects) {
		if (object -> HasProperty(propertyId) && object -> HasProperty(PROPERTY_FLOAT)) {
			return object;
		}
	}
	Log::LogError("<Block> can't find float object with property %s at position (%d, %d)", PropertyIdProc::GetNameById(propertyId), blockPosition.x, blockPosition.y);
	return nullptr;
}

ObjectBase* Block::GetFirstObjectWithoutPropertyWithFloat(PropertyId propertyId) {
	for (ObjectBase *object : objects) {
		if (!object -> HasProperty(propertyId) && object -> HasProperty(PROPERTY_FLOAT)) {
			return object;
		}
	}
	Log::LogError("<Block> can't find float object without property %s at position (%d, %d)", PropertyIdProc::GetNameById(propertyId), blockPosition.x, blockPosition.y);
	return nullptr;
}

void Block::AddObject(ObjectBase *object) {
	objects.push_back(object);
}

void Block::RemoveObject(int genId) {
	for (size_t i = 0; i < objects.size(); i++) {
		if (objects[i] -> GetGenId() == genId) {
			objects.erase(objects.begin() + i);
			return;
		}
	}
	Log::LogError("<Block> can't find object with genId %d at position (%d, %d)", genId, blockPosition.x, blockPosition.y);
}

void Block::foreach(ObjectProcFunc procFunc) {
	for (ObjectBase *object : objects) {
		procFunc(*object);
	}
}