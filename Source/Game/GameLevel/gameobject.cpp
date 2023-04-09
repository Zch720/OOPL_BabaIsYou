#include "stdafx.h"
#include "gameobject.h"
#include "texture_manager.h"
#include "../../Expansion/log.h"

Gameobject::Gameobject(const GameobjectId gameobjectId, const Point gameBoardPosition, const int textureSize) {
	this->gameobjectId = gameobjectId;
	this->gameBoardPosition = gameBoardPosition;
	this->textureSize = textureSize;
	this->gameobjectType = static_cast<GameobjectType>(GetGameobjectTypeById(gameobjectId));
}

void Gameobject::setTextureWithColor(const Point textureOriginPosition, const PropId colorPropId) {
	if (colorPropId == textureColorPropId && textureSetted) return;

	textureColorPropId = colorPropId;
	texture = TextureManager::GetGameobjecTexture(gameobjectId, textureColorPropId);

	CPoint texturePosition = CPoint(textureSize * gameBoardPosition.x, textureSize * gameBoardPosition.y);
	texturePosition += textureOriginPosition;
	texture.SetTopLeft(texturePosition.x, texturePosition.y);
	
	textureFatcor = (double)textureSize / texture.GetWidth();

	textureSetted = true;
}

/*
	OBJECT_TYPE_CHARACTER: no otherInformation
	OBJECT_TYPE_DIRECTIONAL: no otherInformation
	OBJECT_TYPE_STATIC: no otherInformation
	OBJECT_TYPE_TILED: otherInformation denote gameobject connect status
	OBJECT_TYPE_TEXT: otherInformation denote text is dark(0) or light(1)
*/
void Gameobject::show(const int textureCount, const int otherInformation) {
	switch (gameobjectType) {
	case OBJECT_TYPE_CHARACTER:
		texture.SetFrameIndexOfBitmap(((textureDirection << 2) + characterTextureStep) * 3 + textureCount);
		break;
	case OBJECT_TYPE_DIRECTIONAL:
		texture.SetFrameIndexOfBitmap(textureDirection * 3 + textureCount);
		break;
	case OBJECT_TYPE_STATIC:
		texture.SetFrameIndexOfBitmap(textureCount);
		break;
	case OBJECT_TYPE_TILED:
	case OBJECT_TYPE_TEXT:
		texture.SetFrameIndexOfBitmap(otherInformation * 3 + textureCount);
		break;
	}

	updatePosition();
	
	texture.ShowBitmap(textureFatcor);
}

void Gameobject::updatePosition() {
	if (moveRemainStep != 0) {
		int left = texture.GetLeft();
		int top = texture.GetTop();
		int moveDistance = textureSize / MOVE_STEP;
		if (moveRemainStep <= textureSize % MOVE_STEP) {
			moveDistance++;
		}

		switch (moveDirection) {
		case DIRECTION_UP:
			top -= moveDistance;
			break;
		case DIRECTION_DOWN:
			top += moveDistance;
			break;
		case DIRECTION_LEFT:
			left -= moveDistance;
			break;
		case DIRECTION_RIGHT:
			left += moveDistance;
			break;
		}

		texture.SetTopLeft(left, top);
		moveRemainStep--;
	}
}

void Gameobject::moveUp() {
	while (moveRemainStep != 0) {
		updatePosition();
	}
	moveDirection = DIRECTION_UP;
	textureDirection = DIRECTION_UP;
	gameBoardPosition.y -= 1;
	moveRemainStep = MOVE_STEP;
	characterTextureStep = (characterTextureStep + 1) & 3;
}
void Gameobject::moveDown() {
	while (moveRemainStep != 0) {
		updatePosition();
	}
	moveDirection = DIRECTION_DOWN;
	textureDirection = DIRECTION_DOWN;
	gameBoardPosition.y += 1;
	moveRemainStep = MOVE_STEP;
	characterTextureStep = (characterTextureStep + 1) & 3;
}
void Gameobject::moveLeft() {
	while (moveRemainStep != 0) {
		updatePosition();
	}
	moveDirection = DIRECTION_LEFT;
	textureDirection = DIRECTION_LEFT;
	gameBoardPosition.x -= 1;
	moveRemainStep = MOVE_STEP;
	characterTextureStep = (characterTextureStep + 1) & 3;
}
void Gameobject::moveRight() {
	while (moveRemainStep != 0) {
		updatePosition();
	}
	moveDirection = DIRECTION_RIGHT;
	textureDirection = DIRECTION_RIGHT;
	gameBoardPosition.x += 1;
	moveRemainStep = MOVE_STEP;
	characterTextureStep = (characterTextureStep + 1) & 3;
}

/*
	direction denote origion gameobject direction
*/
void Gameobject::undoUp(Direction direction) {
	while (moveRemainStep != 0) {
		updatePosition();
	}
	moveDirection = DIRECTION_DOWN;
	textureDirection = direction;
	gameBoardPosition.y += 1;
	moveRemainStep = MOVE_STEP;
	characterTextureStep = (characterTextureStep + 3) & 3;
}
void Gameobject::undoDown(Direction direction) {
	while (moveRemainStep != 0) {
		updatePosition();
	}
	moveDirection = DIRECTION_UP;
	textureDirection = direction;
	gameBoardPosition.y -= 1;
	moveRemainStep = MOVE_STEP;
	characterTextureStep = (characterTextureStep + 3) & 3;
}
void Gameobject::undoLeft(Direction direction) {
	while (moveRemainStep != 0) {
		updatePosition();
	}
	moveDirection = DIRECTION_RIGHT;
	textureDirection = direction;
	gameBoardPosition.x += 1;
	moveRemainStep = MOVE_STEP;
	characterTextureStep = (characterTextureStep + 3) & 3;
}
void Gameobject::undoRight(Direction direction) {
	while (moveRemainStep != 0) {
		updatePosition();
	}
	moveDirection = DIRECTION_LEFT;
	textureDirection = direction;
	gameBoardPosition.x -= 1;
	moveRemainStep = MOVE_STEP;
	characterTextureStep = (characterTextureStep + 3) & 3;
}