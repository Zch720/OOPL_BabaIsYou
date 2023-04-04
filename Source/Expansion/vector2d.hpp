#include "stdafx.h"
#include <vector>

template<typename T>
class vector2d : public std::vector<std::vector<T>> {
public:
	std::vector<T>& operator[](const int index) {
		return this->_Myfirst()[index];
	}
	T& operator[](const CPoint position) {
		return this->_Myfirst()[position.x][position.y];
	}
};