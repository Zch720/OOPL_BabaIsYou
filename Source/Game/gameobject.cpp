#include "stdafx.h"
#include "gameobject.h"
#include "texture_manager.h"
#include "../Expansion/log.h"

#define MOVE_STEP	4

Gameobject::Gameobject(GameobjectId gameobjectId, PropId colorPropId, CPoint gameBoardPosition, CPoint textureOriginPosition, int textureSize) {
	this->gameobjectId = gameobjectId;
	this->gameBoardPosition = gameBoardPosition;
	this->textureOriginPosition = textureOriginPosition;
	this->textureSize = textureSize;

	int gameobjectTypeNum = GetGameobjectTypeById(gameobjectId);
	if (gameobjectTypeNum == -1) {
		char message[125];
		sprintf_s(message, "gameobject id %d can't turn to gameobject type.", gameobjectId);
		logError(message);
	}
	this->gameobjectType = static_cast<GameobjectType>(gameobjectTypeNum);

	texture = TextureManager::GetGameobjecTexture(gameobjectId, colorPropId);
	
	CPoint texturePosition = CPoint(textureSize * gameBoardPosition.x, textureSize * gameBoardPosition.y);
	texturePosition += textureOriginPosition;
	texture.SetTopLeft(texturePosition.x, texturePosition.y);
	textureFactor = (double)textureSize / texture.GetWidth();
}

void Gameobject::Show(int textureCount, int otherCount) {
	if (gameobjectType == OBJECT_TYPE_STATIC) {
		texture.SetFrameIndexOfBitmap(textureCount);
	}
	else if (gameobjectType == OBJECT_TYPE_CHARACTER) {
		texture.SetFrameIndexOfBitmap(((direction << 2) + textureStepCount) * 3 + textureCount);
	}
	else if (gameobjectType == OBJECT_TYPE_TILED) {
		// otherCount is connect status
		texture.SetFrameIndexOfBitmap(otherCount * 3 + textureCount);
	}

	updatePosition();
	texture.ShowBitmap(textureFactor);
}

void Gameobject::setTextureColor(PropId colorPropId) {
	texture = TextureManager::GetGameobjecTexture(gameobjectId, colorPropId);
}

void Gameobject::updatePosition() {
	if (remainStep != 0) {
		int left = texture.GetLeft();
		int top = texture.GetTop();
		int moveDistance = textureSize / MOVE_STEP;
		if (remainStep <= textureSize % MOVE_STEP) {
			moveDistance++;
		}

		if (direction == 0) {
			left += moveDistance;
		}
		else if (direction == 1) {
			top -= moveDistance;
		}
		else if (direction == 2) {
			left -= moveDistance;
		}
		else if (direction == 3) {
			top += moveDistance;
		}
		
		texture.SetTopLeft(left, top);
		remainStep--;
	}
	if (undoRemainStep != 0) {
		int left = texture.GetLeft();
		int top = texture.GetTop();
		int moveDistance = textureSize / MOVE_STEP;
		if (undoRemainStep <= textureSize % MOVE_STEP) {
			moveDistance++;
		}

		if (direction == 0) {
			left -= moveDistance;
		}
		else if (direction == 1) {
			top += moveDistance;
		}
		else if (direction == 2) {
			left += moveDistance;
		}
		else if (direction == 3) {
			top -= moveDistance;
		}

		texture.SetTopLeft(left, top);
		undoRemainStep--;
	}
}

void Gameobject::moveUp() {
	direction = 1;
	remainStep = MOVE_STEP;
	gameBoardPosition.y -= 1;
	textureStepCount = (textureStepCount + 1) & 3;
}

void Gameobject::moveDown() {
	direction = 3;
	remainStep = MOVE_STEP;
	gameBoardPosition.y += 1;
	textureStepCount = (textureStepCount + 1) & 3;
}

void Gameobject::moveLeft() {
	direction = 2;
	remainStep = MOVE_STEP;
	gameBoardPosition.x -= 1;
	textureStepCount = (textureStepCount + 1) & 3;
}

void Gameobject::moveRight() {
	direction = 0;
	remainStep = MOVE_STEP;
	gameBoardPosition.x += 1;
	textureStepCount = (textureStepCount + 1) & 3;
}

void Gameobject::undoUp() {
	direction = 1;
	undoRemainStep = MOVE_STEP;
	gameBoardPosition.y += 1;
	textureStepCount = (textureStepCount + 3) & 3;
}

void Gameobject::undoDown() {
	direction = 3;
	undoRemainStep = MOVE_STEP;
	gameBoardPosition.y -= 1;
	textureStepCount = (textureStepCount + 3) & 3;
}

void Gameobject::undoLeft() {
	direction = 2;
	undoRemainStep = MOVE_STEP;
	gameBoardPosition.x += 1;
	textureStepCount = (textureStepCount + 3) & 3;
}

void Gameobject::undoRight() {
	direction = 0;
	undoRemainStep = MOVE_STEP;
	gameBoardPosition.x -= 1;
	textureStepCount = (textureStepCount + 3) & 3;
}