#include "Vect.h"
#include <math.h>

Vec3f::Vec3f(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
Vec3f::Vec3f()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}
Vec3f::Vec3f(const Vec3f &other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

float& Vec3f::operator [](int index)
{
	return v[index];
}

Vec2f::Vec2f(float x, float y)
{
	this->x = x;
	this->y = y;
}
Vec2f::Vec2f()
{
	this->x = 0;
	this->y = 0;
}

Vec2f::Vec2f(const Vec2f & other)
{
	this->x = other.x;
	this->y = other.y;
}

float& Vec2f::operator [](int index)
{
	return v[index];
}

Vec2f Vec2f::operator-(const Vec2f & other) const
{
	return Vec2f(x - other.x, y - other.y);
}

Vec2f Vec2f::operator+(const Vec2f & other) const
{
	return Vec2f(x + other.x, y + other.y);
}

Vec2f Vec2f::operator*(const float s) const
{
	return Vec2f(x*s, y*s);
}

float Vec2f::distance(const Vec2f & other) const
{
	return sqrtf(powf(other.x - this->x, 2) + powf(other.y - this->y, 2));
}

float Vec2f::magnitude() const
{
	return sqrtf(powf(x, 2) + powf(y, 2));
}

Vec2f Vec2f::unit() const
{
	auto mag = magnitude();
	return Vec2f(x / mag, y / mag);
}