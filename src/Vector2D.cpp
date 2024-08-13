
#include "Vector2D.h"

Vector2D::Vector2D()
{
	x = 0.0f;
	y = 0.0f;
}
Vector2D::Vector2D(float p_x, float p_y)
{
	this->x = p_x;
	this->y = p_y;
}
Vector2D &Vector2D::add(const Vector2D &vec)
{
	this->x += vec.x;
	this->y += vec.y;
	return *this;
}
Vector2D &Vector2D::substract(const Vector2D &vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	return *this;
}
Vector2D &Vector2D::multiply(const Vector2D &vec)
{
	this->x *= vec.x;
	this->y *= vec.y;
	return *this;
}
Vector2D &Vector2D::divide(const Vector2D &vec)
{
	this->x /= vec.x;
	this->y /= vec.y;
	return *this;
}
Vector2D &operator+(Vector2D &vec1, const Vector2D &vec2)
{
	return vec1.add(vec2);
}
Vector2D &operator-(Vector2D &vec1, const Vector2D &vec2)
{
	return vec1.substract(vec2);
}
Vector2D &operator*(Vector2D &vec1, const Vector2D &vec2)
{
	return vec1.multiply(vec2);
}
Vector2D &operator/(Vector2D &vec1, const Vector2D &vec2)
{
	return vec1.divide(vec2);
}
Vector2D &Vector2D::operator+=(const Vector2D &vec)
{
	return this->add(vec);
}
Vector2D &Vector2D::operator-=(const Vector2D &vec)
{
	return this->substract(vec);
}
Vector2D &Vector2D::operator*=(const Vector2D &vec)
{
	return this->multiply(vec);
}
Vector2D &Vector2D::operator/=(const Vector2D &vec)
{
	return this->divide(vec);
}
Vector2D &Vector2D::operator*(const int &p_scale)
{
	this->x *= p_scale;
	this->y *= p_scale;
	return *this;
}
Vector2D Vector2D::zero()
{
	x = 0.0f;
	y = 0.0f;

	return *this;
	//	return *this;
}

std::ostream &operator<<(std::ostream &stream, const Vector2D &vec)
{
	stream << "(" << vec.x << "," << vec.y << ")";
	return stream;
}
