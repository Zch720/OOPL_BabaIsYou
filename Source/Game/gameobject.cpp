#include "stdafx.h"
#include "gameobject.h"

#define MOVE_STEP	4

Gameobject::Gameobject(GameobjectId gameobjectId, CPoint gameBoardPosition, CPoint textureOriginPosition, int textureSize) {
	this->gameobjectId = gameobjectId;
	this->gameBoardPosition = gameBoardPosition;

	// TODO: load textures

	/*** test ***/
	std::string textureDir = GetTexturePathByGameobjectId(gameobjectId);
	texture.LoadBitmapByString({ textureDir + "0_1.bmp" }, 0x00FF00);
	/************/

	CPoint texturePosition = CPoint(textureSize * gameBoardPosition.x, textureSize * gameBoardPosition.y);
	texturePosition += textureOriginPosition;
	texture.SetTopLeft(texturePosition.x, texturePosition.y);
	this->textureSize = textureSize;
	textureFactor = (double)textureSize / texture.GetWidth();
}

void Gameobject::Show() {
	updatePosition();
	texture.ShowBitmap(textureFactor);
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
			top -= moveDistance;
		}
		else if (direction == 1) {
			left += moveDistance;
		}
		else if (direction == 2) {
			top += moveDistance;
		}
		else if (direction == 3) {
			left -= moveDistance;
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
			top += moveDistance;
		}
		else if (direction == 1) {
			left -= moveDistance;
		}
		else if (direction == 2) {
			top -= moveDistance;
		}
		else if (direction == 3) {
			left += moveDistance;
		}

		texture.SetTopLeft(left, top);
		undoRemainStep--;
	}
}

void Gameobject::moveUp() {
	direction = 0;
	remainStep = MOVE_STEP;
	gameBoardPosition.y -= 1;
}

void Gameobject::moveDown() {
	direction = 2;
	remainStep = MOVE_STEP;
	gameBoardPosition.y += 1;
}

void Gameobject::moveLeft() {
	direction = 3;
	remainStep = MOVE_STEP;
	gameBoardPosition.x -= 1;
}

void Gameobject::moveRight() {
	direction = 1;
	remainStep = MOVE_STEP;
	gameBoardPosition.x += 1;
}

void Gameobject::undoUp() {
	direction = 0;
	undoRemainStep = MOVE_STEP;
	gameBoardPosition.y += 1;
}

void Gameobject::undoDown() {
	direction = 2;
	undoRemainStep = MOVE_STEP;
	gameBoardPosition.y -= 1;
}

void Gameobject::undoLeft() {
	direction = 3;
	undoRemainStep = MOVE_STEP;
	gameBoardPosition.x += 1;
}

void Gameobject::undoRight() {
	direction = 1;
	undoRemainStep = MOVE_STEP;
	gameBoardPosition.x -= 1;
}