#pragma once

#ifndef BOMBERMAN_GAMEOBJECT_H
#define BOMBERMAN_GAMEOBJECT_H

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/**
 * @brief
 * Base class for all entities in the game
 * */
class GameObject
{
private:
public:
	GameObject() {}
	virtual ~GameObject() {}
	/**
	 * @brief
	 * Each object should have an update function
	 * */
	virtual void update() {}
	/**
	 * @brief
	 * Each object should have a draw function
	 * */
	virtual void draw() {}
	/**
	 * @brief
	 * Each object should have a source and destination rectangular, so we can display it onto the screen
	 * */
	SDL_Rect srcRect, destRect; // for displaying sprites
	/**
	 * @brief
	 * Each object should have a texture
	 * */
	SDL_Texture *texture;
	/**
	 * @brief
	 * Each object should have a tag
	 * */
	std::string tag_obj;
	size_t currentScore = 0;
	size_t bombCount = 0;
	/**
	 * @brief
	 * Each object should have an indicator to tell if an entity is alive or not
	 * */
	bool isAlive = true;
};

#endif // BOMBERMAN_GAMEOBJECT_H
