//
// Created by User win 10 on 31.05.2022.
//
#include <cmath>
#include <algorithm>

#include "Player.h"
#include "TextureManager.h"
//#include "Map.h"
#include "Bomb.h"

static const int MAX_FLAME_RANGE = 10;
static const int MAX_SPEED = 5;

// vector<unique_ptr<Flame>> Player::flames;

SDL_Texture *Map::texture_bonus_bomb;
SDL_Texture *Map::texture_bonus_speed;
SDL_Texture *Map::texture_bonus_flame;

// size_t Player::currentScore;

Player::Player(const char *filename)
{
	keyboardController.transform.position.zero();
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = 32;
	srcRect.h = 32;
	setTex(filename);
}
Player::Player(const char *filename, int x, int y, string p_tag_obj)
{
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = 32;
	srcRect.h = 32;
	keyboardController.transform.position.zero();

	destRect.x = x * 2;
	destRect.y = y * 2;
	destRect.w = 32 * keyboardController.transform.scale;
	destRect.h = 32 * keyboardController.transform.scale;
	position.x = x * 2;
	position.y = y * 2;
	keyboardController.transform.scale = 1.5f;

	keyboardController.player_tag = p_tag_obj;

	setTex(filename);
	tag_obj = p_tag_obj;

	bombCount = 1;
}
// sets texture
void Player::setTex(const char *p_filename)
{
	texture = TextureManager::loadTexture(p_filename);
}
// places bomb on the map
void Player::placeBomb()
{
	for (auto const &b : bombContainer)
	{
		if (b->index_map.first == destRect.x / 64 && b->index_map.second == destRect.y / 64)
		{
			return;
		}
	}
	bombCount--;
	bombContainer.emplace_back(make_unique<Bomb>(make_pair(destRect.x / 64, destRect.y / 64)));
}
// check if there is a breakable wall on the coords
bool Player::isWallOnTile(int y_coord, int x_coord, int id_tile)
{
	return Map::map_arr[y_coord][x_coord] == id_tile;
}
// this function is being invoked only when isWallOnTile returned true. Changes map_arrays according to bomb explosions
void Player::changeMapArrayAndMapObject(int y_coord, int x_coord, int y_resolution, SDL_Texture *p_texture)
{
	auto it = Map::collidableMapObjects.begin();
	for (auto const &m_obj : Map::collidableMapObjects)
	{
		if (m_obj->destRect.x == x_coord * 64 && m_obj->destRect.y == y_coord * 64)
		{
			// finding that object in all map objects and changing its id and texture
			Map::collidableMapObjects.erase(it);
			Map::mapObjects.at(x_coord + y_resolution * (y_coord))->tileId = 2;
			Map::mapObjects.at(x_coord + y_resolution * (y_coord))->texture = p_texture;
			break;
		}
		++it;
	}
	Map::map_arr[y_coord][x_coord] = 2;
	if (randomGenerate(0, 100, 50)) // 50 percent chance to drop smth
	{
		string bonus_tag;
		SDL_Texture *temp_texture;
		BonusType bonusType = BonusType(rand() % 3);
		switch (bonusType)
		{
		case 0:
			temp_texture = Map::texture_bonus_bomb;
			bonus_tag = "bonus_bomb";
			// currentScore += 400;

			break;
		case 1:
			temp_texture = Map::texture_bonus_flame;
			bonus_tag = "bonus_flame";
			// currentScore += 300;

			break;
		case 2:
			temp_texture = Map::texture_bonus_speed;
			bonus_tag = "bonus_speed";
			// currentScore += 500;

			break;
		default:
			break;
		}
		Game::bonuses.emplace_back(make_unique<Bonus>(x_coord, y_coord, temp_texture, bonus_tag));
		//		cout << bonusType << endl;
	}

	//	BonusType c = a
	//	Color color = Color(rand()%3);
}

void Player::explodeBomb(unique_ptr<Bomb> &bomb)
{
	SDL_Texture *walk_tile = TextureManager::loadTexture("src/assets/images/walk_tile.png");
	SDL_Texture *tex_flames = TextureManager::loadTexture("src/assets/images/flames.png");

	int y_resolution = 15;
	int x_coord = bomb->index_map.first;
	int y_coord = bomb->index_map.second;
	bool destroyedUp = false, destroyedRight = false, destroyedDown = false, destroyedLeft = false;
	for (int i = 0; i <= flameRange; i++)
	{
		if (isWallOnTile(y_coord - i, x_coord, 3) && !destroyedUp) // up
		{
			changeMapArrayAndMapObject(y_coord - i, x_coord, y_resolution, walk_tile);
			flames.emplace_back(make_unique<Flame>(tex_flames, x_coord * 32, (y_coord - i) * 32, 32, 32, "flame"));
			destroyedUp = true;
		}
		else if (isWallOnTile(y_coord - i, x_coord, 1) && !destroyedUp) // up
			destroyedUp = true;
		else if (isWallOnTile(y_coord - i, x_coord, 2) &&
				 !destroyedUp) // 32 because scale of 2 is already defined in the constructor of MapObject
		{
			flames.emplace_back(make_unique<Flame>(tex_flames, x_coord * 32, (y_coord - i) * 32, 32, 32, "flame"));
		}
		if (isWallOnTile(y_coord, x_coord + i, 3) && !destroyedRight) // right
		{
			changeMapArrayAndMapObject(y_coord, x_coord + i, y_resolution, walk_tile);
			flames.emplace_back(make_unique<Flame>(tex_flames, (x_coord + i) * 32, (y_coord)*32, 32, 32, "flame"));
			destroyedRight = true;
		}
		else if (isWallOnTile(y_coord, x_coord + i, 1) && !destroyedRight) // right
			destroyedRight = true;
		else if (isWallOnTile(y_coord, x_coord + i, 2) &&
				 !destroyedRight) // 32 because scale of 2 is already defined in the constructor of MapObject
		{
			flames.emplace_back(make_unique<Flame>(tex_flames, (x_coord + i) * 32, (y_coord)*32, 32, 32, "flame"));
		}

		if (isWallOnTile(y_coord + i, x_coord, 3) && !destroyedDown) // down
		{
			changeMapArrayAndMapObject(y_coord + i, x_coord, y_resolution, walk_tile);
			flames.emplace_back(make_unique<Flame>(tex_flames, x_coord * 32, (y_coord + i) * 32, 32, 32, "flame"));
			destroyedDown = true;
		}
		else if (isWallOnTile(y_coord + i, x_coord, 1) && !destroyedDown) // down
			destroyedDown = true;
		else if (isWallOnTile(y_coord + i, x_coord, 2) &&
				 !destroyedDown) // 32 because scale of 2 is already defined in the constructor of MapObject
		{
			flames.emplace_back(make_unique<Flame>(tex_flames, x_coord * 32, (y_coord + i) * 32, 32, 32, "flame"));
		}

		if (isWallOnTile(y_coord, x_coord - i, 3) && !destroyedLeft) // left
		{
			changeMapArrayAndMapObject(y_coord, x_coord - i, y_resolution, walk_tile);
			flames.emplace_back(make_unique<Flame>(tex_flames, (x_coord - i) * 32, (y_coord)*32, 32, 32, "flame"));
			destroyedLeft = true;
		}
		else if (isWallOnTile(y_coord, x_coord - i, 1) && !destroyedLeft) // left
			destroyedLeft = true;
		else if (isWallOnTile(y_coord, x_coord - i, 2) &&
				 !destroyedLeft) // 32 because scale of 2 is already defined in the constructor of MapObject
		{
			flames.emplace_back(make_unique<Flame>(tex_flames, (x_coord - i) * 32, (y_coord)*32, 32, 32, "flame"));
		}
	}
	bombCount++;
	// cout << "Bombs left: " << bombCount << endl;
}

void Player::update()
{
	for (auto const &pl : Game::players)
	{
		for (auto const &bonus : Game::bonuses)
		{
			if (CollisionManager::checkCollision(pl->destRect, bonus->destRect))
			{
				if (bonus->tag_obj == "bonus_bomb")
					pl->currentScore += 300;
				else if (bonus->tag_obj == "bonus_flame")
					pl->currentScore += 400;
				else if (bonus->tag_obj == "bonus_speed")
					pl->currentScore += 300;
			}
		}
	}
	// increase flameRange by 1 every 1o secs of the game
	if (flameIncreaseCounter++ && flameIncreaseCounter % (60 * 10) == 0)
	{
		flameIncreaseCounter = 0;
		if (flameRange <= MAX_FLAME_RANGE)
			this->flameRange += 1;
		flameIncreaseCounter++;
	}
	keyboardController.handleUserInput(); // handling user input

	// vector2D for storing previous value of our position to make proper collision
	Vector2D temp_pos;
	SDL_Rect temp_rect;
	temp_pos.x = position.x;
	temp_pos.y = position.y;
	temp_rect.x = static_cast<int>(position.x);
	temp_rect.y = static_cast<int>(position.y);
	temp_rect.w = keyboardController.transform.width * keyboardController.transform.scale;
	temp_rect.h = keyboardController.transform.height * keyboardController.transform.scale;

	if (keyboardController.direction == 4)
	{
		keyboardController.transform.velocity.x = 0;
		keyboardController.transform.velocity.y = 0;
	}
	if (keyboardController.tag == "bomb_placed" && bombCount > 0)
	{
		placeBomb();
		// cout << "Bombs left: " << bombCount << endl;
		bombIsPlaced = true;
	}

	else if (keyboardController.direction == 0)
	{
		temp_rect.y -= keyboardController.transform.speed + 1;
		for (const auto &map_obj : Map::collidableMapObjects)
		{
			//			CollisionManager::checkCollision(temp_rect, map_obj->destRect);
			if (CollisionManager::checkCollision(temp_rect, map_obj->destRect))
			{
				//				cout << "UP" << endl;
				keyboardController.transform.velocity.y = 0;
			}
		}
	}
	else if (keyboardController.direction == 1)
	{
		temp_rect.x -= keyboardController.transform.speed + 1;
		for (const auto &map_obj : Map::collidableMapObjects)
		{
			if (CollisionManager::checkCollision(temp_rect, map_obj->destRect))
			{
				//				cout << "LEFT" << endl;
				keyboardController.transform.velocity.x = 0;
			}
		}
	}
	else if (keyboardController.direction == 2)
	{
		temp_rect.y += keyboardController.transform.speed + 1;
		for (const auto &map_obj : Map::collidableMapObjects)
		{
			if (CollisionManager::checkCollision(temp_rect, map_obj->destRect))
			{
				//				cout << "DOWN" << endl;
				keyboardController.transform.velocity.y = 0;
			}
		}
	}
	else
	{
		temp_rect.x += keyboardController.transform.speed + 1;
		for (const auto &map_obj : Map::collidableMapObjects)
		{
			if (CollisionManager::checkCollision(temp_rect, map_obj->destRect))
			{
				//				cout << "RIGHT" << endl;
				keyboardController.transform.velocity.x = 0;
			}
		}
	}
	//===================================== calculating a position
	position.y += keyboardController.transform.velocity.y * keyboardController.transform.speed;
	position.x += keyboardController.transform.velocity.x * keyboardController.transform.speed;
	//===================================== calculating a position

	//===================================== turning position into rectangular
	destRect.x = static_cast<int>(position.x); // destRect and srcRect are defined in GameObject
	destRect.y = static_cast<int>(position.y);
	destRect.w = (keyboardController.transform.width) * keyboardController.transform.scale;
	destRect.h = (keyboardController.transform.height) * keyboardController.transform.scale;

	//====================================================== managing bomb explosions
	auto it = bombContainer.begin();
	for (auto &b : bombContainer)
	{
		if (!b->isAlive)
		{
			explodeBomb(b);			 // explode the bomb
			bombContainer.erase(it); // erase it from the vector after exploding
			it = bombContainer.begin();
			break;
		}
		else
		{
			b->update();
			++it;
		}
	}
	//====================================================== managing bomb explosions

	//====================================================== managing flames
	for (auto const &f : flames)
		f->update();
	flames.erase(remove_if(begin(flames), end(flames),
						   [](const unique_ptr<Flame> &mFlame)
						   {
							   return !mFlame->isAlive;
						   }),
				 end(flames));
	//====================================================== managing flames

	//====================================================== managing bonuses

	Game::bonuses.erase(remove_if(begin(Game::bonuses), end(Game::bonuses),
								  [](const unique_ptr<GameObject> &mBonus)
								  {
									  return !mBonus->isAlive;
								  }),
						end(Game::bonuses));
	for (const auto &b : Game::bonuses) // collision between bonuses and player1
	{
		if ((this->tag_obj == "player1" || this->tag_obj == "player2") &&
			CollisionManager::checkCollision(b->destRect, this->destRect))
		{
			this->addEffect(b->tag_obj);
			//			cout << "player hit: " << b->tag_obj
			//			     << endl;//TODO: if tag_obj =="player1"&&gameMode = singleplayer ---> gameOver;
			b->isAlive = false;
		}
	}
	//====================================================== managing flames
}
void Player::addEffect(string p_tag_bonus)
{
	if (p_tag_bonus == "bonus_bomb")
		this->bombCount += 1;
	else if (p_tag_bonus == "bonus_speed" && this->keyboardController.transform.speed < MAX_SPEED)
		this->keyboardController.transform.speed += 0.5f;
	else if (this->flameRange < MAX_FLAME_RANGE)
		this->flameRange++;
}
void Player::draw()
{
	for (auto const &b : bombContainer)
		TextureManager::draw(b->texture, b->srcRect, b->destRect);
	for (auto const &f : flames)
		TextureManager::draw(f->texture, f->srcRect, f->destRect);
	TextureManager::draw(texture, srcRect, destRect);
}
