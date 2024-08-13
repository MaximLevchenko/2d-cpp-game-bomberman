#pragma once

#ifndef BOMBERMAN_PLAYER_H
#define BOMBERMAN_PLAYER_H

#include "GameObject.h"
#include "TextureManager.h"
#include "TransformObject.h"
#include "Vector2D.h"
#include "KeyboardController.h"
#include "Bomb.h"
#include "Flame.h"
#include "Map.h"
#include "CollisionManager.h"
#include "Bonus.h"
#include "RandomNumberGenerator.h"
// class Bomb;
//#include ""
/**
 * @brief
 * Class for defining player`s behaviour
 * */
class Player : public GameObject
{
public:
	/**
	 * @brief
	 * Default constructor
	 * */
	Player() = default;
	Player(const char *filename);
	/**
	 * @brief
	 * Overloaded constructor, initializes position, sets up texture and gives a tile id
	 * */
	Player(const char *filename, int x, int y, string p_tag_obj);

	~Player() override
	{
		SDL_DestroyTexture(texture);
	}
	/**
	 * @brief
	 * Updates a position of a player, detects if bomb was placed, detects if flames
	 * should be deleted from the map, explodes a bomb
	 *
	 * */
	void update() override;
	/**
	 * @brief
	 * Draws a player to the screen
	 * */
	void draw() override;
	/**
	 * @brief
	 * Sets up a texture for the player
	 * */
	void setTex(const char *p_filename);
	/**
	 * @brief
	 * Places a bomb on the map
	 * */
	void placeBomb();
	/**
	 * @brief
	 * Bomb explosion, destroys breakable walls if they are in range of a fire
	 * */
	void explodeBomb(unique_ptr<Bomb> &bomb);
	/**
	 * @brief
	 * OChecks if there is a wall on given coordinates
	 * @param x_coord x-axis coordinate of the wall
	 * @param y_coord y-axis coordinate of the wall
	 * @return true if breakable wall is on the given coordinates, false otherwise
	 * */
	bool isWallOnTile(int x_coord, int y_coord, int id_tile);
	/**
	 * @brief
	 * Changes our map accordingly to the bomb explosion
	 * */
	void changeMapArrayAndMapObject(int y_coord, int x_coord, int y_resolution, SDL_Texture *p_texture);
	/**
	 * @brief
	 * Adds an effect if the player picked up a bonus
	 * @param tag tag ob the bonus type
	 * */
	void addEffect(string p_tag_bonus);
	bool bombIsPlaced = false;
	int flameRange = 1;
	int flameIncreaseCounter = 0;
	// int bombCount;
	//	static size_t currentScore;

	Vector2D position;
	KeyboardController keyboardController;
	/**
	 * @brief
	 * Container for storing Bomb objects
	 * */
	vector<unique_ptr<Bomb>> bombContainer;
	/**
	 * @brief
	 * Container for storing FLame
	 * */
	static vector<unique_ptr<Flame>> flames;
};

#endif // BOMBERMAN_PLAYER_H
