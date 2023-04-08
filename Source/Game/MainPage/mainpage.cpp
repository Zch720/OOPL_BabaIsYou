#include "stdafx.h"
#include "mainpage.h"

CMovingBitmap MainPage::standbyBackgroung = CMovingBitmap();
CMovingBitmap MainPage::startScreenTitle = CMovingBitmap();
CMovingBitmap MainPage::startScreenLine = CMovingBitmap();
CMovingBitmap MainPage::chooser = CMovingBitmap();
Button MainPage::continuePlaying = Button();
Button MainPage::startTheGame = Button();
Button MainPage::playLevel = Button();
Button MainPage::levelEditor = Button();
Button MainPage::settings = Button();
Button MainPage::credits = Button();
Button MainPage::exitTheGame = Button();
POINT MainPage::chooserLocation[8] = { {575, 484}, {220, 610}, {220, 710}, {220, 810}, {575, 484},  {940, 610}, {940, 710}, {940, 810} };
CPoint MainPage::chooserPoint = CPoint();
bool MainPage::screenSwitch = false;

void MainPage::StandbyScreenInit() {
	standbyBackgroung.LoadBitmapByString({ 
		"Resources/mainpage/standbyscreen/start_1.bmp",
		"Resources/mainpage/standbyscreen/start_2.bmp",
		"Resources/mainpage/standbyscreen/start_3.bmp",
		"Resources/mainpage/standbyscreen/start_4.bmp",
		"Resources/mainpage/standbyscreen/start_5.bmp",
		"Resources/mainpage/standbyscreen/start_6.bmp",
		"Resources/mainpage/standbyscreen/start_7.bmp",
		});
	standbyBackgroung.SetTopLeft(0, 0);
	standbyBackgroung.SetAnimation(250, false);
}

void MainPage::StartScreenInit() {
	startScreenTitle.LoadBitmapByString({"Resources/mainpage/startscreen/title1.bmp","Resources/mainpage/startscreen/title2.bmp","Resources/mainpage/startscreen/title3.bmp",});
	startScreenTitle.SetTopLeft(531, 150);
	startScreenTitle.SetAnimation(250, false);

	startScreenLine.LoadBitmapByString({"Resources/mainpage/startscreen/line1.bmp",	"Resources/mainpage/startscreen/line2.bmp", "Resources/mainpage/startscreen/line3.bmp"});
	startScreenLine.SetTopLeft(508, 425);
	startScreenLine.SetAnimation(250, false);

	continuePlaying.SetButtonTexture(CPoint(960, 525) , {"Resources/mainpage/startscreen/button1.bmp", "Resources/mainpage/startscreen/button2.bmp" , "Resources/mainpage/startscreen/button3.bmp" });
	continuePlaying.SetButtonText("CONTINUE PLAYING");
	startTheGame.SetButtonTexture(CPoint(600, 650), { "Resources/mainpage/startscreen/button1.bmp", "Resources/mainpage/startscreen/button2.bmp" , "Resources/mainpage/startscreen/button3.bmp" });
	startTheGame.SetButtonText("START THE GAME");
	playLevel.SetButtonTexture(CPoint(1320, 650), { "Resources/mainpage/startscreen/button1.bmp", "Resources/mainpage/startscreen/button2.bmp" , "Resources/mainpage/startscreen/button3.bmp" });
	playLevel.SetButtonText("PLAY LEVELS");
	levelEditor.SetButtonTexture(CPoint(600, 750), { "Resources/mainpage/startscreen/button1.bmp", "Resources/mainpage/startscreen/button2.bmp" , "Resources/mainpage/startscreen/button3.bmp" });
	levelEditor.SetButtonText("LEVEL EDITOR");
	settings.SetButtonTexture(CPoint(1320, 750), { "Resources/mainpage/startscreen/button1.bmp", "Resources/mainpage/startscreen/button2.bmp" , "Resources/mainpage/startscreen/button3.bmp" });
	settings.SetButtonText("SETTINGS");
	credits.SetButtonTexture(CPoint(600, 850), { "Resources/mainpage/startscreen/button1.bmp", "Resources/mainpage/startscreen/button2.bmp" , "Resources/mainpage/startscreen/button3.bmp" });
	credits.SetButtonText("CREDITS");
	exitTheGame.SetButtonTexture(CPoint(1320, 850), { "Resources/mainpage/startscreen/button1.bmp", "Resources/mainpage/startscreen/button2.bmp" , "Resources/mainpage/startscreen/button3.bmp" });
	exitTheGame.SetButtonText("EXIT THE GAME");

	chooser.LoadBitmapByString({ "Resources/mainpage/startscreen/chooser1.bmp", "Resources/mainpage/startscreen/chooser2.bmp" , "Resources/mainpage/startscreen/chooser3.bmp" }, 0x00FF00);
	chooser.SetTopLeft(575, 484);
	chooser.SetAnimation(250, false);
}

void MainPage::ChooserMove(int direction) {
	if (direction == 0) {
		chooserPoint.y -= 1;
		chooserPoint.y &= 3;
	}
	if (direction == 1) {
		chooserPoint.y += 1;
		chooserPoint.y &= 3;
	}
	if (direction == 2) {
		chooserPoint.x -= 1;
		chooserPoint.x &= 1;
	}
	if (direction == 3) {
		chooserPoint.x += 1;
		chooserPoint.x &= 1;
	}
	POINT whichButton = chooserLocation[4 * chooserPoint.x + chooserPoint.y];
	chooser.SetTopLeft(whichButton.x, whichButton.y);
}

void MainPage::ChooserEnter() {
	if (!screenSwitch) return;
	if (chooserPoint.y == 0) {
		continuePlaying.Click();
	}
	else if (chooserPoint.x == 0 && chooserPoint.y == 1) {
		startTheGame.Click();
	}
	else if (chooserPoint.x == 1 && chooserPoint.y == 3) {
		exitTheGame.Click();
	}
}

void MainPage::CheckMouseMove(CPoint point) {
	continuePlaying.CheckMouseMove(point);
	startTheGame.CheckMouseMove(point);
	playLevel.CheckMouseMove(point);
	levelEditor.CheckMouseMove(point);
	settings.CheckMouseMove(point);
	credits.CheckMouseMove(point);
	exitTheGame.CheckMouseMove(point);
}

void MainPage::CheckMouseClick(CPoint point) {
	continuePlaying.CheckMouseClick(point);
	startTheGame.CheckMouseClick(point);
	playLevel.CheckMouseClick(point);
	levelEditor.CheckMouseClick(point);
	settings.CheckMouseClick(point);
	credits.CheckMouseClick(point);
	exitTheGame.CheckMouseClick(point);
}

void MainPage::SetContieuePlayingFunc(ButtonOnClickFunc func) {
	continuePlaying.SetOnClickFunc(func);
}

void MainPage::SetStartTheGameFunc(ButtonOnClickFunc func) {
	startTheGame.SetOnClickFunc(func);
}

void MainPage::SetExitTheGameFunc(ButtonOnClickFunc func) {
	exitTheGame.SetOnClickFunc(func);
}

void MainPage::SwitchCheck() {
	screenSwitch = true;
	continuePlaying.SetActivity(true);
	startTheGame.SetActivity(true);
	playLevel.SetActivity(true);
	levelEditor.SetActivity(true);
	settings.SetActivity(true);
	credits.SetActivity(true);
	exitTheGame.SetActivity(true);
}

void MainPage::ShowImage() {
	if (!screenSwitch) {
		standbyBackgroung.ShowBitmap();
	}
	else {
		startScreenTitle.ShowBitmap();
		startScreenLine.ShowBitmap();
		chooser.ShowBitmap();
		continuePlaying.ShowImage();
		startTheGame.ShowImage();
		playLevel.ShowImage();
		levelEditor.ShowImage();
		settings.ShowImage();
		credits.ShowImage();
		exitTheGame.ShowImage();
	}

}

void MainPage::ShowText(CDC *pDC) {
	if (screenSwitch == true) {
		continuePlaying.ShowText(pDC);
		startTheGame.ShowText(pDC);
		playLevel.ShowText(pDC);
		levelEditor.ShowText(pDC);
		settings.ShowText(pDC);
		credits.ShowText(pDC);
		exitTheGame.ShowText(pDC);
	}
}