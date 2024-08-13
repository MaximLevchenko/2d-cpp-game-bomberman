#pragma once

#ifndef BOMBERMAN_FLAME_H
#define BOMBERMAN_FLAME_H

#include "string"

#include "GameObject.h"
#include "TextureManager.h"
/**
 * @brief
 * Class which describes a behaviour of a flame object, which is created after the bomb explosion, extends GameObject
 * */
class Flame : public GameObject
{
public:
	/**
	 * @brief
	 * Overloaded constructor, sets up the position, texture and tag of the object
	 * */
	Flame(SDL_Texture *p_tex, int p_x, int p_y, int p_w, int p_h, std::string p_tag_obj)
	{
		destRect.x = p_x * scale;
		destRect.y = p_y * scale;
		destRect.w = (p_w)*scale;
		destRect.h = (p_h)*scale; // destRect is from GameObject

		texture = p_tex;
		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 32;
		tag_obj = p_tag_obj;
	}
	~Flame() override
	{
	}
	/**
	 * @brief
	 * Each frame decreases its screen time, when screen time hits 0 ----> we remove this object
	 * */
	void update() override
	{
		if (screenTime <= 0)
		{
			isAlive = false;
			return;
		}
		screenTime--;
	}
	/**
	 * @brief
	 * Draws a flame to the screen
	 * */
	void draw() override
	{
		TextureManager::draw(texture, srcRect, destRect);
	}

	int scale = 2;
	int screenTime = 30;
};

#endif // BOMBERMAN_FLAME_H
