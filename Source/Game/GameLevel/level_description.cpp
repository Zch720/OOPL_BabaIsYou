#include "stdafx.h"
#include "textobject_id.h"
#include "property_manager.h"
#include "level_data.h"
#include "level_description.h"
#include "../../Expansion/log.h"

void LevelDescription::Description::AddMainPrefix(ObjectInfo objectInfo) {
    mainPrefix.infos[mainPrefix.size++] = objectInfo;
}
void LevelDescription::Description::SetMainObject(ObjectInfo objectInfo) {
    mainObject = objectInfo;
}
void LevelDescription::Description::SetMainConnect(ObjectInfo objectInfo) {
    mainConnect = objectInfo;
}
void LevelDescription::Description::SetCenterOperator(ObjectInfo objectInfo) {
    centerOperator = objectInfo;
}
void LevelDescription::Description::SetSubConnect(ObjectInfo objectInfo) {
    subConnect = objectInfo;
}
void LevelDescription::Description::AddSubPrefix(ObjectInfo objectInfo) {
    subPrefix.infos[subPrefix.size++] = objectInfo;
}
void LevelDescription::Description::SetSubObject(ObjectInfo objectInfo) {
    subObject = objectInfo;
}

ObjectInfo LevelDescription::Description::GetMainPrefix(int index) {
    return mainPrefix.infos[index];
}
ObjectInfo LevelDescription::Description::GetMainObject() {
    return mainObject;
}
ObjectInfo LevelDescription::Description::GetMainConnect() {
    return mainConnect;
}
ObjectInfo LevelDescription::Description::GetCenterOperator() {
    return centerOperator;
}
ObjectInfo LevelDescription::Description::GetSubConnect() {
    return subConnect;
}
ObjectInfo LevelDescription::Description::GetSubPrefix(int index) {
    return subPrefix.infos[index];
}
ObjectInfo LevelDescription::Description::GetSubObject() {
    return subObject;
}
int LevelDescription::Description::GetMainPrefixCount() {
    return mainPrefix.size;
}
int LevelDescription::Description::GetSubPrefixCount() {
    return subPrefix.size;
}

std::vector<ObjectInfo> LevelDescription::Description::GetAllExistObject() {
    std::vector<ObjectInfo> result;
    for (int i = 0; i < mainPrefix.size; i++) result.push_back(mainPrefix.infos[i]);
    if (isObjectExist(mainObject)) result.push_back(mainObject);
    if (isObjectExist(mainConnect)) result.push_back(mainConnect);
    if (isObjectExist(centerOperator)) result.push_back(centerOperator);
    if (isObjectExist(subConnect)) result.push_back(subConnect);
    for (int i = 0; i < subPrefix.size; i++) result.push_back(subPrefix.infos[i]);
    if (isObjectExist(subObject)) result.push_back(subObject);
    return result;
}

bool LevelDescription::Description::operator==(const Description &other) {
    if (mainPrefix.size != other.mainPrefix.size) return false;
    if (subPrefix.size != other.subPrefix.size) return false;

    for (int i = 0; i < mainPrefix.size; i++) {
        if (mainPrefix.infos[i].genId!= other.mainPrefix.infos[i].genId) return false;
    }
    if (mainObject.genId != other.mainObject.genId) return false;
    if (mainConnect.genId != other.mainConnect.genId) return false;
    if (centerOperator.genId != other.centerOperator.genId) return false;
    if (subConnect.genId != other.subConnect.genId) return false;
    for (int i = 0; i < subPrefix.size; i++) {
        if (subPrefix.infos[i].genId != other.subPrefix.infos[i].genId) return false;
    }
    if (subObject.genId != other.subObject.genId) return false;

    return true;
}

bool LevelDescription::Description::operator!=(const Description &other) {
    return !(*this == other);
}

LevelDescription::Description LevelDescription::Description::operator+(const Description &other) {
    Description result;
    plusObjectInfos(mainPrefix, other.mainPrefix, result.mainPrefix);
    plusObjectInfo(mainObject, other.mainObject, result.mainObject);
    plusObjectInfo(mainConnect, other.mainConnect, result.mainConnect);
    plusObjectInfo(centerOperator, other.centerOperator, result.centerOperator);
    plusObjectInfo(subConnect, other.subConnect, result.subConnect);
    plusObjectInfos(subPrefix, other.subPrefix, result.subPrefix);
    plusObjectInfo(subObject, other.subObject, result.subObject);
    return result;
}

LevelDescription::Description& LevelDescription::Description::operator+=(const Description &other) {
    return *this = *this + other;
}

bool LevelDescription::Description::isObjectExist(ObjectInfo objectInfo) {
    return objectInfo.objectId != OBJECT_NONE;
}

void LevelDescription::Description::plusObjectInfo(ObjectInfo info, ObjectInfo other, ObjectInfo &result) {
    if (isObjectExist(info)) result = info;
    if (isObjectExist(other)) result = other;
}

void LevelDescription::Description::plusObjectInfos(ObjectInfos infos, ObjectInfos other, ObjectInfos &result) {
    if (infos.size) {
        result.size = infos.size;
        memcpy(result.infos, infos.infos, sizeof(ObjectInfo) * infos.size);
    } else {
        result.size = other.size;
        memcpy(result.infos, other.infos, sizeof(ObjectInfo) * other.size);
    }
}


std::vector<LevelDescription::Description> LevelDescription::previousDescriptions = {};
std::vector<LevelDescription::Description> LevelDescription::descriptions = {};
std::unordered_set<ObjectInfo> LevelDescription::connectedTextobjetcs = {};
std::unordered_set<ObjectInfo> LevelDescription::usableTextobjetcs = {};

void LevelDescription::Clear() {
    descriptions.clear();
    connectedTextobjetcs.clear();
}

void LevelDescription::CalculateTextInfo() {
    CalculateConnectedTextobject();
    CalculateUsableTextobject();
}

void LevelDescription::CalculateAllDescription() {
    previousDescriptions = descriptions;
    descriptions.clear();
    findDescription_Is();
    findDescription_Has();
}

void LevelDescription::CalculateConnectedTextobject() {
    connectedTextobjetcs.clear();
    std::vector<ObjectInfo> existObject = {};
    for (Description &description : descriptions) {
        existObject = description.GetAllExistObject();
        connectedTextobjetcs.insert(existObject.begin(), existObject.end());
    }
}

void LevelDescription::CalculateUsableTextobject() {
    usableTextobjetcs.clear();
    for (Description &description : descriptions) {
        if (description.GetCenterOperator().objectId == TEXTOBJECT_IS) {
            if (TextobjectIdProc::IsGameobjectTextobject(description.GetSubObject().objectId)) {
                checkGameobjectDescriptionUsable(description);
            } else {
                checkPropertyDescriptionUsable(description);
            }
        } else if (description.GetCenterOperator().objectId == TEXTOBJECT_HAS) {
            checkHasDescriptionUsable(description);
        }
    }
}

bool LevelDescription::HasNewDescription() {
    if (previousDescriptions.size() < descriptions.size()) return true;
    for (size_t i = 0, j = 0; i < descriptions.size(); i++) {
        for (; j < previousDescriptions.size(); j++) {
            if (descriptions[i] == previousDescriptions[j]) break;
        }
        if (j == previousDescriptions.size()) return true;
    }
    return false;
}

bool LevelDescription::IsConnectedTextobject(ObjectInfo objectInfo) {
    return connectedTextobjetcs.find(objectInfo) != connectedTextobjetcs.end();
}

bool LevelDescription::IsUsableTextobject(ObjectInfo objectInfo) {
    return usableTextobjetcs.find(objectInfo) != usableTextobjetcs.end();
}

std::vector<std::pair<ObjectId, ObjectId>> LevelDescription::GetDescriptionsIs() {
    std::vector<std::pair<ObjectId, ObjectId>> result = {};

    for (Description &description : descriptions) {
        if (description.GetCenterOperator().objectId == TEXTOBJECT_HAS) continue;
        result.push_back({description.GetMainObject().objectId, description.GetSubObject().objectId});
    }

    return result;
}

std::vector<std::pair<ObjectId, ObjectId>> LevelDescription::GetDescriptionsHas() {
    std::vector<std::pair<ObjectId, ObjectId>> result = {};

    for (Description &description : descriptions) {
        if (description.GetCenterOperator().objectId == TEXTOBJECT_IS) continue;
        result.push_back({description.GetMainObject().objectId, description.GetSubObject().objectId});
    }

    return result;
}

void LevelDescription::findDescription_Is() {
    LevelData::AllObjectForeach([](ObjectBase &object) {
        if (object.GetObjectId() == TEXTOBJECT_IS) {
            ObjectInfo isObject = object.GetInfo();
            checkDescriptionHorizontal_Is(isObject);
            checkDescriptionVertical_Is(isObject);
        }
    });
}

void LevelDescription::checkDescriptionHorizontal_Is(ObjectInfo isObject) {
    Description description = {};
    description.SetCenterOperator(isObject);
    std::vector<Description> mainTexts = getMainObjectHorizontal(isObject.position.Left());
    std::vector<Description> subTexts = getSubObjectHorizontalHasProperty(isObject.position.Right());
    for (Description &mainText : mainTexts) {
        for (Description &subText : subTexts) {
            descriptions.push_back(mainText + subText + description);
        }
    }
}

void LevelDescription::checkDescriptionVertical_Is(ObjectInfo isObject) {
    Description description = {};
    description.SetCenterOperator(isObject);
    std::vector<Description> mainTexts = getMainObjectVertical(isObject.position.Up());
    std::vector<Description> subTexts = getSubObjectVerticalHasProperty(isObject.position.Down());
    for (Description &mainText : mainTexts) {
        for (Description &subText : subTexts) {
            descriptions.push_back(mainText + subText + description);
        }
    }
}

void LevelDescription::findDescription_Has() {
    LevelData::AllObjectForeach([](ObjectBase &object) {
        if (object.GetObjectId() == TEXTOBJECT_HAS) {
            ObjectInfo hasObject = object.GetInfo();
            checkDescriptionHorizontal_Has(hasObject);
            checkDescriptionVertical_Has(hasObject);
        }
    });
}

void LevelDescription::checkDescriptionHorizontal_Has(ObjectInfo hasObject) {
    Description description = {};
    description.SetCenterOperator(hasObject);
    std::vector<Description> mainTexts = getMainObjectHorizontal(hasObject.position.Left());
    std::vector<Description> subTexts = getSubObjectHorizontal(hasObject.position.Right());
    for (Description &mainText : mainTexts) {
        for (Description &subText : subTexts) {
            descriptions.push_back(mainText + subText + description);
        }
    }
}

void LevelDescription::checkDescriptionVertical_Has(ObjectInfo hasObject) {
    Description description = {};
    description.SetCenterOperator(hasObject);
    std::vector<Description> mainTexts = getMainObjectVertical(hasObject.position.Up());
    std::vector<Description> subTexts = getSubObjectVertical(hasObject.position.Down());
    for (Description &mainText : mainTexts) {
        for (Description &subText : subTexts) {
            descriptions.push_back(mainText + subText + description);
        }
    }
}

std::vector<LevelDescription::Description> LevelDescription::getMainObjectHorizontal(Point position) {
    if (!LevelData::IsInsideGameboard(position)) return {};
    if (!LevelData::HasTextobjectInBlock(position)) return {};
    ObjectInfo textobject = LevelData::GetTextobjectInBlock(position).GetInfo();
    if (!TextobjectIdProc::IsGameobjectTextobject(textobject.objectId)) return {};
    Description description = {};
    description.SetMainObject(textobject);

    std::vector<Description> result = getMainConnectHorizontal(position.Left());
    result.push_back(description);
    return result;
}

std::vector<LevelDescription::Description> LevelDescription::getSubObjectHorizontal(Point position) {
    if (!LevelData::IsInsideGameboard(position)) return {};
    if (!LevelData::HasTextobjectInBlock(position)) return {};
    ObjectInfo textobject = LevelData::GetTextobjectInBlock(position).GetInfo();
    if (!TextobjectIdProc::IsGameobjectTextobject(textobject.objectId)) return {};
    Description description = {};
    description.SetSubObject(textobject);

    std::vector<Description> result = getSubConnectHorizontal(position.Right());
    result.push_back(description);
    return result;
}

std::vector<LevelDescription::Description> LevelDescription::getSubObjectHorizontalHasProperty(Point position) {
    if (!LevelData::IsInsideGameboard(position)) return {};
    if (!LevelData::HasTextobjectInBlock(position)) return {};
    ObjectInfo textobject = LevelData::GetTextobjectInBlock(position).GetInfo();
    if (TextobjectIdProc::IsOperatorTextobject(textobject.objectId)) return {};
    Description description = {};
    description.SetSubObject(textobject);

    std::vector<Description> result = getSubConnectHorizontalHasProperty(position.Right());
    result.push_back(description);
    return result;
}


std::vector<LevelDescription::Description> LevelDescription::getMainObjectVertical(Point position) {
    if (!LevelData::IsInsideGameboard(position)) return {};
    if (!LevelData::HasTextobjectInBlock(position)) return {};
    ObjectInfo textobject = LevelData::GetTextobjectInBlock(position).GetInfo();
    if (!TextobjectIdProc::IsGameobjectTextobject(textobject.objectId)) return {};
    Description description = {};
    description.SetMainObject(textobject);

    std::vector<Description> result = getMainConnectVertical(position.Up());
    result.push_back(description);
    return result;
}

std::vector<LevelDescription::Description> LevelDescription::getSubObjectVertical(Point position) {
    if (!LevelData::IsInsideGameboard(position)) return {};
    if (!LevelData::HasTextobjectInBlock(position)) return {};
    ObjectInfo textobject = LevelData::GetTextobjectInBlock(position).GetInfo();
    if (!TextobjectIdProc::IsGameobjectTextobject(textobject.objectId)) return {};
    Description description = {};
    description.SetSubObject(textobject);

    std::vector<Description> result = getSubConnectVertical(position.Down());
    result.push_back(description);
    return result;
}

std::vector<LevelDescription::Description> LevelDescription::getSubObjectVerticalHasProperty(Point position) {
    if (!LevelData::IsInsideGameboard(position)) return {};
    if (!LevelData::HasTextobjectInBlock(position)) return {};
    ObjectInfo textobject = LevelData::GetTextobjectInBlock(position).GetInfo();
    if (TextobjectIdProc::IsOperatorTextobject(textobject.objectId)) return {};
    Description description = {};
    description.SetSubObject(textobject);

    std::vector<Description> result = getSubConnectVerticalHasProperty(position.Down());
    result.push_back(description);
    return result;
}
std::vector<LevelDescription::Description> LevelDescription::getMainConnectHorizontal(Point position) {
    if (!LevelData::IsInsideGameboard(position)) return {};
    if (!LevelData::HasTextobjectInBlock(position)) return {};
    ObjectInfo textobject = LevelData::GetTextobjectInBlock(position).GetInfo();
    if (textobject.objectId != TEXTOBJECT_AND) return {};
    Description description = {};
    description.SetMainConnect(textobject);

    std::vector<Description> result = getMainObjectHorizontal(position.Left());
    if (result.size() == 0) return {};
    result[result.size() - 1] += description;
    return result;
}

std::vector<LevelDescription::Description> LevelDescription::getSubConnectHorizontal(Point position) {
    if (!LevelData::IsInsideGameboard(position)) return {};
    if (!LevelData::HasTextobjectInBlock(position)) return {};
    ObjectInfo textobject = LevelData::GetTextobjectInBlock(position).GetInfo();
    if (textobject.objectId != TEXTOBJECT_AND) return {};
    Description description = {};
    description.SetSubConnect(textobject);

    std::vector<Description> result = getSubObjectHorizontal(position.Right());
    if (result.size() == 0) return {};
    result[result.size() - 1] += description;
    return result;
}

std::vector<LevelDescription::Description> LevelDescription::getSubConnectHorizontalHasProperty(Point position) {
    if (!LevelData::IsInsideGameboard(position)) return {};
    if (!LevelData::HasTextobjectInBlock(position)) return {};
    ObjectInfo textobject = LevelData::GetTextobjectInBlock(position).GetInfo();
    if (textobject.objectId != TEXTOBJECT_AND) return {};
    Description description = {};
    description.SetSubConnect(textobject);

    std::vector<Description> result = getSubObjectHorizontalHasProperty(position.Right());
    if (result.size() == 0) return {};
    result[result.size() - 1] += description;
    return result;
}

std::vector<LevelDescription::Description> LevelDescription::getMainConnectVertical(Point position) {
    if (!LevelData::IsInsideGameboard(position)) return {};
    if (!LevelData::HasTextobjectInBlock(position)) return {};
    ObjectInfo textobject = LevelData::GetTextobjectInBlock(position).GetInfo();
    if (textobject.objectId != TEXTOBJECT_AND) return {};
    Description description = {};
    description.SetMainConnect(textobject);

    std::vector<Description> result = getMainObjectVertical(position.Up());
    if (result.size() == 0) return {};
    result[result.size() - 1] += description;
    return result;
}

std::vector<LevelDescription::Description> LevelDescription::getSubConnectVertical(Point position) {
    if (!LevelData::IsInsideGameboard(position)) return {};
    if (!LevelData::HasTextobjectInBlock(position)) return {};
    ObjectInfo textobject = LevelData::GetTextobjectInBlock(position).GetInfo();
    if (textobject.objectId != TEXTOBJECT_AND) return {};
    Description description = {};
    description.SetSubConnect(textobject);

    std::vector<Description> result = getSubObjectVertical(position.Down());
    if (result.size() == 0) return {};
    result[result.size() - 1] += description;
    return result;
}

std::vector<LevelDescription::Description> LevelDescription::getSubConnectVerticalHasProperty(Point position) {
    if (!LevelData::IsInsideGameboard(position)) return {};
    if (!LevelData::HasTextobjectInBlock(position)) return {};
    ObjectInfo textobject = LevelData::GetTextobjectInBlock(position).GetInfo();
    if (textobject.objectId != TEXTOBJECT_AND) return {};
    Description description = {};
    description.SetSubConnect(textobject);

    std::vector<Description> result = getSubObjectVerticalHasProperty(position.Down());
    if (result.size() == 0) return {};
    result[result.size() - 1] += description;
    return result;
}

void LevelDescription::checkGameobjectDescriptionUsable(Description &description) {
    ObjectId mainObject = TextobjectIdProc::GetGameobjectId(description.GetMainObject().objectId);
    ObjectId subObject = TextobjectIdProc::GetGameobjectId(description.GetSubObject().objectId);
    if (PropertyManager::GetObjectConvert(mainObject) != subObject) return;

    std::vector<ObjectInfo> existObject = description.GetAllExistObject();
    usableTextobjetcs.insert(existObject.begin(), existObject.end());
}

void LevelDescription::checkPropertyDescriptionUsable(Description &description) {
    ObjectId mainObjectId = TextobjectIdProc::GetGameobjectId(description.GetMainObject().objectId);
    PropertyId propertyId = TextobjectIdProc::GetPropertyId(description.GetSubObject().objectId);
    if (!PropertyManager::ObjectHasProperty(mainObjectId, propertyId)) return;
    
    std::vector<ObjectInfo> existObject = description.GetAllExistObject();
    usableTextobjetcs.insert(existObject.begin(), existObject.end());
}

void LevelDescription::checkHasDescriptionUsable(Description &description) {
    std::vector<ObjectInfo> existObject = description.GetAllExistObject();
    usableTextobjetcs.insert(existObject.begin(), existObject.end());
}