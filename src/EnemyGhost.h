#pragma once

#ifndef BOMBERMAN_ENEMYGHOST_H
#define BOMBERMAN_ENEMYGHOST_H

#include "Enemy.h"
/**
 * @brief
 * Enemy type which can walk through
 * */
class EnemyGhost : public Enemy
{
public:
	/**
	 * @brief
	 * Overloaded constructor which invokes a constructor of the "Enemy", extends Enemy
	 * */
	EnemyGhost(const char *p_filename, int p_x, int p_y, string p_tag_obj) : Enemy(p_filename, p_x, p_y, p_tag_obj) {}
	~EnemyGhost() override {}
	/**
	 * @brief
	 *  Invokes an update function of the "Enemy" class
	 * */
	void update() override;
	/**
	 * @brief
	 *  Invokes a draw function of the "Enemy"  class
	 * */
	void draw() override;
};

#endif // BOMBERMAN_ENEMYGHOST_H
