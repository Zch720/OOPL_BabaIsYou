#include "stdafx.h"
#include "map_object.h"
#include "../../Expansion/log.h"
#include "../../Expansion/string_proc.h"

Mapobject::Mapobject() {}

Mapobject::Mapobject(MapobjectId mapobjectId, int world) {
	this->mapobjectId = mapobjectId;
}

bool Mapobject::IsMoving() {
	return moveRemainStep != 0;
}

void Mapobject::MoveUp(Point textureOrigionPosition) {
	clearRemainStep();
	mapobjectPosition.y -= 1;
	moveRemainStep = MAX_MOVE_STEP;
	moveDirection = DIRECTION_UP;
}

void Mapobject::MoveDown(Point textureOrigionPosition) {
	clearRemainStep();
	mapobjectPosition.y += 1;
	moveRemainStep = MAX_MOVE_STEP;
	moveDirection = DIRECTION_DOWN;
}

void Mapobject::MoveLeft(Point textureOrigionPosition) {
	clearRemainStep();
	mapobjectPosition.x -= 1;
	moveRemainStep = MAX_MOVE_STEP;
	moveDirection = DIRECTION_LEFT;
}

void Mapobject::MoveRight(Point textureOrigionPosition) {
	clearRemainStep();
	mapobjectPosition.x += 1;
	moveRemainStep = MAX_MOVE_STEP;
	moveDirection = DIRECTION_RIGHT;
}

void Mapobject::LoadTexture(int world, Point textureOrigionPosition) {
	std::string mapobfectPath = "./resources/map/" + intToString(world) + "/" + GetMapobjectNameById(mapobjectId);
	texture.LoadBitmapByString({ mapobfectPath + "_1.bmp", mapobfectPath + "_2.bmp", mapobfectPath + "_3.bmp" }, 0x00FF00);
	SetTexturePosition(textureOrigionPosition);
	texture.SetAnimation(250, false);
}

void Mapobject::SetTexturePosition(Point textureOrigionPosition) {
	Point realPosition = textureOrigionPosition + mapobjectPosition * 54;
	if (mapobjectId == BOX) {
		realPosition.AddOffset(-9, -9);
	}
	texture.SetTopLeft(realPosition.x, realPosition.y);
}

void Mapobject::Show() {
	updateTexturePosition();
	if (mapobjectId != NONE) {
		texture.ShowBitmap();
	}
}

void Mapobject::clearRemainStep() {
	while(IsMoving()) {
		updateTexturePosition();
	}
}

int Mapobject::getTextureMoveDistance() {
	return 54 / MAX_MOVE_STEP + ((moveRemainStep <= 54 % MAX_MOVE_STEP) ? 1 : 0);
}

void Mapobject::updateTexturePosition() {
	if (!moveRemainStep) return;

	Point texturePosition = { texture.GetLeft(), texture.GetTop() } ;
	if (moveDirection == DIRECTION_UP) texturePosition.y -= getTextureMoveDistance();
	else if (moveDirection == DIRECTION_DOWN) texturePosition.y += getTextureMoveDistance();
	else if (moveDirection == DIRECTION_LEFT) texturePosition.x -= getTextureMoveDistance();
	else if (moveDirection == DIRECTION_RIGHT) texturePosition.x += getTextureMoveDistance();
	texture.SetTopLeft(texturePosition.x, texturePosition.y);

	moveRemainStep--;
}