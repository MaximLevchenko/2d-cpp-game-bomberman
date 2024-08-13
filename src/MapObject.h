#pragma once

#ifndef BOMBERMAN_MAPOBJECT_H
#define BOMBERMAN_MAPOBJECT_H

#include <utility>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "GameObject.h"
#include "TextureManager.h"
#include "Map.h"

/**
 * @brief
 * Class for map objects, extends GameObject
 * */
class MapObject : public GameObject
{
public:
	/**
	 * @brief
	 * Overloaded constructor, initializes position, sets up texture and gives a tile id
	 * */
	MapObject(SDL_Texture *p_tex, int p_tileId, int p_x, int p_y, int p_w, int p_h, string p_tag_obj)
	{

		destRect.x = p_x * scale;
		destRect.y = p_y * scale;
		destRect.w = (p_w)*scale;
		destRect.h = (p_h)*scale; // destRect is from GameObject

		texture = p_tex;
		tileId = p_tileId;
		//		if(SDL_HasIntersection(&tileRect, &srcRect))
		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 32;
		tag_obj = std::move(p_tag_obj);
	}
	/**
	 * @brief
	 * Overloaded constructor, initializes position, sets up texture
	 * */
	MapObject(SDL_Texture *p_tex, int p_tileId, int p_x, int p_y, int p_w, int p_h)
	{

		destRect.x = p_x * scale;
		destRect.y = p_y * scale;
		destRect.w = (p_w)*scale;
		destRect.h = (p_h)*scale; // destRect is from GameObject

		texture = p_tex;
		tileId = p_tileId;
		//		if(SDL_HasIntersection(&tileRect, &srcRect))
		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 32;
		tag_obj = "default";
	}
	~MapObject()
	{
		//		SDL_DestroyTexture(texture);
	}
	/**
	 * @brief
	 * Draws map object on the map
	 * */
	void draw() override
	{
		TextureManager::draw(texture, srcRect, destRect);
	}
	int tileId;
	int scale = 2;
};

#endif // BOMBERMAN_MAPOBJECT_H
