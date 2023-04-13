#pragma once

class Point : public POINT {
public:
	Point();
	Point(int x, int y);

	bool operator==(const POINT point);
	bool operator!=(const POINT point);

	Point operator+(const POINT point);
	Point operator-(const POINT point);
	Point operator*(const int number);

	Point operator+=(const POINT point);
	Point operator-=(const POINT point);
	Point operator*=(const int number);

	Point Up();
	Point Down();
	Point Left();
	Point Right();

	Point Offset(int x, int y);
	Point Offset(POINT point);
	Point AddOffset(int x, int y);
	Point AddOffset(POINT point);
};