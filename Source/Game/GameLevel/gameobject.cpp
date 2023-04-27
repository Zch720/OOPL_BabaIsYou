#include "stdafx.h"
#include "gameobject.h"
#include "texture_manager.h"
#include "../../Expansion/log.h"

Gameobject::Gameobject(GameobjectId gameobjectId, Point gameBoardPosition) {
	info.id = gameobjectId;
	info.position = gameBoardPosition;
	info.type = static_cast<GameobjectType>(GetGameobjectTypeById(gameobjectId));
	textCrossed = TextureManager::GetGameobjecTexture(GAMEOBJECT_CROSSED, PROP_NONE);
	textureCount = rand() % 3;
}

GameobjectInfo Gameobject::GetInfo() {
	return info;
}
Direction Gameobject::GetTextureDirection() {
	return textureDirection;
}

void Gameobject::SetReplace(bool value) {
	alreadyReplace = value;
}
void Gameobject::SetTextureDirection(Direction direction) {
	textureDirection = direction;
}

bool Gameobject::Replace(GameobjectId replaceGameobjectId) {
	if (alreadyReplace) return false;

	Point texturePosition = {texture.GetLeft(), texture.GetTop()};
	info.id = replaceGameobjectId;
	info.type = static_cast<GameobjectType>(GetGameobjectTypeById(replaceGameobjectId));
	texture = TextureManager::GetGameobjecTexture(replaceGameobjectId, PROP_NONE);
	texture.SetTopLeft(texturePosition.x, texturePosition.y);
	return alreadyReplace = true;
}
void Gameobject::SetTexture(PropId colorPropId) {
	if (colorPropId == textureColorPropId && textureSetted) return;
	
	Point texturePosition = info.position * TextureManager::GetTextureSize() + TextureManager::GetTextureOriginPosition();
	textureColorPropId = colorPropId;
	texture = TextureManager::GetGameobjecTexture(info.id, textureColorPropId);
	texture.SetTopLeft(texturePosition.x, texturePosition.y);

	textureSetted = true;
}


void Gameobject::showCharacterTexture() {
	texture.SetFrameIndexOfBitmap(((textureDirection << 2) + characterTextureStep) * 3 + textureCount);
	texture.ShowBitmap();
}
void Gameobject::showDirectionalTexture() {
	texture.SetFrameIndexOfBitmap(textureDirection * 3 + textureCount);
	texture.ShowBitmap();
}
void Gameobject::showStaticTexture() {
	texture.SetFrameIndexOfBitmap(textureCount);
	texture.ShowBitmap();
}
void Gameobject::showTiledTexture(int otherInformation) {
	texture.SetFrameIndexOfBitmap(otherInformation * 3 + textureCount);
	texture.ShowBitmap();
}
void Gameobject::showTextTexture(int otherInformation) {
	texture.SetFrameIndexOfBitmap((otherInformation & 0b1) * 3 + textureCount);
	texture.ShowBitmap();
	if (otherInformation & 0b10) {
		textCrossed.SetFrameIndexOfBitmap(textureCount);
		textCrossed.SetTopLeft(texture.GetLeft(), texture.GetTop());
		textCrossed.ShowBitmap();
	}
}

/*
	OBJECT_TYPE_CHARACTER: no otherInformation
	OBJECT_TYPE_DIRECTIONAL: no otherInformation
	OBJECT_TYPE_STATIC: no otherInformation
	OBJECT_TYPE_TILED: otherInformation denote gameobject connect status
	OBJECT_TYPE_TEXT: first bit in otherInformation denote text is dark(0) or light(1), second bit in otherInformation denote text is useable(0 or 1)
*/
void Gameobject::Show(int otherInformation) {
	updateTexturePosition();
	switch (info.type) {
	case OBJECT_TYPE_CHARACTER:
		showCharacterTexture();
		break;
	case OBJECT_TYPE_DIRECTIONAL:
		showDirectionalTexture();
		break;
	case OBJECT_TYPE_STATIC:
		showStaticTexture();
		break;
	case OBJECT_TYPE_TILED:
		showTiledTexture(otherInformation);
		break;
	case OBJECT_TYPE_TEXT:
		showTextTexture(otherInformation);
		break;
	}
}
void Gameobject::UpdateTextureCount() {
	this->textureCount = (this->textureCount + 1) % 3;
}

int Gameobject::getTextureMoveDistance() {
	int result = TextureManager::GetTextureSize() / MOVE_STEP;
	if (moveRemainStep <= TextureManager::GetTextureSize() % MOVE_STEP) {
		result++;
	}
	return result;
}
void Gameobject::updateTexturePosition() {
	if (moveRemainStep != 0) {
		int left = texture.GetLeft();
		int top = texture.GetTop();

		switch (moveDirection) {
		case DIRECTION_UP:
			top -= getTextureMoveDistance();
			break;
		case DIRECTION_DOWN:
			top += getTextureMoveDistance();
			break;
		case DIRECTION_LEFT:
			left -= getTextureMoveDistance();
			break;
		case DIRECTION_RIGHT:
			left += getTextureMoveDistance();
			break;
		}

		texture.SetTopLeft(left, top);
		moveRemainStep--;
	}
}

bool Gameobject::IsMoving() {
	return moveRemainStep != 0;
}

void Gameobject::MoveUp() {
	while (moveRemainStep != 0) {
		updateTexturePosition();
	}
	moveDirection = textureDirection = DIRECTION_UP;
	info.position.y -= 1;
	moveRemainStep = MOVE_STEP;
	characterTextureStep = (characterTextureStep + 1) & 3;
}
void Gameobject::MoveDown() {
	while (moveRemainStep != 0) {
		updateTexturePosition();
	}
	moveDirection = textureDirection = DIRECTION_DOWN;
	info.position.y += 1;
	moveRemainStep = MOVE_STEP;
	characterTextureStep = (characterTextureStep + 1) & 3;
}
void Gameobject::MoveLeft() {
	while (moveRemainStep != 0) {
		updateTexturePosition();
	}
	moveDirection = textureDirection = DIRECTION_LEFT;
	info.position.x -= 1;
	moveRemainStep = MOVE_STEP;
	characterTextureStep = (characterTextureStep + 1) & 3;
}
void Gameobject::MoveRight() {
	while (moveRemainStep != 0) {
		updateTexturePosition();
	}
	moveDirection = textureDirection = DIRECTION_RIGHT;
	info.position.x += 1;
	moveRemainStep = MOVE_STEP;
	characterTextureStep = (characterTextureStep + 1) & 3;
}

/*
	direction denote origion gameobject texture direction
*/
void Gameobject::UndoUp(Direction direction) {
	while (moveRemainStep != 0) {
		updateTexturePosition();
	}
	moveDirection = DIRECTION_DOWN;
	textureDirection = direction;
	info.position.y += 1;
	moveRemainStep = MOVE_STEP;
	characterTextureStep = (characterTextureStep + 3) & 3;
}
void Gameobject::UndoDown(Direction direction) {
	while (moveRemainStep != 0) {
		updateTexturePosition();
	}
	moveDirection = DIRECTION_UP;
	textureDirection = direction;
	info.position.y -= 1;
	moveRemainStep = MOVE_STEP;
	characterTextureStep = (characterTextureStep + 3) & 3;
}
void Gameobject::UndoLeft(Direction direction) {
	while (moveRemainStep != 0) {
		updateTexturePosition();
	}
	moveDirection = DIRECTION_RIGHT;
	textureDirection = direction;
	info.position.x += 1;
	moveRemainStep = MOVE_STEP;
	characterTextureStep = (characterTextureStep + 3) & 3;
}
void Gameobject::UndoRight(Direction direction) {
	while (moveRemainStep != 0) {
		updateTexturePosition();
	}
	moveDirection = DIRECTION_LEFT;
	textureDirection = direction;
	info.position.x -= 1;
	moveRemainStep = MOVE_STEP;
	characterTextureStep = (characterTextureStep + 3) & 3;
}