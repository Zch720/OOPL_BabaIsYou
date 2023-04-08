#pragma once

#include <stack>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "gameobject.h"

class DescriptionProc {
public:
	struct TextObjectInfo {
		GameobjectId id;
		Point position;

		bool operator==(const TextObjectInfo &other) const;
		bool operator<(const TextObjectInfo &other);

		size_t operator()(const TextObjectInfo &infoToHash) const;
	};

private:
	typedef std::pair<GameobjectId, GameobjectId> GameobjectIdPair;
	typedef std::unordered_set<TextObjectInfo> TextObjectInfoSet;

	static std::unordered_multimap<GameobjectId, std::vector<TextObjectInfo>> descriptionProps;
	static std::stack<std::unordered_multimap<GameobjectId, std::vector<TextObjectInfo>>> descriptionStack;
	static TextObjectInfoSet connectedTextObjects;
	static std::stack<TextObjectInfoSet> connectedTextObjectsStack;
	static TextObjectInfoSet cannotUseTextObjects;
	static std::stack<TextObjectInfoSet> cannotUseTextObjectsStack;

	static GameobjectId getPreviousDescriptionConvertNoneGameobject(GameobjectId);
	static int getDescriptionConvertNounGameobjectCount(GameobjectId);

	static Gameobject* getNounTextInBlock(Point);
	static Gameobject* getPropTextInBlock(Point);
	static void checkOperatorIs();
	static void checkOperatorIsHorizontal(Gameobject *gameobject);
	static void checkOperatorIsVertical(Gameobject *gameobject);
	static std::unordered_map<Gameobject*, bool> checkMainObjectHorizontal(Point position);
	static std::unordered_map<Gameobject*, bool> checkSubObjectHorizontal(Point position);
	static std::unordered_map<Gameobject*, bool> checkMainObjectVertical(Point position);
	static std::unordered_map<Gameobject*, bool> checkSubObjectVertical(Point position);

public:
	static std::vector<GameobjectIdPair> GetDescriptionProps();
	static std::unordered_set<Gameobject*> GetConnectedTextObjects();

	static void Clear();
	static void Undo();
	static void GetAllDescription();
	static void UpdatePropFromDescription();
};