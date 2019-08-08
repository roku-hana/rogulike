#pragma once

class Vector2 {
public:
	Vector2();
	Vector2(int x, int y);
	int x, y;
	static const Vector2 Zero;
};