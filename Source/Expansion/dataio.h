#pragma once

#include <string>

/*
讀取檔案，無法讀取時回傳空字串
*/
std::string loadFile(std::string filepath);

/*
儲存檔案
*/
bool saveFile(std::string filepath, std::string data);