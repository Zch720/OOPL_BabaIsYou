#pragma once

#include <unordered_set>
#include <stack>
#include "gameobject.h"
#include "gameobject_properties_manager.h"

class LevelManager {
private:
	struct GameobjectCreateInfo {
		GameobjectId gameobjectId;
		CPoint position;
		Direction textureDirection;
	};

	enum UndoType {
		UNDO_MOVE_UP,
		UNDO_MOVE_DOWN,
		UNDO_MOVE_LEFT,
		UNDO_MOVE_RIGHT,
		UNDO_DELETE,
		UNDO_GEN
	};
	struct UndoInfo {
		UndoType type;
		GameobjectId gameobjectId;
		Direction direction;
		CPoint position;
	};

	const int TEXTURE_ANIMATION_WAIT_TIME = 5;

	// game board status
	std::vector<std::vector<std::vector<Gameobject*>>> gameBoard;
	int gameBoardWidth = 0;
	int gameBoardHeight = 0;

	// game status
	bool touchWinObject = false;

	// texture status
	unordered_set<Gameobject*> connectedTextObject;
	CPoint textureOrigionPosition = CPoint(0, 0);
	int textureSize = 0;
	int textureAnimationCount = 0;
	int nextTextureWaitTime = 0;

	// properties status
	GameobjectPropsManager propsManager;
	std::vector<std::pair<GameobjectId, GameobjectId>> descriptionProps;

	// move status
	std::vector<std::vector<int8_t>> blockMoveableRecord;
	std::unordered_set<Gameobject*> moveableGameobjects;

	// undo status
	std::stack<std::vector<UndoInfo>> undoRecord;
	std::vector<UndoInfo> undoBuffer;

	
	// basic actions
	void clearLevel();
	int getWorld(int);
	void createGameboard(std::vector<GameobjectCreateInfo>);
	void createBlockMoveableRecord();
	void resetBlockMoveableRecord();

	// game board process
	bool checkHasGameobjectInBlock(CPoint, GameobjectId);
	int getGameobjectConnectStatus(Gameobject*);
	Gameobject* findGameobjectInBlockById(CPoint, GameobjectId);
	Gameobject* findGameobjectInBlockByProp(CPoint, PropId);
	std::unordered_set<Gameobject*> findAllYouGameobject();
	Gameobject* genGameobject(CPoint, GameobjectId, bool addToBuffer = true);
	void deleteGameobject(Gameobject*, bool addToBuffer= true);
	void addGameobject(CPoint, Gameobject*);
	void removeGameobject(Gameobject*);
	void replaceGameobject(GameobjectId, GameobjectId);
	void updateGameobjectTextureColor();

	// check block moveable;
	bool checkMoveableObjects(CPoint, bool);
	bool checkMoveUp(CPoint);
	bool checkMoveDown(CPoint);
	bool checkMoveLeft(CPoint);
	bool checkMoveRight(CPoint);

	// prop process
	bool checkHasPropInBlock(CPoint, PropId);
	bool checkPropOverlap(PropId, PropId);
	bool checkBlockPropOverlap(CPoint, PropId, PropId);
	void checkAllOverlapProp();
	void checkOverlapPropFull_You_Win();
	void checkOverlapPropBlock_Sink(CPoint);
	void deleteOverlapPropBoth(CPoint, PropId, PropId);
	void deleteOverlapPropSecond(CPoint, PropId, PropId);
	void loadTextObjectsPushProp(std::unordered_set<GameobjectId>);
	void updateProps();
	void updatePropsManager();

	// description process
	Gameobject* getNounTextObjectInBlock(CPoint);
	Gameobject* getPropTextObjectInBlock(CPoint);
	void getAllDescriptions();
	void checkDescription_is(Gameobject*);

public:
	LevelManager();
	~LevelManager();

	void LoadLevel(int level);

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void Undo();

	bool IsMoving();
	bool IsWin();

	void Show();
};