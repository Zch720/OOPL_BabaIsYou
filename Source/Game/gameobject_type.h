#pragma once

enum GameobjectType {
	OBJECT_TYPE_CHARACTER,
	OBJECT_TYPE_STATIC,
	OBJECT_TYPE_TILED,
	OBJECT_TYPE_TEXT
};

int GetGameobjectTypeById(int gameobjectId);