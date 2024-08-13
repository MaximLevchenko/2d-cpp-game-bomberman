//
// Created by User win 10 on 10.06.2022.
//

#include "Enemy.h"

Enemy::Enemy(const char *p_filename, int p_x, int p_y, string p_tag_obj)
{
	transformObject.speed = 2;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = 32;
	srcRect.h = 32;

	destRect.x = p_x * 2;
	destRect.y = p_y * 2;
	destRect.w = srcRect.w * transformObject.scale;
	destRect.h = srcRect.h * transformObject.scale;
	//	transformPositionToTiles();

	en_dest_rect = destRect;
	en_src_rect = srcRect;

	setTex(p_filename);
	tag_obj = p_tag_obj;
}

void Enemy::update()
{
	transformPositionToTiles();
	//	position.x = 0;
	//	position.y = 0;
	//	destRect.x += static_cast<int>(position.x);
	//	destRect.y += static_cast<int>(position.y);
	destRect.w = srcRect.w * transformObject.scale;
	destRect.h = srcRect.h * transformObject.scale;
}
void Enemy::draw()
{
	TextureManager::draw(texture, srcRect, destRect);
	//	cout<<"draw enemy"<<endl;
}

void Enemy::setTex(const char *p_filename)
{
	texture = TextureManager::loadTexture(p_filename);
}
bool Enemy::moveThroughFoundDummyPath()
{
	// if the y-axis of our path is not null, then we should move whether down or up
	if (dummyMovementCoords.first != 0)
	{
		if (dummyMovementCoords.first > 0)
		{
			dummyMovementCoords.first -= transformObject.speed;
			while (dummyMovementCoords.first < 0)
				dummyMovementCoords.first++;
			destRect.y += transformObject.speed;
		}
		else if (dummyMovementCoords.first < 0)
		{
			dummyMovementCoords.first += transformObject.speed;
			while (dummyMovementCoords.first > 0)
				dummyMovementCoords.first--;
			destRect.y -= transformObject.speed;
		}
		return true;
	}
	// if the x-axis of our path is not null, then we should move whether left or right
	if (dummyMovementCoords.second != 0)
	{
		if (dummyMovementCoords.second > 0)
		{
			dummyMovementCoords.second -= transformObject.speed;
			while (dummyMovementCoords.second < 0)
				dummyMovementCoords.second++;
			destRect.x += transformObject.speed;
		}
		else if (dummyMovementCoords.second < 0)
		{
			dummyMovementCoords.second += transformObject.speed;
			while (dummyMovementCoords.second > 0)
				dummyMovementCoords.second--;
			destRect.x -= transformObject.speed;
		}
		return true;
	}
	return false;
}
void Enemy::findDummyPath(pair<int, int> enemy_coords)
{
	transformObject.speed = 2;
	int y_coords = enemy_coords.first, x_coords = enemy_coords.second;

	if (moveThroughFoundDummyPath()) // if we are moving through the path, we dont need to further execute the code in this func
		return;

	if ((dummyMovementCoords.first == 0 && dummyMovementCoords.second == 0 && prev_direction != "left" &&
		 Map::map_arr[y_coords - 1][x_coords] == 2) ||
		(dummyMovementCoords.first == 0 && dummyMovementCoords.second == 0 &&
		 (Map::map_arr[y_coords - 1][x_coords] == 2 || Map::map_arr[y_coords - 1][x_coords] == 3) &&
		 tag_obj == "enemy_ghost")) // up
	{
		int i = 1;
		for (; Map::map_arr[y_coords - i - 1][x_coords] == 2 || (Map::map_arr[y_coords - i - 1][x_coords] == 3 &&
																 tag_obj == "enemy_ghost");
			 i++)
		{
		}
		dummyMovementCoords = {(y_coords - i - y_coords) * 64, (x_coords - x_coords) * 64};
		prev_direction = "up";
	}
	else if ((dummyMovementCoords.first == 0 && dummyMovementCoords.second == 0 && prev_direction != "down" &&
			  Map::map_arr[y_coords][x_coords + 1] == 2) ||
			 (dummyMovementCoords.first == 0 && dummyMovementCoords.second == 0 &&
			  (Map::map_arr[y_coords][x_coords + 1] == 2 || Map::map_arr[y_coords][x_coords + 1] == 3) &&
			  tag_obj == "enemy_ghost")) // right
	{
		int i = 1;
		for (; Map::map_arr[y_coords][x_coords + i + 1] == 2 || (Map::map_arr[y_coords][x_coords + i + 1] == 3 &&
																 tag_obj == "enemy_ghost");
			 i++)
		{
		}
		dummyMovementCoords = {(y_coords - y_coords) * 64, (x_coords + i - x_coords) * 64};
		prev_direction = "right";
	}
	else if ((dummyMovementCoords.first == 0 && dummyMovementCoords.second == 0 && prev_direction != "up" &&
			  Map::map_arr[y_coords + 1][x_coords] == 2) ||
			 (dummyMovementCoords.first == 0 && dummyMovementCoords.second == 0 &&
			  (Map::map_arr[y_coords + 1][x_coords] == 2 || Map::map_arr[y_coords + 1][x_coords] == 3) &&
			  tag_obj == "enemy_ghost")) // down
	{
		int i = 1;
		for (; Map::map_arr[y_coords + i + 1][x_coords] == 2 || (Map::map_arr[y_coords + i + 1][x_coords] == 3 &&
																 tag_obj == "enemy_ghost");
			 i++)
		{
		}
		dummyMovementCoords = {(y_coords + i - y_coords) * 64, (x_coords - x_coords) * 64};
		prev_direction = "down";
	}
	else if ((dummyMovementCoords.first == 0 && dummyMovementCoords.second == 0 && prev_direction != "down" &&
			  Map::map_arr[y_coords][x_coords - 1] == 2) ||
			 (dummyMovementCoords.first == 0 && dummyMovementCoords.second == 0 &&
			  (Map::map_arr[y_coords][x_coords - 1] == 2 || Map::map_arr[y_coords][x_coords - 1] == 3) &&
			  tag_obj == "enemy_ghost")) // left
	{
		int i = 1;
		for (; Map::map_arr[y_coords][x_coords - i - 1] == 2 || (Map::map_arr[y_coords][x_coords - i - 1] == 3 &&
																 tag_obj == "enemy_ghost");
			 i++)
		{
		}
		dummyMovementCoords = {(y_coords - y_coords) * 64, (x_coords - i - x_coords) * 64};
		prev_direction = "left";
	}
}
void Enemy::transformPositionToTiles()
{
	en_dest_rect.x = destRect.x;
	en_dest_rect.y = destRect.y;
	int en_x = static_cast<int>(en_dest_rect.x / (32 * 2));
	int en_y = static_cast<int>(en_dest_rect.y / (32 * 2));
	//	en_dest_rect
	//	if (moveThroughFoundDummyPath())//if we are moving through the path, we dont need to further execute the code in this func
	//		return;
	findDummyPath({en_y, en_x});
}
