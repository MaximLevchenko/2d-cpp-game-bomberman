#pragma once

#ifndef BOMBERMAN_ENEMY_H
#define BOMBERMAN_ENEMY_H

#include "GameObject.h"
#include "TransformObject.h"
#include "Vector2D.h"
#include "TextureManager.h"
#include "Player.h"
#include "Game.h"

/**
 * @brief
 * Class for defining common behaviour for the enemy, extends GameObject
 * */
class Enemy : public GameObject
{
public:
	Enemy() = default;
	/**
	 * @brief
	 * Overloaded constructor
	 * @param p_filename path to the texture image
	 * @param p_x x-axis initial pos of the enemy
	 * @param p_y y-axis initial pos of the enemy
	 * @param p_tag_obj unique tag of the enemy
	 * */
	Enemy(const char *p_filename, int p_x, int p_y, string p_tag_obj);
	~Enemy() override {} // SDL_DestroyTexture(texture);
						 /**
						  * @brief
						  * Update function for the enemy, updates emenie`s position accordingly to the user`s input
						  * */
	void update() override;
	/**
	 * @brief
	 * Each frame draw`s enemy object to the screen
	 * */
	void draw() override;

	/**
	 * @brief
	 * Sets the texture for the bomb
	 * @param p_filename Path to the texture
	 * */
	void setTex(const char *p_filename);
	/**
	 * @brief
	 * Transforms position of the enemy and the player to the coordinates on the map
	 * */
	void transformPositionToTiles();
	/**
	 * @brief
	 * Function which finds a basic pseudo-random movement for the enemy
	 * */
	void findDummyPath(pair<int, int> enemy_coords);
	/**
	 * @brief
	 * Function which moves an enemy through the found pseudo-random path
	 * */
	bool moveThroughFoundDummyPath();
	/**
	 * @brief
	 * Variable which stores previous direction an enemy went to
	 * */
	string prev_direction;
	SDL_Rect pl_src_rect, pl_dest_rect;
	SDL_Rect en_src_rect, en_dest_rect;
	/**
	 * @brief
	 * Pair of coordinates for basic movement
	 * */
	pair<int, int> dummyMovementCoords;
	TransformObject transformObject;
	Vector2D position;
	//	KeyboardController keyboardController;
};

#endif // BOMBERMAN_ENEMY_H
