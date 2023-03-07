#include "stdafx.h"
#include "log.h"
#include <fstream>
#include <strsafe.h>

#define LOG_FILENAME "./game_log.txt"

std::ofstream logFile;

void logInit() {
	struct stat logFileInfo;

	if (stat(LOG_FILENAME, &logFileInfo) == 0) {
		remove(LOG_FILENAME);
	}
}

void logMessage(const char *typeMessage, const char *message) {
	logFile.open(LOG_FILENAME, std::ios_base::app);

	logFile << typeMessage << message << '\n';

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