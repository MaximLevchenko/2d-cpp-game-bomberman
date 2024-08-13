#pragma once

#ifndef BOMBERMAN_BOMB_H
#define BOMBERMAN_BOMB_H

#include "GameObject.h"
#include "Vector2D.h"
#include "TextureManager.h"
#include "TransformObject.h"
//#define USE_FANCYPANTS
#include "Game.h"
//#ifdef USE_FANCYPANTS
//#endif
/**
 * @brief
 * Class, which manages bomb placement for the Player, extends GameObject
 * */
class Bomb : public GameObject
{
public:
	Bomb() = default;
	~Bomb() override;
	/**
	 * @brief
	 * @param pl_coords coordinates of the player
	 * */
	Bomb(std::pair<int, int> pl_coords);
	/**
	 * @brief
	 * Each frame decreases a time for the bomb to explode
	 * */
	void update() override;
	/**
	 * @brief
	 * Each frame draws a bomb the the screen
	 * */
	void draw() override;
	/**
	 * @brief
	 * Sets the texture for the bomb
	 * @param p_filename Path to the texture
	 * */
	void setTex(const char *p_filename);
	bool isPlaced = false;
	TransformObject transformObject_b;
	Vector2D position_b;
	/**
	 * @brief
	 * Coordinates of the bomb on the map
	 * */
	std::pair<int, int> index_map;
	/**
	 * @brief
	 * Constant time it takes for a bomb to explode(3sec)
	 * */
	int timeToExplode = 180;
};

#endif // BOMBERMAN_BOMB_H
