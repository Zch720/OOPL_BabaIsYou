#pragma once

/*
初始化 log
*/
void logInit();

/*
輸出 log 訊息：
	info 一般訊息
	warning 警告訊息
	error 錯誤訊息
*/
void logInfo(const char *message);
void logWarning(const char *message);
void logError(const char *message);