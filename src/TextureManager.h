
#ifndef BOMBERMAN_TEXTUREMANAGER_H
#define BOMBERMAN_TEXTUREMANAGER_H

#include <iostream>
#include "memory"

#include "ErrorHandler.h"
using namespace std;

#include "Game.h"

/**
 * @brief
 * Loads and draws textures to the screen
 * */
class TextureManager
{
public:
	/**
	 * @brief
	 * Loads texture
	 * */
	static SDL_Texture *loadTexture(const char *p_filename);
	/**
	 * @brief
	 *Draws texture to the screen
	 * */
	static void draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dst);
};

#endif // BOMBERMAN_TEXTUREMANAGER_H
