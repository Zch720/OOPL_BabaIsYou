#include "stdafx.h"
#include <stdlib.h>
#include <cmath>
#include "effect_object.h"

#define PI acos(-1)

game_framework::CMovingBitmap EffectTextures::winObjectEffectTexture54 = {};
game_framework::CMovingBitmap EffectTextures::winObjectEffectTexture108 = {};

void EffectTextures::Init() {
	winObjectEffectTexture54.LoadBitmapByString(
		{
			"./resources/effect/win_object/54/1.bmp",
			"./resources/effect/win_object/54/2.bmp",
			"./resources/effect/win_object/54/3.bmp",
			"./resources/effect/win_object/54/4.bmp",
			"./resources/effect/win_object/54/5.bmp",
		},
		0x000000
	);
	winObjectEffectTexture108.LoadBitmapByString(
		{
			"./resources/effect/win_object/108/1.bmp",
			"./resources/effect/win_object/108/2.bmp",
			"./resources/effect/win_object/108/3.bmp",
			"./resources/effect/win_object/108/4.bmp",
			"./resources/effect/win_object/108/5.bmp",
		},
		0x000000
	);
}

game_framework::CMovingBitmap EffectTextures::GetWinObjectEffectTexture54() {
	return winObjectEffectTexture54;
}

game_framework::CMovingBitmap EffectTextures::GetWinObjectEffectTexture108() {
	return winObjectEffectTexture108;
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