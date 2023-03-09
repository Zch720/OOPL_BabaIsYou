#include "stdafx.h"
#include "log.h"
#include <fstream>
#include <strsafe.h>

#define LOG_FILENAME "./game_log.txt"

std::ofstream logFile;

void logInit() {
	struct stat logFileInfo;

	// 如果有舊的 log 檔案，則刪除
	if (stat(LOG_FILENAME, &logFileInfo) == 0) {
		remove(LOG_FILENAME);
	}
}

void logMessage(const char *typeMessage, const char *message) {
	// 以在最後加入文字的模式，開啟檔案
	logFile.open(LOG_FILENAME, std::ios_base::app);

	// 輸出訊息
	logFile << typeMessage << message << '\n';

	// 關閉檔案
	logFile.close();
}

void logInfo(const char *message) {
	logMessage("[INFO]: ", message);
}
void logWarning(const char *message) {
	logMessage("[WARN]: ", message);
}
void logError(const char *message) {
	logMessage("[ERROR]: ", message);
}