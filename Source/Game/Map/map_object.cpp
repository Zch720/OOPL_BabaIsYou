#include "stdafx.h"
#include "map_object.h"
#include "../../Expansion/log.h"
#include "../../Expansion/string_proc.h"

void Mapobject::Show() {
	if (mapobjectId != NONE) {
		texture.ShowBitmap();
	}
}

Mapobject::Mapobject() {

}

Mapobject::Mapobject(MapobjectId mapobjectId, int world) {
	this->mapobjectId = mapobjectId;
}

void Mapobject::LoadTexture(int world, Point textureOrigionPosition) {
	std::string mapobfectPath = "./resources/map/" + intToString(world) + "/" + GetMapobjectNameById(mapobjectId);
	texture.LoadBitmapByString({ mapobfectPath + "_1.bmp", mapobfectPath + "_2.bmp", mapobfectPath + "_3.bmp" }, 0x00FF00);
	Point realPosition = textureOrigionPosition + mapobjectPosition * 54;
	if (mapobjectId == BOX) {
		realPosition.AddOffset(-9, -9);
	}
	texture.SetTopLeft(realPosition.x, realPosition.y);

	texture.SetAnimation(250, false);
}