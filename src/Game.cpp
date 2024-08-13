#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Game.h"
#include "ErrorHandler.h"
#include "Player.h"
#include "Map.h"
#include "MapObject.h"
#include "CircleCollision.h"
#include "Enemy.h"
#include "EnemyOvapi.h"
#include "EnemyGhost.h"
#include "UiLabel.h"

using namespace std;

SDL_Renderer *Game::renderer = nullptr; // static variable
SDL_Event Game::event;					// static variable

int Map::map_arr[15][15];										   // static variable
std::vector<std::unique_ptr<GameObject>> Game::enemies;			   // static variable
std::vector<std::unique_ptr<MapObject>> Map::mapObjects;		   // static variable
std::vector<std::unique_ptr<MapObject>> Map::collidableMapObjects; // static variable
std::vector<std::unique_ptr<Flame>> Player::flames;				   // static variable
std::vector<std::unique_ptr<GameObject>> Game::bonuses;			   // static variable
std::vector<std::unique_ptr<GameObject>> Game::players;			   // static variable
// std::vector<std::unique_ptr<GameObject>> Game::labels;			   // static variable

unique_ptr<Map> map1;
unique_ptr<UiLabel> label1_bomb_count;
unique_ptr<UiLabel> label2_bomb_count;
unique_ptr<UiLabel> label1_score;
unique_ptr<UiLabel> label2_score;
void Game::getUserInput()
{
	size_t gameMode;
	cout << "-------------------------------------------------------------" << endl;
	std::cout << "Choose your game mode " << endl;
	std::cout << "0:  Single-Player " << endl;
	std::cout << "1:  Multi-Player " << endl;
	std::cout << "2:  Exit The Game " << endl;
	cout << "-------------------------------------------------------------" << endl;

	while (true)
	{
		cin >> gameMode;
		if (cin.eof())
		{
			//      this->clean();
			throw std::invalid_argument("EOF");
			;
		}
		if (cin.good() && (gameMode == 0 || gameMode == 1 || gameMode == 2))
			break;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cerr << "Invalid input of gameMode, try typing 0 for single-player, or 1 for multi-player." << endl;
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << endl;
	switch (gameMode)
	{
	case 0:
		singlePlayer = true;
		multiPlayer = false;
		break;
	case 1:
		multiPlayer = true;
		singlePlayer = false;
		break;
	case 2:
		continueGame = false;
		isRunning = false;
		cout << "!!!!!!!!!!!!----------------         ----------------!!!!!!!!!!!!" << endl;
		cout << endl;
		cout << "Thank You For Playing The Game" << endl;
		cout << endl;
		cout << "!!!!!!!!!!!!----------------         ----------------!!!!!!!!!!!!" << endl;
		isRunning = false;
		break;
	default:
		break;
	}
}
void Game::initGame(const char *p_name, int p_xPos, int p_Ypos, int p_w, int p_h, bool fullscreen)
{
	//===================================================== when restarting the game, we should clear all containers
	while (!enemies.empty()) // detecting if game has restarted
	{
		enemies.erase(enemies.begin());
	}
	while (!players.empty())
	{
		players.erase(players.begin());
	}
	while (!Map::mapObjects.empty())
	{
		Map::mapObjects.erase(Map::mapObjects.begin());
	}
	while (!Map::collidableMapObjects.empty())
	{
		Map::collidableMapObjects.erase(Map::collidableMapObjects.begin());
	}
	while (!bonuses.empty())
	{
		bonuses.erase(bonuses.begin());
	}
	while (!Player::flames.empty())
	{
		Player::flames.erase(Player::flames.begin());
	}
	//=====================================================

	Uint32 flags = 0;

	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		logSDLError(cout, "SDL_INIT");
		isRunning = false; // Game.h variable for detecting whether to continue main cycle or not
	}
	if (!IMG_Init(IMG_INIT_PNG))
	{
		logSDLError(cout, "IMG_Init");
		isRunning = false;
	}
	if (TTF_Init() == -1)
	{
		logSDLError(cout, "TTF_Init");
		isRunning = false;
	}
	window = SDL_CreateWindow(p_name, p_xPos, p_Ypos, p_w, p_h, flags);
	if (window == nullptr)
	{
		logSDLError(cout, "SDL_CreateWindow");
		isRunning = false;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		logSDLError(cout, "SDL_CreateRenderer");
		isRunning = false;
	}
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // setting color to white
	//==========================================================================
	isRunning = true;
	//================================always happens
	map1 = make_unique<Map>();
	map1->initialize();
	map1->loadMap("src/assets/dev/15x15_test.map", 15, 15);

	SDL_Color white = {255, 255, 255, 255};
	label1_bomb_count = make_unique<UiLabel>(90, 10, "P1 bomb count:", "arial", white, "src/assets/fonts/BoyzRGrossNF.ttf");
	label1_score = make_unique<UiLabel>(90, 880, "P1 score:", "arial", white, "src/assets/fonts/BoyzRGrossNF.ttf");

	//================================always happens
	unique_ptr<Player> player;
	player = make_unique<Player>("src/assets/images/bomberman.png", 32 * 2, 32 * 3, "player1");
	players.emplace_back(move(player));
	if (singlePlayer)
	{
		enemies.emplace_back(
			make_unique<EnemyOvapi>("src/assets/images/enemy_ovapi.png", 32 * 12, 32 * 3,
									"enemy_ovapi")); // 32*12, 32*3
		enemies.emplace_back(
			make_unique<Enemy>("src/assets/images/enemy_common.png", 32 * 12, 32 * 11,
							   "enemy")); //
		enemies.emplace_back(
			make_unique<EnemyGhost>("src/assets/images/enemy_ghost.png", 32 * 12, 32 * 11,
									"enemy_ghost")); //
		enemies.emplace_back(
			make_unique<EnemyGhost>("src/assets/images/enemy_ghost.png", 32 * 2, 32 * 8,
									"enemy_ghost")); //
	}
	else if (multiPlayer)
	{
		label2_bomb_count = make_unique<UiLabel>(660, 10, "P2 bomb count:", "arial", white, "src/assets/fonts/BoyzRGrossNF.ttf");
		label2_score = make_unique<UiLabel>(660, 880, "P2 score:", "arial", white, "src/assets/fonts/BoyzRGrossNF.ttf");
		unique_ptr<Player> player2 = make_unique<Player>("src/assets/images/bomberman2.png", 32 * 12, 32 * 3,
														 "player2");
		players.emplace_back(move(player2));
	}
	isRunning = true;
}

void Game::handleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}
void Game::checkForHighScore(size_t current_score)
{
	string filename("src/assets/dev/highScore.txt");
	size_t highScore;
	fstream file(filename);
	if (!file.is_open())
		cerr << "Could not open the file - '"
			 << filename << "'" << endl;
	file >> highScore;
	file.close();

	ofstream file_output(filename);
	if (current_score > highScore)
	{
		file_output << current_score;
		cout << "NEW HIGH SCORE" << endl;
	}
	else
	{
		cout << "HIGH SCORE IS: " << highScore << endl;
		file_output << highScore;
	}
	cout
		<< endl;
	file_output.close();
}
void Game::congratulateWinner()
{
	cout << "!!!!!!!!!!!!----------------GAME OVER----------------!!!!!!!!!!!!" << endl;
	cout << endl;
	if (multiPlayer)
	{
		checkForHighScore(players[0]->currentScore);
		cout << players[0]->tag_obj << " won, "
			 << "score is: " << players[0]->currentScore << endl;
	}
	if (singlePlayer)
	{
		if (!players.empty())
		{
			checkForHighScore(players[0]->currentScore);
			cout << "Player won, "
				 << "score is " << players[0]->currentScore << endl;
		}

		else if (enemies.size() == 1)
			cout << enemies[0]->tag_obj << " won " << endl;
		else
			cout << " Enemies won " << endl;
	}
	cout << endl;
	cout << "!!!!!!!!!!!!----------------         ----------------!!!!!!!!!!!!" << endl;
	isRunning = false;
	SDL_Delay(500); // wait a lil bit
}
void Game::declareATie()
{
	if (singlePlayer)
	{
		cout << "!!!!!!!!!!!!----------------GAME OVER----------------!!!!!!!!!!!!" << endl;

		cout << endl;
		cout << "No one has won, both you and an enemy died at the same time" << endl;
		cout << endl;
		cout << "!!!!!!!!!!!!----------------         ----------------!!!!!!!!!!!!" << endl;
		isRunning = false;
	}
	if (multiPlayer)
	{
		cout << "!!!!!!!!!!!!----------------GAME OVER----------------!!!!!!!!!!!!" << endl;
		cout << endl;
		cout << "No one has won, both players died at the same time" << endl;
		cout << endl;
		cout << "!!!!!!!!!!!!----------------         ----------------!!!!!!!!!!!!" << endl;
	}
	isRunning = false;
}
bool Game::isGameFinished()
{
	if (multiPlayer)
	{
		if (players.size() == 1) // gameObjects
		{
			congratulateWinner(); // player1 or player2
			return true;
		}
		else if (players.size() == 0) // players were simultaneously exploded by the bomb   //gameObjects
		{
			declareATie();
			return true;
		}
	}
	if (singlePlayer)
	{
		if ((enemies.size() > 0 && players.empty()) || (enemies.empty() && players.size() == 1))
		{
			congratulateWinner(); // player or enemy
			return true;
		}
		else if (enemies.empty() && players.empty()) // player and the enemy were simultaneously exploded by the bomb
		{
			declareATie();
			return true;
		}
	}
	return false;
}
void Game::getTextForLabel1(stringstream &ss, std::string tag)
{
	if (tag == "bomb1")
		for (auto const &obj : Game::players)
		{
			if (obj->tag_obj == "player1")
				ss << "P1 Bombs: " << obj->bombCount;
		}
	else if (tag == "bomb2")
		for (auto const &obj : Game::players)
		{
			if (obj->tag_obj == "player2")
				ss << "P2 Bombs: " << obj->bombCount;
		}
	else if (tag == "score1")
		for (auto const &obj : Game::players)
		{
			if (obj->tag_obj == "player1")
				ss << "P1 Score: " << obj->currentScore;
		}
	else if (tag == "score2")
		for (auto const &obj : Game::players)
		{
			if (obj->tag_obj == "player2")
				ss << "P2 Score: " << obj->currentScore;
		}
}
void Game::update()
{

	Player::flames.erase(remove_if(begin(Player::flames), end(Player::flames),
								   [](const unique_ptr<Flame> &mFlame)
								   {
									   return !mFlame->isAlive;
								   }),
						 end(Player::flames));

	Game::enemies.erase(remove_if(begin(Game::enemies), end(Game::enemies),
								  [](const unique_ptr<GameObject> &mObj)
								  {
									  return !mObj->isAlive;
								  }),
						end(Game::enemies));
	Game::players.erase(remove_if(begin(Game::players), end(Game::players),
								  [](const unique_ptr<GameObject> &mPlayer)
								  {
									  return !mPlayer->isAlive;
								  }),
						end(Game::players));
	if (isGameFinished()) // check whether game has finished or not
		return;

	for (const auto &obj : Game::enemies)
	{
		obj->update();
	}
	for (const auto &obj : Game::players)
	{
		obj->update();
	}
	for (const auto &flame : Player::flames) // collision between flames and enemies/players
	{
		for (const auto &obj : Game::enemies)
		{
			if (CollisionManager::checkCollision(flame->destRect, obj->destRect))
			{
				obj->isAlive = false; // if there is a collision between an enemy and the flame
			}
		}
		for (const auto &pl : Game::players)
		{
			if (CollisionManager::checkCollision(flame->destRect, pl->destRect))
			{
				//
				pl->isAlive = false; // if there is a collision between flame and the player
			}
		}
	}
	for (const auto &pl : Game::players) // collision between enemies and player
	{
		for (const auto &en : Game::enemies)
		{
			if (CollisionManager::checkCollision(pl->destRect, en->destRect))
			{
				//
				pl->isAlive = false; // if there is a collision between flame and the player
			}
		}
	}
	stringstream ss;
	getTextForLabel1(ss, "bomb1");
	label1_bomb_count->setLabelText(ss.str(), "arial");
	ss.str(std::string());
	getTextForLabel1(ss, "score1");
	label1_score->setLabelText(ss.str(), "arial");
	ss.str(std::string());
	if (multiPlayer)
	{
		getTextForLabel1(ss, "bomb2");
		label2_bomb_count->setLabelText(ss.str(), "arial");
		ss.str(std::string());
		getTextForLabel1(ss, "score2");
		label2_score->setLabelText(ss.str(), "arial");
		ss.str(std::string());
	}
}
void Game::render()
{
	SDL_RenderClear(renderer);
	for (const auto &obj : Map::mapObjects)
	{
		obj->draw();
	}
	for (const auto &obj : Game::bonuses)
	{
		obj->draw();
	}
	for (const auto &obj : Game::enemies)
	{
		obj->draw();
	}
	for (const auto &obj : Game::players)
	{
		obj->draw();
	}
	label1_bomb_count->draw();
	label1_score->draw();
	if (multiPlayer)
	{
		label2_bomb_count->draw();
		label2_score->draw();
	}

	SDL_RenderPresent(renderer);
}
void Game::clean()
{

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	if (!continueGame)
		SDL_QUIT;
	//  cout << "Thanks for playing the game" << endl;
}