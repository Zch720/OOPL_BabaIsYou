#include "stdafx.h"
#include "map.h"

CMovingBitmap Map::world0Backgroung = CMovingBitmap();

void Map::LoadWorld() {

}

void Map::Show() {
	world0Backgroung.ShowBitmap();
}