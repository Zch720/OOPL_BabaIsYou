#include "stdafx.h"
#include <stdlib.h>
#include "objects.h"
#include "texture_manager.h"
#include "property_manager.h"
#include "../../Expansion/log.h"

// Object Info
bool ObjectInfo::operator==(const ObjectInfo &info) const {
	return genId == info.genId;
}

bool ObjectInfo::operator<(const ObjectInfo &info) {
	return genId < info.genId;
}

size_t ObjectInfo::GetHash() const {
	return genId;
}

size_t std::hash<ObjectInfo>::operator()(const ObjectInfo &info) const {
	return info.GetHash();
}


// Object Base
ObjectBase::ObjectBase(ObjectType type) {
	info.type = type;
	textureCount = rand() % 3;
	crossed = TextureManager::GetTexture(OBJECT_CROSSED, PROPERTY_NONE);
}

bool ObjectBase::IsMoving() {
	return textureRemainStep != 0;
}

bool ObjectBase::HasProperty(PropertyId id) {
	return PropertyManager::ObjectHasProperty(info.objectId, id);
}

ObjectInfo ObjectBase::GetInfo() {
	return info;
}

Point ObjectBase::GetPosition() {
	return info.position;
}

int ObjectBase::GetGenId() {
	if (!genIdSetted) {
		Log::LogError("<Objects> The object gen id was not set.");
	}
	return info.genId;
}

ObjectId ObjectBase::GetObjectId() {
	return info.objectId;
}

Direction ObjectBase::GetTextureDirection() {
	return info.textureDirection;
}

ObjectType ObjectBase::GetObjectType() {
	return info.type;
}

int ObjectBase::GetPropertyCount() {
	return PropertyManager::GetObjectColor(info.objectId);
}

void ObjectBase::SetPosition(POINT point) {
	info.position = point;
	texturePosition = TextureManager::GetTextureOrogionPosition();
	texturePosition += TextureManager::GetTextureSize() * info.position;
}

void ObjectBase::SetGenId(int id) {
	if (genIdSetted) {
		Log::LogError("<Objects> The object gen id has been set.");
	}
	genIdSetted = true;
	info.genId = id;
}

void ObjectBase::SetObjectId(ObjectId id) {
	info.objectId = id;
}

void ObjectBase::SetTextureDirection(Direction direction) {
	info.textureDirection = direction;
}

void ObjectBase::CheckColorUpdate() {
	if (currentColor != PropertyManager::GetObjectColor(info.objectId)) LoadTexture();
}

void ObjectBase::LoadTexture() {
	if (info.objectId == OBJECT_NONE) return;
	currentColor = PropertyManager::GetObjectColor(info.objectId);
	texture = TextureManager::GetTexture(info.objectId, currentColor);
	texture.SetTopLeft(texturePosition.x, texturePosition.y);
	crossed.SetTopLeft(texturePosition.x, texturePosition.y);
}

void ObjectBase::AddAnimationCount() {
	animationShowCount = (animationShowCount + 1) & 0b11;
}

void ObjectBase::UpdateTextureFrame(ShowInfo info) {
	updateTextureCount(info.nextTexture);
	updateTexture(info);
	updateTexturePosition();
	texturePositionAddOffset(info.textureOffset);
} 

void ObjectBase::Show() {
	texture.ShowBitmap();
}

void ObjectBase::ShowCrossed() {
	crossed.ShowBitmap();
}

void ObjectBase::updateTexturePosition() {
	if (!textureRemainStep) return;

	if (moveDirection == DIRECTION_UP) texturePosition.y -= getTextureMoveDistance();
	else if (moveDirection == DIRECTION_DOWN) texturePosition.y += getTextureMoveDistance();
	else if (moveDirection == DIRECTION_LEFT) texturePosition.x -= getTextureMoveDistance();
	else if (moveDirection == DIRECTION_RIGHT) texturePosition.x += getTextureMoveDistance();

	textureRemainStep--;
}

void ObjectBase::texturePositionAddOffset(Point offset) {
	Point position = texturePosition + offset;
	texture.SetTopLeft(position.x, position.y);
	crossed.SetTopLeft(position.x, position.y);
}

void ObjectBase::updateTextureCount(bool nextTexture) {
	if (!nextTexture) return;
	textureCount++;
	if (textureCount == 3) textureCount = 0;
}

void ObjectBase::MoveUp(Direction textureDirection) {
	while (textureRemainStep) {
		updateTexturePosition();
	}
	moveDirection = DIRECTION_UP;
	info.textureDirection = textureDirection;
	info.position = info.position.Up();
	textureRemainStep = MAX_TEXTURE_STEP;
	characterShowCount = (characterShowCount + 1) & 0b11;
}

void ObjectBase::MoveDown(Direction textureDirection) {
	while (textureRemainStep) {
		updateTexturePosition();
	}
	moveDirection = info.textureDirection = DIRECTION_DOWN;
	info.textureDirection = textureDirection;
	info.position = info.position.Down();
	textureRemainStep = MAX_TEXTURE_STEP;
	characterShowCount = (characterShowCount + 1) & 0b11;
}

void ObjectBase::MoveLeft(Direction textureDirection) {
	while (textureRemainStep) {
		updateTexturePosition();
	}
	moveDirection = info.textureDirection = DIRECTION_LEFT;
	info.textureDirection = textureDirection;
	info.position = info.position.Left();
	textureRemainStep = MAX_TEXTURE_STEP;
	characterShowCount = (characterShowCount + 1) & 0b11;
}

void ObjectBase::MoveRight(Direction textureDirection) {
	while (textureRemainStep) {
		updateTexturePosition();
	}
	moveDirection = info.textureDirection = DIRECTION_RIGHT;
	info.textureDirection = textureDirection;
	info.position = info.position.Right();
	textureRemainStep = MAX_TEXTURE_STEP;
	characterShowCount = (characterShowCount + 1) & 0b11;
}

void ObjectBase::UndoMoveUp(Direction textureDirection) {
	while (textureRemainStep) {
		updateTexturePosition();
	}
	moveDirection = info.textureDirection = DIRECTION_DOWN;
	info.textureDirection = textureDirection;
	info.position = info.position.Down();
	textureRemainStep = MAX_TEXTURE_STEP;
	characterShowCount = (characterShowCount + 3) & 0b11;
}

void ObjectBase::UndoMoveDown(Direction textureDirection) {
	while (textureRemainStep) {
		updateTexturePosition();
	}
	moveDirection = DIRECTION_UP;
	info.textureDirection = textureDirection;
	info.position = info.position.Up();
	textureRemainStep = MAX_TEXTURE_STEP;
	characterShowCount = (characterShowCount + 3) & 0b11;
}

void ObjectBase::UndoMoveLeft(Direction textureDirection) {
	while (textureRemainStep) {
		updateTexturePosition();
	}
	moveDirection = info.textureDirection = DIRECTION_RIGHT;
	info.textureDirection = textureDirection;
	info.position = info.position.Right();
	textureRemainStep = MAX_TEXTURE_STEP;
	characterShowCount = (characterShowCount + 3) & 0b11;
}

void ObjectBase::UndoMoveRight(Direction textureDirection) {
	while (textureRemainStep) {
		updateTexturePosition();
	}
	moveDirection = info.textureDirection = DIRECTION_LEFT;
	info.textureDirection = textureDirection;
	info.position = info.position.Left();
	textureRemainStep = MAX_TEXTURE_STEP;
	characterShowCount = (characterShowCount + 3) & 0b11;
}

int ObjectBase::getTextureMoveDistance() {
	return TextureManager::GetTextureSize() / MAX_TEXTURE_STEP + 
		(textureRemainStep <= TextureManager::GetTextureSize() % MAX_TEXTURE_STEP);
}


EmptyObject::EmptyObject() : ObjectBase(TYPE_NONE) {}

void EmptyObject::updateTexture(ShowInfo showInfo) {}


TextObject::TextObject() : ObjectBase(TYPE_TEXT) {}

void TextObject::updateTexture(ShowInfo showInfo) {
	if (showInfo.nextTexture) textureCount = (textureCount + 1) % 3;
	texture.SetFrameIndexOfBitmap(showInfo.textConnected * 3 + textureCount);
	crossed.SetFrameIndexOfBitmap(textureCount);
}


TiledObject::TiledObject() : ObjectBase(TYPE_TILED) {}

void TiledObject::updateTexture(ShowInfo showInfo) {
	if (showInfo.nextTexture) textureCount = (textureCount + 1) % 3;
	texture.SetFrameIndexOfBitmap(showInfo.tiledConnected * 3 + textureCount);
}


StaticObject::StaticObject() : ObjectBase(TYPE_STATIC) {}

void StaticObject::updateTexture(ShowInfo showInfo) {
	if (showInfo.nextTexture) textureCount = (textureCount + 1) % 3;
	texture.SetFrameIndexOfBitmap(textureCount);
}


CharacterObject::CharacterObject() : ObjectBase(TYPE_CHARACTER) {}

void CharacterObject::updateTexture(ShowInfo showInfo) {
	if (showInfo.nextTexture) textureCount = (textureCount + 1) % 3;
	texture.SetFrameIndexOfBitmap(((GetTextureDirection() << 2) + characterShowCount) * 3 + textureCount);
}


AnimationObject::AnimationObject() : ObjectBase(TYPE_ANIMATION) {}

void AnimationObject::updateTexture(ShowInfo showInfo) {
	if (showInfo.nextTexture) textureCount = (textureCount + 1) % 3;
	texture.SetFrameIndexOfBitmap(animationShowCount * 3 + textureCount);
}


DirectionObject::DirectionObject() : ObjectBase(TYPE_DIRECTION) {}

void DirectionObject::updateTexture(ShowInfo showInfo) {
	if (showInfo.nextTexture) textureCount = (textureCount + 1) % 3;
	texture.SetFrameIndexOfBitmap(GetTextureDirection() * 3 + textureCount);
}


AnimationDirectionObject::AnimationDirectionObject() : ObjectBase(TYPE_ANIMATION_DIRECTION) {}

void AnimationDirectionObject::updateTexture(ShowInfo showInfo) {
	if (showInfo.nextTexture) textureCount = (textureCount + 1) % 3;
	texture.SetFrameIndexOfBitmap(((GetTextureDirection() << 2) + animationShowCount) * 3 + textureCount);
}