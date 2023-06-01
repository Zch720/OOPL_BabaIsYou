#include "stdafx.h"
#include "button.h"
#include "../../Expansion/log.h"
#include "../../Expansion/center_text.h"

#define DEFAULT_TEXTURE_INDEX	0
#define HOVER_TEXTURE_INDEX		1
#define CLICKED_TEXTURE_INDEX	2

#define CLICKED_COUNT_MAX		5

Button::Button() {}

void Button::SetActivity(bool activity) {
	isActivity = activity;
}

void Button::SetButtonTexture(CPoint centerPosition, std::vector<std::string> texturePaths) {
	texture.LoadBitmapByString(texturePaths, 0x00FF00);
	texture.SetFrameIndexOfBitmap(DEFAULT_TEXTURE_INDEX);

	buttonCenterPosition = centerPosition;

	isLoaded = true;
}
void Button::SetButtonTexture(CPoint centerPosition, std::string defaultTexturePath, std::string hoverTexturePath, std::string clickedTexturePath) {
	texture.LoadBitmapByString({ defaultTexturePath, hoverTexturePath, clickedTexturePath }, 0x00FF00);
	texture.SetFrameIndexOfBitmap(DEFAULT_TEXTURE_INDEX);

	buttonCenterPosition = centerPosition;

	isLoaded = true;
}

void Button::SetButtonText(std::string text) {
	buttonText = text;
}

void Button::SetOnClickFunc(ButtonOnClickFunc func) {
	onClickFunc = func;
}

void Button::CheckMouseClick(CPoint position) {
	if (!isActivity) return;
	if (!isLoaded) return;

	if (isClicked = checkMouseOverlap(position)) {
		texture.SetFrameIndexOfBitmap(CLICKED_TEXTURE_INDEX);
		clickedTextureShowCount = CLICKED_COUNT_MAX;
	}
}
void Button::CheckMouseMove(CPoint position) {
	if (!isActivity) return;
	if (!isLoaded) return;
	if (isClicked) return;

	if (isHover = checkMouseOverlap(position)) {
		texture.SetFrameIndexOfBitmap(HOVER_TEXTURE_INDEX);
	}
	else {
		texture.SetFrameIndexOfBitmap(DEFAULT_TEXTURE_INDEX);
	}
}

void Button::Click() {
	if (onClickFunc) {
		onClickFunc();
	}
}

void Button::ShowImage() {
	texture.SetTopLeft(
		buttonCenterPosition.x - texture.GetWidth() / 2,
		buttonCenterPosition.y - texture.GetHeight() / 2
	);
	texture.ShowBitmap();
	updateButtonStatus();
}


bool Button::checkMouseOverlap(CPoint position) {
	return (
		texture.GetLeft() <= position.x && position.x <= texture.GetLeft() + texture.GetWidth()
		&& texture.GetTop() <= position.y && position.y <= texture.GetTop() + texture.GetHeight()
	);
}
void Button::updateButtonStatus() {
	if (isClicked && clickedTextureShowCount-- == 0) {
		isClicked = false;
		texture.SetFrameIndexOfBitmap(HOVER_TEXTURE_INDEX);

		if (onClickFunc) {
			onClickFunc();
		}
	}
}

void Button::ShowText(CDC *pDC) {
	CenterTextDraw::Print(pDC, buttonCenterPosition.x, buttonCenterPosition.y, buttonText);
}