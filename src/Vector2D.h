#pragma once

#ifndef BOMBERMAN_VECTOR2D_H
#define BOMBERMAN_VECTOR2D_H

#include <iostream>

/**
 * @brief
 * Class for physics and math for our game
 * */
class Vector2D
{
public:
	Vector2D();
	Vector2D(float p_x, float p_y);

	Vector2D &add(const Vector2D &vec);
	Vector2D &substract(const Vector2D &vec);
	Vector2D &multiply(const Vector2D &vec);
	Vector2D &divide(const Vector2D &vec);

	friend Vector2D &operator+(Vector2D &vec1, const Vector2D &vec2);
	friend Vector2D &operator-(Vector2D &vec1, const Vector2D &vec2);
	friend Vector2D &operator*(Vector2D &vec1, const Vector2D &vec2);
	friend Vector2D &operator/(Vector2D &vec1, const Vector2D &vec2);

	Vector2D &operator+=(const Vector2D &vec);
	Vector2D &operator-=(const Vector2D &vec);
	Vector2D &operator*=(const Vector2D &vec);
	Vector2D &operator/=(const Vector2D &vec);

	Vector2D &operator*(const int &p_scale);
	Vector2D zero();

	friend std::ostream &operator<<(std::ostream &stream, const Vector2D &vec);

	float x;
	float y;
};

#endif // BOMBERMAN_VECTOR2D_H
