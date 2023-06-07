#include "stdafx.h"
#include "dataio.h"
#include <exception>
#include <fstream>
#include "log.h"

std::string loadFile(std::string filepath) {
	std::ifstream inputFile(filepath);

	// 如果無法存取檔案，回傳空字串
	if (!inputFile) {
		Log::LogError("can't load file '%s'", filepath.c_str());
	}

	std::string data = "";
	std::string line;

	while (std::getline(inputFile, line)) {
		data += line + "\n";
	}

	inputFile.close();
	return data;
}

bool saveFile(std::string filepath, std::string data) {
	std::ofstream outputFile(filepath);

	// 如果無法開啟檔案，回傳 false
	if (!outputFile) {
		Log::LogError("can't save file '%s'", filepath.c_str());
	}

	try {
		// 輸出檔案
		const char *data_cstr = data.c_str();
		outputFile.write(data_cstr, strlen(data_cstr));

		// 關閉檔案
		outputFile.close();

		return true;
	}
	catch (std::exception e) {
		// 關閉檔案
		outputFile.close();

		Log::LogError("can't save file '%s'", filepath.c_str());
		return false;
	}
}