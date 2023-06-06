#include "stdafx.h"
#include <stdlib.h>
#include <cmath>
#include "effect_object.h"
#include "../../Expansion/point.h"

#define PI acos(-1)

game_framework::CMovingBitmap EffectTextures::winObjectEffectTexture54 = {};
game_framework::CMovingBitmap EffectTextures::winObjectEffectTexture108 = {};
game_framework::CMovingBitmap EffectTextures::dispearTexture54 = {};
game_framework::CMovingBitmap EffectTextures::dispearTexture108 = {};
game_framework::CMovingBitmap EffectTextures::moveUp54 = {};
game_framework::CMovingBitmap EffectTextures::moveUp108 = {};
game_framework::CMovingBitmap EffectTextures::moveDown54 = {};
game_framework::CMovingBitmap EffectTextures::moveDown108 = {};
game_framework::CMovingBitmap EffectTextures::moveLeft54 = {};
game_framework::CMovingBitmap EffectTextures::moveLeft108 = {};
game_framework::CMovingBitmap EffectTextures::moveRight54 = {};
game_framework::CMovingBitmap EffectTextures::moveRight108 = {};
game_framework::CMovingBitmap EffectTextures::deadHintBubble = {};

void EffectTextures::loadTexture(std::string path, int count, game_framework::CMovingBitmap& texture) {
	std::vector<std::string> paths;
	char filepath[260];

	paths.clear();
	for (int i = 0; i < count; i++) {
		sprintf_s(filepath, 260, "%s/%d.bmp", path.c_str(), i);
		paths.push_back(filepath);
	}
	texture.LoadBitmapByString(paths, 0x000000);
}

void EffectTextures::Init() {
	loadTexture("./resources/effect/win_object/54/", 5, winObjectEffectTexture54);
	loadTexture("./resources/effect/win_object/108/", 5, winObjectEffectTexture108);
	loadTexture("./resources/effect/dispear/54/", 19, dispearTexture54);
	loadTexture("./resources/effect/dispear/108/", 19, dispearTexture108);
	loadTexture("./resources/effect/move_up/54/", 18, moveUp54);
	loadTexture("./resources/effect/move_up/108/", 18, moveUp108);
	loadTexture("./resources/effect/move_down/54/", 18, moveDown54);
	loadTexture("./resources/effect/move_down/108/", 18, moveDown108);
	loadTexture("./resources/effect/move_left/54/", 18, moveLeft54);
	loadTexture("./resources/effect/move_left/108/", 18, moveLeft108);
	loadTexture("./resources/effect/move_right/54/", 18, moveRight54);
	loadTexture("./resources/effect/move_right/108/", 18, moveRight108);
	loadTexture("./resources/effect/dead_bubble/", 4, deadHintBubble);
}

game_framework::CMovingBitmap EffectTextures::GetWinObjectEffectTexture54() {
	return winObjectEffectTexture54;
}

game_framework::CMovingBitmap EffectTextures::GetWinObjectEffectTexture108() {
	return winObjectEffectTexture108;
}

game_framework::CMovingBitmap EffectTextures::GetDispearTexture54() {
	return dispearTexture54;
}

game_framework::CMovingBitmap EffectTextures::GetDispearTexture108() {
	return dispearTexture108;
}

game_framework::CMovingBitmap EffectTextures::GetMoveUpTexture54() {
	return moveUp54;
}

game_framework::CMovingBitmap EffectTextures::GetMoveUpTexture108() {
	return moveUp108;
}

game_framework::CMovingBitmap EffectTextures::GetMoveDownTexture54() {
	return moveDown54;
}

game_framework::CMovingBitmap EffectTextures::GetMoveDownTexture108() {
	return moveDown108;
}

game_framework::CMovingBitmap EffectTextures::GetMoveLeftTexture54() {
	return moveLeft54;
}

game_framework::CMovingBitmap EffectTextures::GetMoveLeftTexture108() {
	return moveLeft108;
}

game_framework::CMovingBitmap EffectTextures::GetMoveRightTexture54() {
	return moveRight54;
}

game_framework::CMovingBitmap EffectTextures::GetMoveRightTexture108() {
	return moveRight108;
}

game_framework::CMovingBitmap EffectTextures::GetDeadHintBubbleTexture() {
	return deadHintBubble;
}


bool EffectObjectBase::IsEnd() {
	return info.frame == frameCount;
}

void EffectObjectBase::Show() {
	updatePosition();
	updateTexture();
	texture.ShowBitmap();
}


WinObjectEffect::WinObjectEffect(POINT centerPosition, int size) {
	createInfo();
	loadTexture(size);
	this -> centerPosition = centerPosition;
}

void WinObjectEffect::loadTexture(int size) {
	if (size == 54) {
		texture = EffectTextures::GetWinObjectEffectTexture54();
	} else {
		texture = EffectTextures::GetWinObjectEffectTexture108();
	}
	texture.SetFrameIndexOfBitmap(0);
}

void WinObjectEffect::createInfo() {
	info.startDistance = rand() % 12 + 7;
	info.endDistance = rand() % 37 + 40;
	info.totalDistance = info.endDistance - info.startDistance;
	info.degree = PI * (rand() % 360) / 180;
	info.frame = (int)(info.totalDistance / 2);
	int frameTime = 1;
	for (int i = 0; i < textureCount - 2; i++) {
		frameTime += rand() % (info.frame - 5 - frameTime);
		info.changeFrameIndex.push_back(frameTime);
	}
	info.changeFrameIndex.push_back(info.frame - (rand() % 5) - 1);
}

void WinObjectEffect::updatePosition() {
	double currentDistance = (double)info.totalDistance * frameCount / info.frame + info.startDistance;
	int x = (int)(currentDistance * cos(info.degree) + centerPosition.x);
	int y = (int)(currentDistance * sin(info.degree) + centerPosition.y);
	texture.SetTopLeft(x - texture.GetWidth() / 2, y - texture.GetHeight() / 2);
}

void WinObjectEffect::updateTexture() {
	if (textureChangeCount < textureCount - 1 && info.changeFrameIndex[textureChangeCount] == frameCount) {
		texture.SetFrameIndexOfBitmap(++textureChangeCount);
	}
	frameCount++;
}


DispearEffect::DispearEffect(POINT centerPosition, int size) {
	createInfo();
	loadTexture(size);
	this -> centerPosition = Point(rand() % 51 - 25, rand() % 51 - 25) * (size / 54) + centerPosition;
	texture.SetTopLeft(this -> centerPosition.x - texture.GetWidth() / 2, this -> centerPosition.y - texture.GetHeight() / 2);
}

void DispearEffect::loadTexture(int size) {
	if (size == 54) {
		texture = EffectTextures::GetDispearTexture54();
	}
	else {
		texture = EffectTextures::GetDispearTexture108();
	}
	texture.SetFrameIndexOfBitmap(0);
}

void DispearEffect::createInfo() {
	info.frame = textureCount;
}

void DispearEffect::updatePosition() {}

void DispearEffect::updateTexture() {
	texture.SetFrameIndexOfBitmap(frameCount++);
}


MoveUpEffect::MoveUpEffect(POINT centerPosition, int size) {
	createInfo();
	loadTexture(size);
	this -> centerPosition = centerPosition;
}

void MoveUpEffect::loadTexture(int size) {
	if (size == 54) {
		texture = EffectTextures::GetMoveUpTexture54();
	}
	else {
		texture = EffectTextures::GetMoveUpTexture108();
	}
	texture.SetFrameIndexOfBitmap(0);
}

void MoveUpEffect::createInfo() {
	info.startDistance = rand() % 15 - 7;
	info.endDistance = info.startDistance + 27;
	info.totalDistance = 27;
	info.frame = textureCount;
}

void MoveUpEffect::updatePosition() {
	int y = centerPosition.y + (int)(info.totalDistance * frameCount / info.frame) + info.startDistance;
	texture.SetTopLeft(centerPosition.x - texture.GetWidth() / 2, y - texture.GetHeight() / 2);
}

void MoveUpEffect::updateTexture() {
	texture.SetFrameIndexOfBitmap(frameCount++);
}


MoveDownEffect::MoveDownEffect(POINT centerPosition, int size) {
	createInfo();
	loadTexture(size);
	this -> centerPosition = centerPosition;
}

void MoveDownEffect::loadTexture(int size) {
	if (size == 54) {
		texture = EffectTextures::GetMoveDownTexture54();
	}
	else {
		texture = EffectTextures::GetMoveDownTexture108();
	}
	texture.SetFrameIndexOfBitmap(0);
}

void MoveDownEffect::createInfo() {
	info.startDistance = rand() % 15 - 7;
	info.endDistance = info.startDistance + 27;
	info.totalDistance = 27;
	info.frame = textureCount;
}

void MoveDownEffect::updatePosition() {
	int y = centerPosition.y - (int)(info.totalDistance * frameCount / info.frame) - info.startDistance;
	texture.SetTopLeft(centerPosition.x - texture.GetWidth() / 2, y - texture.GetHeight() / 2);
}

void MoveDownEffect::updateTexture() {
	texture.SetFrameIndexOfBitmap(frameCount++);
}


MoveLeftEffect::MoveLeftEffect(POINT centerPosition, int size) {
	createInfo();
	loadTexture(size);
	this -> centerPosition = { centerPosition.x, centerPosition.y + 10 };
}

void MoveLeftEffect::loadTexture(int size) {
	if (size == 54) {
		texture = EffectTextures::GetMoveLeftTexture54();
	}
	else {
		texture = EffectTextures::GetMoveLeftTexture108();
	}
	texture.SetFrameIndexOfBitmap(0);
}

void MoveLeftEffect::createInfo() {
	info.startDistance = rand() % 15 - 7;
	info.endDistance = info.startDistance + 27;
	info.totalDistance = 27;
	info.frame = textureCount;
}

void MoveLeftEffect::updatePosition() {
	int x = centerPosition.x + (int)(info.totalDistance * frameCount / info.frame) + info.startDistance;
	texture.SetTopLeft(x - texture.GetWidth() / 2, centerPosition.y - texture.GetHeight() / 2);
}

void MoveLeftEffect::updateTexture() {
	texture.SetFrameIndexOfBitmap(frameCount++);
}


MoveRightEffect::MoveRightEffect(POINT centerPosition, int size) {
	createInfo();
	loadTexture(size);
	this -> centerPosition = { centerPosition.x, centerPosition.y + 10 };
}

void MoveRightEffect::loadTexture(int size) {
	if (size == 54) {
		texture = EffectTextures::GetMoveRightTexture54();
	}
	else {
		texture = EffectTextures::GetMoveRightTexture108();
	}
	texture.SetFrameIndexOfBitmap(0);
}

void MoveRightEffect::createInfo() {
	info.startDistance = rand() % 15 - 7;
	info.endDistance = info.startDistance + 27;
	info.totalDistance = 27;
	info.frame = textureCount;
}

void MoveRightEffect::updatePosition() {
	int x = centerPosition.x - (int)(info.totalDistance * frameCount / info.frame) - info.startDistance;
	texture.SetTopLeft(x - texture.GetWidth() / 2, centerPosition.y - texture.GetHeight() / 2);
}

void MoveRightEffect::updateTexture() {
	texture.SetFrameIndexOfBitmap(frameCount++);
}


DeadHintBubbleEffect::DeadHintBubbleEffect(POINT centerPosition, int width) {
	createInfo();
	loadTexture();
	this -> centerPosition = {
		centerPosition.x + (rand() % width) - width / 2,
		centerPosition.y
	} ;
}

void DeadHintBubbleEffect::loadTexture() {
	texture = EffectTextures::GetDeadHintBubbleTexture();
	texture.SetFrameIndexOfBitmap(0);
}

void DeadHintBubbleEffect::createInfo() {
	info.startDistance = rand() % 12 + 7;
	info.endDistance = rand() % 37 + 40;
	info.totalDistance = info.endDistance - info.startDistance;
	info.degree = PI * (rand() % 360) / 180;
	info.frame = (int)(info.totalDistance / 2);
	int frameTime = 1;
	for (int i = 0; i < textureCount - 2; i++) {
		frameTime += rand() % (info.frame - 5 - frameTime);
		info.changeFrameIndex.push_back(frameTime);
	}
	info.changeFrameIndex.push_back(info.frame - (rand() % 5) - 1);
}

void DeadHintBubbleEffect::updatePosition() {
	double currentDistance = (double)info.totalDistance * frameCount / info.frame + info.startDistance;
	int x = (int)(currentDistance * cos(info.degree) + centerPosition.x);
	int y = (int)(currentDistance * sin(info.degree) + centerPosition.y);
	texture.SetTopLeft(x - texture.GetWidth() / 2, y - texture.GetHeight() / 2);
}

void DeadHintBubbleEffect::updateTexture() {
	if (textureChangeCount < textureCount - 1 && info.changeFrameIndex[textureChangeCount] == frameCount) {
		texture.SetFrameIndexOfBitmap(++textureChangeCount);
	}
	frameCount++;
}