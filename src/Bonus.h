#pragma once

#ifndef BOMBERMAN_BONUS_H
#define BOMBERMAN_BONUS_H

#include <string>

#include "GameObject.h"
#include "TextureManager.h"

/**
 * @brief
 * Enum of all possible bonus types
 * */
enum BonusType
{
	addBomb,
	addFlameRange,
	addSpeed
};

/**
 * @brief
 * Class which defines a behaviour for bonuses.
 * Bonus can be randomly spawned after the wall explosion.
 * After the Player "picks up" a bonus, it grants a certain effect, extends GameObject
 * */
class Bonus : public GameObject
{
public:
	/**
	 * @brief
	 * Overloaded construction for the Bonus
	 * @param x_coord position at x-axis
	 * @param y_coord position at x-axis
	 * @param bonus_id unique id of the bonus type
	 * @param p_tag_obj unique tag for each bonus type
	 * */
	Bonus(int x_coord, int y_coord, SDL_Texture *p_texture, string p_tag_obj)
	{
		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 32;

		destRect.x = x_coord * 64;
		destRect.y = y_coord * 64;
		destRect.w = srcRect.w * scale;
		destRect.h = srcRect.h * scale;

		texture = p_texture;

		tag_obj = p_tag_obj;
		// bonus_id = 1;
	}

	~Bonus() override {}
	/**
	 * @brief
	 * No implementation, we don`t need need to update position of the bonus as its static
	 * */
	void update() override{};
	void draw() override
	{
		TextureManager::draw(texture, srcRect, destRect);
	}
	/**
	 * @brief
	 * Size scale of each bonus object
	 * */
	int scale = 2;
};

#endif // BOMBERMAN_BONUS_H
