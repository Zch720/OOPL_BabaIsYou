#pragma once

#include "../../Library/gameutil.h"
#include "../../Expansion/point.h"
#include "property_id.h"
#include "gameobject_id.h"
#include "gameobject_type.h"

enum Direction {
	DIRECTION_RIGHT = 0,
	DIRECTION_UP = 1,
	DIRECTION_LEFT = 2,
	DIRECTION_DOWN = 3
};

struct GameobjectInfo {
	GameobjectId id;
	GameobjectType type;
	Point position;
};

class Gameobject {
private:
	const int MOVE_STEP = 4;

	GameobjectInfo info;
	
	game_framework::CMovingBitmap texture;
	game_framework::CMovingBitmap textCrossed;
	bool textureSetted = false;
	bool alreadyReplace = false;
	PropId textureColorPropId = PROP_NONE;
	Direction textureDirection = DIRECTION_RIGHT;
	int textureCount = 0;

	Direction moveDirection = DIRECTION_RIGHT;
	int characterTextureStep = 0;
	int moveRemainStep = 0;

	void showCharacterTexture();
	void showDirectionalTexture();
	void showStaticTexture();
	void showTiledTexture(int otherInformation);
	void showTextTexture(int otherInformation);

	int getTextureMoveDistance();
	void updateTexturePosition();

public:
	Gameobject(GameobjectId gameobjectId, Point position);

	GameobjectInfo GetInfo();
	Direction GetTextureDirection();

	void SetReplace(bool value);
	void SetTextureDirection(Direction direction);

	bool Replace(GameobjectId replaceGameobjectId);
	void SetTexture(Point textureOriginPosition, PropId colorPropId);

	/*
		OBJECT_TYPE_CHARACTER: no otherInformation
		OBJECT_TYPE_DIRECTIONAL: no otherInformation
		OBJECT_TYPE_STATIC: no otherInformation
		OBJECT_TYPE_TILED: otherInformation denote gameobject connect status
		OBJECT_TYPE_TEXT: otherInformation denote text is dark(0) or light(1)
	*/
	void Show(int otherInformation = 0);
	void UpdateTextureCount();

	bool IsMoving();

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	void UndoUp(Direction direction);
	void UndoDown(Direction direction);
	void UndoLeft(Direction direction);
	void UndoRight(Direction direction);
};