#pragma once

class Vector2 {
public:
	Vector2();
	Vector2(int x, int y);
	int x, y;
	static const Vector2 Zero;
	Vector2& operator+=(const Vector2& right)
	{
		x += right.x;
		y += right.y;
		return *this;
	}
};