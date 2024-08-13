#include "Map.h"
#include "Game.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

Map::Map()
{
}
Map::~Map()
{
}
void Map::loadMap(const std::string &filename, int sizeX, int sizeY)
{
	//	cout<<Map::map_arr[0][0];
	ifstream numbers;
	string line;
	// int num;
	std::string s;

	numbers.open(filename);

	if (!(numbers))
		cout << "error: file could not be read." << endl;

	for (int i = 0; i < sizeX; i++)
	{
		std::getline(numbers, s);
		std::istringstream iss(s);
		SDL_Texture *tempTex;
		std::string num;
		int j_counter = 0;
		while (getline(iss, num, ','))
		{
			Map::map_arr[i][j_counter] = stoi(num);
			switch (stoi(num))
			{
			case 0:
				tempTex = texture_background;
				//        filename = "../src/assets/images/dirt.png";
				break;
			case 1:
				tempTex = texture_unbr_wall;
				//        filename = "../src/assets/images/grass.png";
				break;
			case 2:
				tempTex = texture_walk_tile;
				break;
			case 3:
				tempTex = texture_wall;
				break;
				//        filename = "../src/assets/images/water.png";
			default:
				cout << "smth with the file" << endl;
				break;
			}
			addTile(tempTex, stoi(num), j_counter * 32, i * 32);
			j_counter++;
		}
	}
}

void Map::addTile(SDL_Texture *p_tex, int p_tileId, int p_x, int p_y)
{
	mapObjects.emplace_back(
		std::make_unique<MapObject>(p_tex, p_tileId, static_cast<int>(p_x), static_cast<int>(p_y), 32, 32));
	if (p_tileId == 1 || p_tileId == 3)
		collidableMapObjects.emplace_back(
			make_unique<MapObject>(p_tex, p_tileId, static_cast<int>(p_x), static_cast<int>(p_y), 32, 32, "collidable"));
}
