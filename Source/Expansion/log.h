#pragma once

/*
��l�� log
*/
void logInit();

/*
��X log �T���G
	info �@��T��
	warning ĵ�i�T��
	error ���~�T��
*/
void logInfo(const char *message);
void logWarning(const char *message);
void logError(const char *message);