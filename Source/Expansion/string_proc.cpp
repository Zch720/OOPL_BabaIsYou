#include "stdafx.h"
#include "string_proc.h"
#include <sstream>

std::vector<std::string> stringSplit(std::string& str, char delim) {
	std::vector<std::string> tokens;
	std::stringstream ss(str);
	std::string token;

	while (std::getline(ss, token, delim)) {
		tokens.push_back(token);
	}

	return tokens;
}

std::string intToString(int number) {
	std::ostringstream oss;
	oss << number;
	return oss.str();
}

int stringToInt(std::string& str) {
	std::istringstream iss(str);
	int number;
	iss >> number;
	return number;
}