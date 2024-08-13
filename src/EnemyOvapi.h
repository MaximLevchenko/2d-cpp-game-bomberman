#pragma once

#ifndef BOMBERMAN_ENEMYOVAPI_H
#define BOMBERMAN_ENEMYOVAPI_H

#include <string>
#include <queue>

#include "TextureManager.h"
#include "GameObject.h"
#include "Game.h"
#include "Vector2D.h"
#include "Map.h"
#include "TransformObject.h"
#include "Enemy.h"

/**
 * @brief
 * Smart type of an Enemy, uses BFS to find the shortest path to a Player, extends Enemy
 * */
class EnemyOvapi : public Enemy
{
public:
	/**
	 * @brief
	 * Overloaded constructor which invokes a constructor of the "Enemy"
	 * */
	EnemyOvapi(const char *p_filename, int p_x, int p_y, std::string p_tag_obj);
	/**
	 * @brief
	 * Updates position and initiates BFS algorithm each tile an enemy has moved
	 * */
	void update() override;
	/**
	 * @brief
	 * Draws the enemy to the screen
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
	 * Function which finds a basic pseudo-random movement for the enemy
	 * */
	void transformPositionToTiles();
	/**
	 * @brief
	 * Function to find the shortest path between two rectangulars
	 * @param[in,out] en_rect rectangular of an enemy
	 * @param[in,out] pl_rect rectangular of a player
	 * */
	void findShortestPath(const SDL_Rect &en_rect, const SDL_Rect &pl_rect);
	/**
	 * @brief
	 * Debug function to print the found path
	 * */
	void printPath(vector<pair<int, int>> &path);
	/**
	 * @brief
	 * Function to check if path we want to visit already has been visited
	 * @param[in,out] to_find coordinates of an enemy
	 * @param[in,out] path all visited path
	 * */
	bool isVisited(const pair<int, int> &to_find, const vector<pair<int, int>> &path);

	vector<pair<int, int>> path_to_player;
	vector<pair<int, int>> coordinates_path; // path to player in coordinates that he should do tp get to the target
	Vector2D position;
	TransformObject transformObject;

	SDL_Rect pl_src_rect, pl_dest_rect;
	SDL_Rect en_src_rect, en_dest_rect;

	bool flag = true;
};

#endif // BOMBERMAN_ENEMYOVAPI_H
