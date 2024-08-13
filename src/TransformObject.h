#pragma once

#ifndef BOMBERMAN_TRANSFORMOBJECT_H
#define BOMBERMAN_TRANSFORMOBJECT_H

#include "Vector2D.h"

/**
 * @brief
 * Class for defining objects speed, scale, height and width
 * */
class TransformObject
{
public:
	Vector2D position;
	Vector2D velocity;

	float speed = 3;
	int height = 32;
	int width = 32;
	float scale = 1.5f;

	TransformObject()
	{
		position.zero(); // initialize x and y to zero
	}
	TransformObject(int p_scale)
	{
		position.zero();
		scale = p_scale;
	}
	// TransformObject(float p_x, float p_y)
	// {
	// 	position.zero();
	// 	//		position.x = p_x;
	// 	//		position.y = p_y;
	// }

	TransformObject(float p_x, float p_y, int p_h, int p_w, int p_scale)
	{
		position.x = p_x;
		position.y = p_y;
		height = p_h;
		width = p_w;
		scale = p_scale;
	}
};

#endif // BOMBERMAN_TRANSFORMOBJECT_H
