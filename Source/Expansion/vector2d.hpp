#pragma once
#include "stdafx.h"
#include <vector>
#include <functional>

template<typename T>
class vector2d : public std::vector<std::vector<T>> {
public:
	typedef std::function<void(T&)> ElementProcFunc;

	std::vector<T>& operator[](const int index) {
		return this->_Myfirst()[index];
	}
	T& operator[](const POINT position) {
		return this->_Myfirst()[position.x][position.y];
	}
	void foreach(ElementProcFunc func) {
		for (std::vector<T> &vec : *this) {
			for (T &element : vec) {
				func(element);
			}
		}
	}
};