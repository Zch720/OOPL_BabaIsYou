#pragma once

#include "object_id.h"
#include "object_type.h"
#include "property_id.h"
#include "../../Library/gameutil.h"
#include "../../Expansion/point.h"
#include "../../Expansion/direction.h"

struct ObjectInfo {
	Point position;
	int genId = -1;
	ObjectId objectId = OBJECT_NONE;
	ObjectType type;
	Direction textureDirection;

	bool operator==(const ObjectInfo &other) const;
	bool operator<(const ObjectInfo &other);

	size_t GetHash() const;
};

namespace std{
	template<>
	struct hash<ObjectInfo> {
		size_t operator()(const ObjectInfo &info) const;
	};
}

struct ShowInfo {
	bool nextTexture;
	bool textConnected;
	int tiledConnected;
	Point textureOffset;
};

class ObjectBase {
private:
	bool genIdSetted = false;
	ObjectInfo info;
	PropertyId currentColor;
	Point texturePosition;

	const int MAX_TEXTURE_STEP = 4;
	int textureRemainStep = 0;
	Direction moveDirection;

	inline int getTextureMoveDistance();

protected:
	game_framework::CMovingBitmap texture;
	game_framework::CMovingBitmap crossed;
	int textureCount = 0;
	int characterShowCount = 0;
	int animationShowCount = 0;
	
	void updateTexturePosition();
	void texturePositionAddOffset(Point offset);
	inline void updateTextureCount(bool nextTexture);
	virtual void updateTexture(ShowInfo showInfo) = 0;

public:
	ObjectBase(ObjectType type);

	bool IsMoving();
	bool HasProperty(PropertyId id);

	ObjectInfo GetInfo();
	Point GetPosition();
	int GetGenId();
	ObjectId GetObjectId();
	Direction GetTextureDirection();
	ObjectType GetObjectType();
	int GetPropertyCount();

	void SetPosition(POINT point);
	void SetGenId(int id);
	void SetObjectId(ObjectId id);
	void SetTextureDirection(Direction direction);

	void CheckColorUpdate();
	void LoadTexture();
	void AddAnimationCount();
	void UpdateTextureFrame(ShowInfo showInfo);
	void Show();
	void ShowCrossed();

	void MoveUp(Direction textureDirection);
	void MoveDown(Direction textureDirection);
	void MoveLeft(Direction textrueDirection);
	void MoveRight(Direction textureDirection);

	void UndoMoveUp(Direction textureDirection);
	void UndoMoveDown(Direction textureDirection);
	void UndoMoveLeft(Direction textrueDirection);
	void UndoMoveRight(Direction textureDirection);
};

class EmptyObject : public ObjectBase {
public:
	EmptyObject();
	void updateTexture(ShowInfo showInfo);
};

class TextObject : public ObjectBase {
public:
	TextObject();
	void updateTexture(ShowInfo showInfo);
};

class TiledObject : public ObjectBase {
public:
	TiledObject();
	void updateTexture(ShowInfo showInfo);
};

class StaticObject : public ObjectBase {
public:
	StaticObject();
	void updateTexture(ShowInfo showInfo);
};

class CharacterObject : public ObjectBase {
public:
	CharacterObject();
	void updateTexture(ShowInfo showInfo);
};

class AnimationObject : public ObjectBase {
public:
	AnimationObject();
	void updateTexture(ShowInfo showInfo);
};

class DirectionObject : public ObjectBase {
public:
	DirectionObject();
	void updateTexture(ShowInfo showInfo);
};

class AnimationDirectionObject : public ObjectBase {
public:
	AnimationDirectionObject();
	void updateTexture(ShowInfo showInfo);
};