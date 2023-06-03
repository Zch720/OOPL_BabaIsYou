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

void EffectTextures::Init() {
	char filepath[260];
	std::vector<std::string> paths;

	paths.clear();
	for (int i = 1; i < 6; i++) {
		sprintf_s(filepath, 260, "./resources/effect/win_object/54/%d.bmp", i);
		paths.push_back(filepath);
	}
	winObjectEffectTexture54.LoadBitmapByString(paths, 0x000000);

	paths.clear();
	for (int i = 1; i < 6; i++) {
		sprintf_s(filepath, 260, "./resources/effect/win_object/108/%d.bmp", i);
		paths.push_back(filepath);
	}
	winObjectEffectTexture108.LoadBitmapByString(paths, 0x000000);

	paths.clear();
	for (int i = 0; i < 19; i++) {
		sprintf_s(filepath, 260, "./resources/effect/dispear/54/%d.bmp", i);
		paths.push_back(filepath);
	}
	dispearTexture54.LoadBitmapByString(paths, 0x000000);
	
	paths.clear();
	for (int i = 0; i < 19; i++) {
		sprintf_s(filepath, 260, "./resources/effect/dispear/108/%d.bmp", i);
		paths.push_back(filepath);
	}
	dispearTexture108.LoadBitmapByString(paths, 0x000000);
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