#include "stdafx.h"
#include "gameobject.h"
#include "../Expansion/log.h"

#define MOVE_STEP	4

Gameobject::Gameobject(GameobjectId gameobjectId, std::string colorDir, CPoint gameBoardPosition, CPoint textureOriginPosition, int textureSize) {
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

	setTextureColorDir(colorDir);
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

void Gameobject::setTextureColorDir(std::string colorDir) {
	std::string textureDir = GetTexturePathByGameobjectId(gameobjectId) + colorDir + "/";

	switch (gameobjectType) {
	case OBJECT_TYPE_CHARACTER:
		loadCharacterTexture(textureDir);
		break;
	case OBJECT_TYPE_TILED:
		loadTiledTexture(textureDir);
		break;
	case OBJECT_TYPE_STATIC:
		loadStaticTexture(textureDir);
		break;
	}
}

void Gameobject::loadTextureStrings(std::vector<std::string> &texturePaths) {
	texture = game_framework::CMovingBitmap();

	texture.LoadBitmapByString(texturePaths, 0x00FF00);

	CPoint texturePosition = CPoint(textureSize * gameBoardPosition.x, textureSize * gameBoardPosition.y);
	texturePosition += textureOriginPosition;
	texture.SetTopLeft(texturePosition.x, texturePosition.y);
	textureFactor = (double)textureSize / texture.GetWidth();
}

void Gameobject::loadCharacterTexture(std::string textureDir) {
	std::vector<std::string> texturePaths;
	char buffer[4];

	for (int directionCode = 0; directionCode < 4; directionCode++) {
		for (int stepCode = 0; stepCode < 4; stepCode++) {
			int textureCode = (directionCode << 3) | stepCode;
			_itoa(textureCode, buffer, 10);
			texturePaths.push_back(textureDir + buffer + "_1.bmp");
			texturePaths.push_back(textureDir + buffer + "_2.bmp");
			texturePaths.push_back(textureDir + buffer + "_3.bmp");
		}
	}
	loadTextureStrings(texturePaths);
}

void Gameobject::loadTiledTexture(std::string textureDir) {
	std::vector<std::string> texturePaths;
	char buffer[4];

	for (int connectCode = 0; connectCode < 15; connectCode++) {
		_itoa(connectCode, buffer, 10);
		texturePaths.push_back(textureDir + buffer + "_1.bmp");
		texturePaths.push_back(textureDir + buffer + "_2.bmp");
		texturePaths.push_back(textureDir + buffer + "_3.bmp");
	}
	loadTextureStrings(texturePaths);
}

void Gameobject::loadStaticTexture(std::string textureDir) {
	std::vector<std::string> texturePaths;

	texturePaths.push_back(textureDir + "0_1.bmp");
	texturePaths.push_back(textureDir + "0_2.bmp");
	texturePaths.push_back(textureDir + "0_3.bmp");

	loadTextureStrings(texturePaths);
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