#pragma once

class Vec3f
{
public:
	union
	{
		struct
		{
			float x, y, z;
		};
		float v[3];
	};
	Vec3f();
	Vec3f(const Vec3f &other);
	Vec3f(float x, float y, float z);
	float& operator [](int);
};

class Vec2f
{
public:
	union
	{
		struct
		{
			float x, y;
		};
		float v[2];
	};
	Vec2f();
	Vec2f(float x, float y);
	Vec2f(const Vec2f &other);
	float& operator [](int);
	Vec2f operator -(const Vec2f &other) const;
	Vec2f operator +(const Vec2f &other) const;
	Vec2f operator *(const float s) const;
	Vec2f operator /(const float s) const;

	float dotProduct(const Vec2f &other) const;
	float distance(const Vec2f &other) const;
	float magnitude() const;
	Vec2f unit() const;
};