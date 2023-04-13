#include "stdafx.h"
#include "point.h"

Point::Point() {
	this->x = 0;
	this->y = 0;
}
Point::Point(int x, int y) {
	this->x = x;
	this->y = y;
}

bool Point::operator==(const POINT point) {
	return {this->x == point.x && this->y == point.y};
}
bool Point::operator!=(const POINT point) {
	return {this->x != point.x || this->y != point.y};
}

Point Point::operator+(const POINT point) {
	return Point(this->x + point.x, this->y + point.y);
}
Point Point::operator-(const POINT point) {
	return Point(this->x - point.x, this->y - point.y);
}
Point Point::operator*(const int number) {
	return Point(this->x * number, this->y * number);
}

Point Point::operator+=(const POINT point) {
	this->x += point.x;
	this->y += point.y;
	return *this;
}
Point Point::operator-=(const POINT point) {
	this->x -= point.x;
	this->y -= point.y;
	return *this;
}
Point Point::operator*=(const int number) {
	this->x *= number;
	this->y *= number;
	return *this;
}

Point Point::Up() {
	return Point(this->x, this->y - 1);
}
Point Point::Down() {
	return Point(this->x, this->y + 1);
}
Point Point::Left() {
	return Point(this->x - 1, this->y);
}
Point Point::Right() {
	return Point(this->x + 1, this->y);
}

Point Point::Offset(int x, int y) {
	return Point(this->x + x, this->y + y);
}
Point Point::Offset(POINT point) {
	return Point(this->x + point.x, this->y + point.y);
}
Point Point::AddOffset(int x, int y) {
	this->x += x;
	this->y += y;
	return *this;
}
Point Point::AddOffset(POINT point) {
	this->x += point.x;
	this->y += point.y;
	return *this;
}