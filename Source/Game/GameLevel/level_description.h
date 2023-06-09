#pragma once

#include <vector>
#include <unordered_set>
#include "objects.h"

class LevelDescription {
private:
    class Description {
    private:
        struct ObjectInfos {
            int size = 0;
            ObjectInfo infos[40];
        };

        ObjectInfos mainPrefix;
        ObjectInfo mainObject;
        ObjectInfo mainConnect;
        ObjectInfo centerOperator;
        ObjectInfo subConnect;
        ObjectInfos subPrefix;
        ObjectInfo subObject;

        bool isObjectExist(ObjectInfo objectInfo);
        void plusObjectInfo(ObjectInfo info, ObjectInfo other, ObjectInfo &result);
        void plusObjectInfos(ObjectInfos infos, ObjectInfos other, ObjectInfos &result);

    public:
        void AddMainPrefix(ObjectInfo objectInfo);
        void SetMainObject(ObjectInfo objectInfo);
        void SetMainConnect(ObjectInfo objectInfo);
        void SetCenterOperator(ObjectInfo objectInfo);
        void SetSubConnect(ObjectInfo objectInfo);
        void AddSubPrefix(ObjectInfo objectInfo);
        void SetSubObject(ObjectInfo objectInfo);

        ObjectInfo GetMainPrefix(int index);
        ObjectInfo GetMainObject();
        ObjectInfo GetMainConnect();
        ObjectInfo GetCenterOperator();
        ObjectInfo GetSubConnect();
        ObjectInfo GetSubPrefix(int index);
        ObjectInfo GetSubObject();
        int GetMainPrefixCount();
        int GetSubPrefixCount();

        std::vector<ObjectInfo> GetAllExistObject();

        bool operator==(const Description &other);
        bool operator!=(const Description &other);
        Description operator+(const Description &other);
        Description& operator+=(const Description &other);
    };

    static std::vector<Description> previousDescriptions;
    static std::vector<Description> descriptions;
    static std::unordered_set<ObjectInfo> connectedTextobjetcs;
    static std::unordered_set<ObjectInfo> usableTextobjetcs;

    static void findDescription_Is();
    static void checkDescriptionHorizontal_Is(ObjectInfo isObject);
    static void checkDescriptionVertical_Is(ObjectInfo isObject);

    static void findDescription_Has();
    static void checkDescriptionHorizontal_Has(ObjectInfo hasObject);
    static void checkDescriptionVertical_Has(ObjectInfo hasObject);

    static std::vector<Description> getMainObjectHorizontal(Point position);
    static std::vector<Description> getSubObjectHorizontal(Point position);
    static std::vector<Description> getSubObjectHorizontalHasProperty(Point position);
    static std::vector<Description> getMainObjectVertical(Point position);
    static std::vector<Description> getSubObjectVertical(Point position);
    static std::vector<Description> getSubObjectVerticalHasProperty(Point position);
    static std::vector<Description> getMainConnectHorizontal(Point position);
    static std::vector<Description> getSubConnectHorizontal(Point position);
    static std::vector<Description> getSubConnectHorizontalHasProperty(Point position);
    static std::vector<Description> getMainConnectVertical(Point position);
    static std::vector<Description> getSubConnectVertical(Point position);
    static std::vector<Description> getSubConnectVerticalHasProperty(Point position);

    static void checkGameobjectDescriptionUsable(Description &description);
    static void checkPropertyDescriptionUsable(Description &description);
    static void checkHasDescriptionUsable(Description &description);

public:
    static void Clear();
    static void CalculateTextInfo();
    static void CalculateAllDescription();
    static void CalculateConnectedTextobject();
    static void CalculateUsableTextobject();

    static bool HasNewDescription();

    static bool IsConnectedTextobject(ObjectInfo objectInfo);
    static bool IsUsableTextobject(ObjectInfo objectInfo);

    static std::vector<std::pair<ObjectId, ObjectId>> GetDescriptionsIs();
    static std::vector<std::pair<ObjectId, ObjectId>> GetDescriptionsHas();
};