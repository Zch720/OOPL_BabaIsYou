#pragma once

#include <vector>
#include <functional>
#include "objects.h"

class LevelData;

class Block {
private:
	POINT blockPosition {0, 0};
	std::vector<ObjectBase*> objects;

	ObjectBase* GetFirstObjectWithoutFloat();
	ObjectBase* GetFirstObjectWithoutGenIdWithoutFloat(int genId);
	ObjectBase* GetFirstObjectWithObjectIdWithoutFloat(ObjectId objectId);
	ObjectBase* GetFirstObjectWithoutObjectIdWithoutFloat(ObjectId objectId);
	ObjectBase* GetFirstObjectWithPropertyWithoutFloat(PropertyId propertyId);
	ObjectBase* GetFirstObjectWithoutPropertyWithoutFloat(PropertyId propertyId);
	
	ObjectBase* GetFirstObjectWithFloat();
	ObjectBase* GetFirstObjectWithoutGenIdWithFloat(int genId);
	ObjectBase* GetFirstObjectWithObjectIdWithFloat(ObjectId objectId);
	ObjectBase* GetFirstObjectWithoutObjectIdWithFloat(ObjectId objectId);
	ObjectBase* GetFirstObjectWithPropertyWithFloat(PropertyId propertyId);
	ObjectBase* GetFirstObjectWithoutPropertyWithFloat(PropertyId propertyId);

public:
	friend LevelData;

	typedef std::function<void(ObjectBase&)> ObjectProcFunc;

	Block(POINT position);
	~Block();

	bool IsPropertyOverlap(PropertyId propertyId1, PropertyId propertyId2);

	bool HasObjectId(ObjectId objectId);
	bool HasPropertyIdWithoutFloat(PropertyId propertyId);
	bool HasPropertyIdWithFloat(PropertyId propertyId);
	bool HasTextobject();

	size_t GetObjectsSize();
	size_t GetObjectsSizeWithFloat();
	size_t GetObjectsSizeWithoutFloat();
	ObjectBase* GetTextobject();
	POINT GetBlockPosition();
	ObjectBase* GetBlockObject(int genId);

	void AddObject(ObjectBase *object);
	void RemoveObject(int genId);

	void foreach(ObjectProcFunc procFunc);
};