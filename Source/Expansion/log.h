#pragma once

#include <fstream>

class Log {
private:
	static bool isInitialized;
	static std::ofstream logFile;
	static void logInit();
	static void logMessage(const char *message);

public:
	/*
	輸出 log 訊息：
		debug message 除錯訊息，無前綴，並且不輸出在 gamelog.txt 中
		info 一般訊息
		warning 警告訊息
		error 錯誤訊息
	*/
	static void LogDebugMessage(const char *outputFormat, ...);
	static void LogInfo(const char *outputFormat, ...);
	static void LogWarning(const char *outputFormat, ...);
	static void LogError(const char *outputFormat, ...);
};