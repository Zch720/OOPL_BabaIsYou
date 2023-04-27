#pragma once

#include <stack>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "gameobject.h"

class DescriptionProc {
public:
	struct TextObjectInfo {
		GameobjectId id = GAMEOBJECT_NONE;
		Point position;

		bool operator==(const TextObjectInfo &other) const;
		bool operator<(const TextObjectInfo &other);

		size_t operator()(const TextObjectInfo &infoToHash) const;

		static TextObjectInfo FromGameobjectInfo(const GameobjectInfo &gameobjectInfo);
	};

private:
	class DescriptionInfo {
	private:
		static const int MAIN_OBJECT_INDEX = 0;
		static const int SUB_OBJECT_INDEX = 1;
		static const int CENTER_CONNECT_OBJECT_INDEX = 2;
		static const int MAIN_PREFIX_OBJECT_INDEX = 3;
		static const int SUB_PREFIX_OBJECT_INDEX = 4;
		static const int MAIN_CONNECT_OBJECT_INDEX = 5;
		static const int SUB_CONNECT_OBJECT_INDEX = 6;

		std::vector<TextObjectInfo> textObjectInfos;

	public:
		DescriptionInfo();

		void SetMainTextObject(TextObjectInfo info);
		void SetSubTextObject(TextObjectInfo info);
		void SetCenterConnectTextObject(TextObjectInfo info);
		void SetMainPrefixObject(TextObjectInfo info);
		void SetSubPrefixObject(TextObjectInfo info);
		void SetMainConnectObject(TextObjectInfo info);
		void SetSubConnectObject(TextObjectInfo info);

		std::vector<TextObjectInfo> GetAllObjects();
		TextObjectInfo GetMainTextObject();
		TextObjectInfo GetSubTextObject();
		TextObjectInfo GetCenterConnectTextObject();
		TextObjectInfo GetMainPrefixObject();
		TextObjectInfo GetSubPrefixObject();
		TextObjectInfo GetMainConnectObject();
		TextObjectInfo GetSubConnectObject();

		bool IsMainTextObjectUsable();
		bool IsSubTextObjectUsable();
		bool IsCenterConnectTextObjectUsable();
		bool IsMainPrefixObjectUsable();
		bool IsSubPrefixObjectUsable();
		bool IsMainConnectObjectUsable();
		bool IsSubConnectObjectUsable();

		DescriptionInfo operator+(const DescriptionInfo &other);
	};

	typedef std::pair<GameobjectId, GameobjectId> GameobjectIdPair;
	typedef std::unordered_set<TextObjectInfo> TextObjectInfoSet;
	typedef std::vector<DescriptionInfo> DescriptionInfoGroup;

	static std::unordered_multimap<GameobjectId, DescriptionInfo> descriptionsBuffer;
	static std::unordered_multimap<GameobjectId, DescriptionInfo> descriptions;
	static std::stack<std::unordered_multimap<GameobjectId, DescriptionInfo>> descriptionsStack;
	static TextObjectInfoSet connectedTextObjects;

	static TextObjectInfoSet getUsableTextObjects();
	static void clearBuffers();
	static void setUndoBuffers();

	static GameobjectId getPreviousDescriptionConvertNoneGameobject(GameobjectId);
	static int getDescriptionConvertNounGameobjectCount(GameobjectId);

	static TextObjectInfo getNounTextInBlock(Point);
	static TextObjectInfo getPropTextInBlock(Point);
	static void checkOperatorIs();
	static void getAllIsDescription();
	static bool isPreConvertObject(GameobjectId, GameobjectId);
	static bool onlyHasOneConvertObject(GameobjectId);
	static bool checkGameobjectCanConvert(GameobjectId, GameobjectId);
	static bool checkOperatorIsUsable(DescriptionInfo&);
	static void addDescriptionIsToConnectedTextObjects(DescriptionInfoGroup&, TextObjectInfo&, DescriptionInfoGroup&);
	static void getDescriptionIs(DescriptionInfoGroup&, TextObjectInfo&, DescriptionInfoGroup&);
	static void checkOperatorIsHorizontal(TextObjectInfo&);
	static void checkOperatorIsVertical(TextObjectInfo&);

	static bool blockUsable(Point);

	static bool addMainTextObject(DescriptionInfoGroup&, Point);
	static bool addSubTextObject(DescriptionInfoGroup&, Point);
	static bool addAndMainTextObject(DescriptionInfo&, Point);
	static bool addAndSubTextObject(DescriptionInfo&, Point);
	static DescriptionInfoGroup getHorizontalMainObjects(Point);
	static DescriptionInfoGroup getAndHorizontalMainObjects(Point);
	static DescriptionInfoGroup getHorizontalSubObjects(Point);
	static DescriptionInfoGroup getAndHorizontalSubObjects(Point);
	static DescriptionInfoGroup getVerticalMainObjects(Point);
	static DescriptionInfoGroup getAndVerticalMainObjects(Point);
	static DescriptionInfoGroup getVerticalSubObjects(Point);
	static DescriptionInfoGroup getAndVerticalSubObjects(Point);

public:
	static std::vector<GameobjectIdPair> GetDescriptionProps();
	static std::unordered_set<Gameobject*> GetConnectedTextObjects();
	static std::unordered_set<Gameobject*> GetUnusableTextObjects();

	static void Clear();
	static void Undo();
	static void CalculateAllDescription();
};