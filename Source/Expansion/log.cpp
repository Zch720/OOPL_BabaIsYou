#include "stdafx.h"
#include "log.h"
#include <stdio.h>
#include <stdarg.h>
#include <debugapi.h>

#define LOG_FILENAME "./game_log.txt"

bool Log::isInitialized = false;
std::ofstream Log::logFile = std::ofstream();

void Log::LogDebugMessage(const char *outputFormat, ...) {
	if (!isInitialized) {
		logInit();
	}

	va_list va;
	va_start(va, outputFormat);

	size_t messageSize = vsnprintf(NULL, 0, outputFormat, va) + 1;
	char *message = new char[messageSize];
	char *messageWithNewLine = new char[messageSize + 1];
	vsprintf_s(message, messageSize, outputFormat, va);
	sprintf_s(messageWithNewLine, messageSize + 1, "%s\n", message);
	logMessage(messageWithNewLine);
	OutputDebugString(messageWithNewLine);
	
	delete[] message;
	delete[] messageWithNewLine;
	va_end(va);
}

void Log::LogInfo(const char *outputFormat, ...) {
	if (!isInitialized) {
		logInit();
	}

	va_list va;
	va_start(va, outputFormat);

	size_t messageSize = vsnprintf(NULL, 0, outputFormat, va) + 1;
	char *message = new char[messageSize];
	char *messageWithTag = new char[messageSize + 9];
	vsprintf_s(message, messageSize, outputFormat, va);
	sprintf_s(messageWithTag, messageSize + 9, "[INFO]: %s\n", message);
	logMessage(messageWithTag);
	OutputDebugString(messageWithTag);
	
	delete[] message;
	delete[] messageWithTag;
	va_end(va);
}
void Log::LogWarning(const char *outputFormat, ...) {
	if (!isInitialized) {
		logInit();
	}

	va_list va;
	va_start(va, outputFormat);

	size_t messageSize = vsnprintf(NULL, 0, outputFormat, va) + 1;
	char *message = new char[messageSize];
	char *messageWithTag = new char[messageSize + 9];
	vsprintf_s(message, messageSize, outputFormat, va);
	sprintf_s(messageWithTag, messageSize + 9, "[WARN]: %s\n", message);
	logMessage(messageWithTag);
	OutputDebugString(messageWithTag);
	
	delete[] message;
	delete[] messageWithTag;
	va_end(va);
}
void Log::LogError(const char *outputFormat, ...) {
	if (!isInitialized) {
		logInit();
	}

	va_list va;
	va_start(va, outputFormat);

	size_t messageSize = vsnprintf(NULL, 0, outputFormat, va) + 1;
	char *message = new char[messageSize];
	char *messageWithTag = new char[messageSize + 10];
	vsprintf_s(message, messageSize, outputFormat, va);
	sprintf_s(messageWithTag, messageSize + 10, "[INFO]: %s\n", message);
	logMessage(messageWithTag);
	OutputDebugString(messageWithTag);
	
	delete[] message;
	delete[] messageWithTag;
	va_end(va);
}

void Log::logInit() {
	struct stat logFileInfo;

	// 如果有舊的 log 檔案，則刪除
	if (stat(LOG_FILENAME, &logFileInfo) == 0) {
		remove(LOG_FILENAME);
	}

	isInitialized = true;
}

void Log::logMessage(const char *message) {
	// 以在最後加入文字的模式，開啟檔案
	logFile.open(LOG_FILENAME, std::ios_base::app);

	// 輸出訊息
	logFile << message;

	// 關閉檔案
	logFile.close();
}