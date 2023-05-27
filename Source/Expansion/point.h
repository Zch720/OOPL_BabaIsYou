#pragma once

class Point : public POINT {
public:
	Point();
	Point(POINT point);
	Point(int x, int y);

	bool operator==(const POINT point);
	bool operator!=(const POINT point);

	Point operator=(const POINT point);

	Point operator+(const POINT point);
	Point operator-(const POINT point);
	Point operator*(const int number);
	friend Point operator*(const int number, Point point);

	Point operator+=(const POINT point);
	Point operator-=(const POINT point);
	Point operator*=(const int number);
	friend Point operator*=(const int number, Point point);

	Point Up();
	Point Down();
	Point Left();
	Point Right();

	Point Offset(int x, int y);
	Point Offset(POINT point);
	Point AddOffset(int x, int y);
	Point AddOffset(POINT point);
};