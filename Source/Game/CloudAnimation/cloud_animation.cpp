#include "stdafx.h"
#include "cloud_animation.h"

game_framework::CMovingBitmap CloudAnimation::cloudCloseNone = {};
game_framework::CMovingBitmap CloudAnimation::cloudOpenNone = {};

void CloudAnimation::Init() {
	std::vector<std::string> files;
	char filepath[260];

	files.clear();
	for (int i = 0; i < OPEN_FRAME; i++) {
		sprintf_s(filepath, 260, "./resources/effect/cloud_open_none/%d.bmp", i);
		files.push_back(filepath);
	}
	cloudOpenNone.LoadBitmapByString(files, 0xFFFFFF);
	
	files.clear();
	for (int i = 0; i < CLOSE_FRAME; i++) {
		sprintf_s(filepath, 260, "./resources/effect/cloud_close_none/%d.bmp", i);
		files.push_back(filepath);
	}
	cloudCloseNone.LoadBitmapByString(files, 0xFFFFFF);
}

void CloudAnimation::StartCloud(Style style) {
	loadCloseTexture(style);
	loadOpenTexture(style);
	closeFrameCount = 0;
}

bool CloudAnimation::IsShowing() {
	return IsCloudClosing() || IsCloudOpening();
}

bool CloudAnimation::IsCloudClosing() {
	return closeFrameCount != CLOSE_FRAME;
}

bool CloudAnimation::IsCloudOpening() {
	return openFrameCount != OPEN_FRAME;
}

bool CloudAnimation::IsSwitch() {
	return openFrameCount == 0;
}

void CloudAnimation::Show() {
	if (closeFrameCount != CLOSE_FRAME) {
		cloudCloseAnimation.SetFrameIndexOfBitmap(closeFrameCount++);
		cloudCloseAnimation.ShowBitmap();
		if (closeFrameCount == CLOSE_FRAME) {
			openFrameCount = 0;
		}
	} else if (openFrameCount != OPEN_FRAME) {
		cloudOpenAnimation.SetFrameIndexOfBitmap(openFrameCount++);
		cloudOpenAnimation.ShowBitmap();
	}
}

void CloudAnimation::loadCloseTexture(Style style) {
	if (style == STYLE_NONE) {
		cloudCloseAnimation = cloudCloseNone;
	}
	cloudCloseAnimation.SetFrameIndexOfBitmap(0);
}

void CloudAnimation::loadOpenTexture(Style style) {
	if (style == STYLE_NONE) {
		cloudOpenAnimation = cloudOpenNone;
	}
	cloudOpenAnimation.SetFrameIndexOfBitmap(0);
}