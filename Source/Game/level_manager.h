#pragma once

#include <unordered_set>
#include <stack>
#include "gameobject.h"
#include "gameobject_properties_manager.h"

class LevelManager {
private:
	struct GameobjectInfo {
		GameobjectId gameobjectId;
		CPoint position;
	};

	enum UndoType {
		UNDO_UP,
		UNDO_DOWN,
		UNDO_RIGHT,
		UNDO_LEFT,
		UNDO_ADD,
		UNDO_DELETE
	};
	struct UndoInfo {
		GameobjectId gameobjectId;
		CPoint position;
		UndoType undoType;
	};

	GameobjectPropsManager propsManager;
	std::vector<std::vector<std::vector<Gameobject*>>> gameBoard;

	int gameBoardWidth = 0;
	int gameBoardHeight = 1;
	CPoint textureOriginPosition = CPoint(0, 0);
	int textureSize;
	int textureCount = 0;
	int textureWait = 0;

	bool reachWinObj;

	std::vector<std::pair<GameobjectId, PropId>> defaultProps;
	std::vector<std::pair<GameobjectId, GameobjectId>> additionProps;

	std::vector<std::vector<int>> moveableRecord;
	std::unordered_set<Gameobject*> hasYouPropObjects;
	std::unordered_set<Gameobject*> waitToMoveObjects;

	std::vector<UndoInfo> undoBuffer;
	std::stack<std::vector<UndoInfo>> undoStack;

	void clearLevel();
	void createGameBoard(std::vector<GameobjectInfo>);
	void createMoveableRecord();
	void resetMoveableRecord();
	void setPropsManager();

	Gameobject* getGemeobjectInBlockById(CPoint, GameobjectId);
	void removeGameobject(CPoint, Gameobject*);
	void addGameobject(CPoint, Gameobject*);
	void genGameobject(CPoint, GameobjectId);

	bool checkObjectsInBlockHasProp(CPoint, PropId);
	bool checkObjectsInBlockHasId(CPoint, GameobjectId);
	int checkObjectConnect(CPoint, GameobjectId);

	void findAllYouObjects();
	bool checkBlockMoveObjects(CPoint, bool);
	bool checkMoveUp(CPoint);
	bool checkMoveDown(CPoint);
	bool checkMoveLeft(CPoint);
	bool checkMoveRight(CPoint);

	void checkAllOverlapProp();
	void checkOverlap_YouWin();
	bool checkPropOverlap(PropId, PropId);
	bool checkPropInSameBlock(CPoint, PropId, PropId);
	
	Gameobject* getNounTextObject(CPoint);
	Gameobject* getPropTextObject(CPoint);
	void getAllDescriptions();
	void checkDescription_is(CPoint);
	void replaceGameobject(GameobjectId, GameobjectId);
	void updateProps();

public:
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