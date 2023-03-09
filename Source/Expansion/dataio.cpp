#include "stdafx.h"
#include "dataio.h"
#include <exception>
#include <fstream>

std::string loadFile(std::string filepath) {
	std::ifstream inputFile(filepath);

	// 如果無法存取檔案，回傳空字串
	if (!inputFile) {
		return "";
	}

	try {
		// 取得檔案大小（字串長度）
		inputFile.seekg(0, inputFile.end);
		int dataLength = (int)inputFile.tellg();
		inputFile.seekg(0, inputFile.beg);

		// 讀取內容
		std::string data(dataLength, ' ');
		inputFile.read(&data[0], dataLength);

		// 取得實際讀取字元數量
		dataLength = (int)inputFile.gcount();
		data[dataLength] = 0;

		// 關閉檔案
		inputFile.close();

		return data;
	}
	catch (std::exception e) {
		// 關閉檔案
		inputFile.close();

		return "";
	}
}

bool saveFile(std::string filepath, std::string data) {
	std::ofstream outputFile(filepath);

	// 如果無法開啟檔案，回傳 false
	if (!outputFile) {
		return false;
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

		return false;
	}
}