#pragma once

#include "../../Library/gameutil.h"
#include <functional>

typedef std::function<void()> ButtonOnClickFunc;

class Button {
private:

	game_framework::CMovingBitmap texture;
	CPoint buttonCenterPosition;
	bool isLoaded = false;
	std::string buttonText;

	ButtonOnClickFunc onClickFunc = nullptr;

	bool isActivity = false;
	bool isHover = false;
	bool isClicked = false;
	int clickedTextureShowCount = 0;

	bool checkMouseOverlap(CPoint);
	void updateButtonStatus();

public:
	Button();
	
	/*
		設定按鈕是否使用
		activity: 按鈕活動狀態
	*/
	void SetActivity(bool activity);
	
	/*
		設定按鈕中心位置
		centerPosition: 按鈕中心位置
	*/
	void SetButtonCenterPosition(CPoint centerPosition);

	/*
		設定按鈕圖片
		centerPosition: 按鈕中心位置
		texture: 按鈕圖片
	*/
	void SetButtonTexture(game_framework::CMovingBitmap texture);

	/*
		設定按鈕圖片
		centerPosition: 按鈕中心位置
		texturePaths: 按鈕圖片，陣列長度應為三，由 index 0 ~ 2 依序放入，預設圖片、滑鼠停留圖片、及按下圖片
	*/
	void SetButtonTexture(CPoint centerPosition, std::vector<std::string> texturePaths);

	/*
		設定按鈕圖片
		centerPosition: 按鈕中心位置
		defaultTexturePath: 預設圖片
		hoverTexturePath: 滑鼠停留圖片
		clickedTexturePath: 按下圖片
	*/
	void SetButtonTexture(CPoint centerPosition, std::string defaultTexturePath, std::string hoverTexturePath, std::string clickedTexturePath);

	void SetButtonText(std::string text);
	
	/*
		設定按下後動作
		func: 按下動作函式的函式指標
	*/
	void SetOnClickFunc(ButtonOnClickFunc func);

	/*
		複製按鈕圖片
		button: 要複製的按鈕
	*/
	void CopyButtonTexture(Button &button);

	/*
		檢查滑鼠是否按下按鈕
		position: 滑鼠位置
	*/
	void CheckMouseClick(CPoint position);
	/*
		檢查滑鼠是否在按鈕上
		position: 滑鼠位置
	*/
	void CheckMouseMove(CPoint position);

	/*
		按下按鈕
	*/
	void Click();

	/*
		顯示按鈕圖片
	*/
	void ShowImage();

	/*
		顯示按鈕文字
	*/
	void ShowText(CDC *pDC);
};