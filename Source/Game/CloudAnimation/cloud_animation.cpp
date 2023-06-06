#include "stdafx.h"
#include "cloud_animation.h"

game_framework::CMovingBitmap CloudAnimation::cloudCloseDefault = {};
game_framework::CMovingBitmap CloudAnimation::cloudOpenDefault = {};
game_framework::CMovingBitmap CloudAnimation::congratulationShowDefault = {};
game_framework::CMovingBitmap CloudAnimation::congratulationLoopDefault = {};

void CloudAnimation::loadTexture(std::string path, game_framework::CMovingBitmap& bitmap, int frameCount, int ignoreColor) {
	std::vector<std::string> files;
	char filepath[260];

	files.clear();
	for (int i = 0; i < frameCount; i++) {
		sprintf_s(filepath, 260, "%s/%d.bmp", path.c_str(), i);
		files.push_back(filepath);
	}
	bitmap.LoadBitmapByString(files, ignoreColor);
}

void CloudAnimation::Init() {
	loadTexture("./resources/effect/cloud_open_default", cloudOpenDefault, OPEN_FRAME, 0xFFFFFF);
	loadTexture("./resources/effect/cloud_close_default", cloudCloseDefault, CLOSE_FRAME, 0xFFFFFF);
	loadTexture("./resources/effect/congratulation_show_default", congratulationShowDefault, CONGRATULATION_SHOW_FRAME, 0x000000);
	loadTexture("./resources/effect/congratulation_loop_default", congratulationLoopDefault, CONGRATULATION_LOOP_FRAME, 0x000000);
}

void CloudAnimation::StartCloudClose() {
	loadCloseTexture(STYLE_DEFAULT);
	showCloudClose = true;
	showCongratulation = false;
	closeFrameCount = 0;
}

void CloudAnimation::StopCloudClose() {
	showCloudClose = false;
	showCongratulation = false;
}

void CloudAnimation::StartCloudOpen() {
	loadOpenTexture(STYLE_DEFAULT);
	showCloudOpen = true;
	showCongratulation = false;
	openFrameCount = 0;
}

void CloudAnimation::StopCloudOpen() {
	showCloudOpen = false;
}

void CloudAnimation::StartCloudCloseWithCongratulation() {
	loadCloseTexture(STYLE_DEFAULT);
	loadCongratulationShowTexture(STYLE_DEFAULT);
	loadCongratulationLoopTexture(STYLE_DEFAULT);
	showCloudClose = true;
	showCongratulation = true;
	closeFrameCount = 0;
	congratulationShowFrameCount = 0;
	congratulationLoopFrameCount = 0;
}

bool CloudAnimation::IsShowing() {
	return showCloudClose || showCloudOpen;
}

bool CloudAnimation::IsCloudClosing() {
	return showCloudClose;
}

bool CloudAnimation::IsCloudCloseEnd() {
	return showCloudClose && closeFrameCount == CLOSE_FRAME;
}

bool CloudAnimation::IsCloudOpening() {
	return showCloudOpen;
}

bool CloudAnimation::IsCloudOpenEnd() {
	return showCloudOpen && openFrameCount == OPEN_FRAME;
}

void CloudAnimation::Show() {
	if (showCongratulation) {
		if (congratulationShowFrameCount != CONGRATULATION_SHOW_FRAME) {
			congratulationShowAnimation.SetFrameIndexOfBitmap(congratulationShowFrameCount++);
			congratulationShowAnimation.ShowBitmap();
			return;
		}

		congratulationLoopAnimation.SetFrameIndexOfBitmap(congratulationLoopFrameCount++);
		congratulationLoopAnimation.ShowBitmap();
		if (congratulationLoopFrameCount == CONGRATULATION_LOOP_FRAME) {
			congratulationLoopFrameCount = 0;
		}
	}
	if (closeFrameCount != CLOSE_FRAME) {
		cloudCloseAnimation.SetFrameIndexOfBitmap(closeFrameCount++);
		cloudCloseAnimation.ShowBitmap();
		if (closeFrameCount == CLOSE_FRAME) {
			showCongratulation = false;
		}
	} else if (openFrameCount != OPEN_FRAME) {
		cloudOpenAnimation.SetFrameIndexOfBitmap(openFrameCount++);
		cloudOpenAnimation.ShowBitmap();
	}
}

void CloudAnimation::loadCloseTexture(Style style) {
	if (style == STYLE_DEFAULT) {
		cloudCloseAnimation = cloudCloseDefault;
	}
	cloudCloseAnimation.SetFrameIndexOfBitmap(0);
}

void CloudAnimation::loadOpenTexture(Style style) {
	if (style == STYLE_DEFAULT) {
		cloudOpenAnimation = cloudOpenDefault;
	}
	cloudOpenAnimation.SetFrameIndexOfBitmap(0);
}

void CloudAnimation::loadCongratulationShowTexture(Style style) {
	if (style == STYLE_DEFAULT) {
		congratulationShowAnimation = congratulationShowDefault;
	}
	congratulationShowAnimation.SetFrameIndexOfBitmap(0);
}

void CloudAnimation::loadCongratulationLoopTexture(Style style) {
	if (style == STYLE_DEFAULT) {
		congratulationLoopAnimation = congratulationLoopDefault;
	}
	congratulationLoopAnimation.SetFrameIndexOfBitmap(0);
}