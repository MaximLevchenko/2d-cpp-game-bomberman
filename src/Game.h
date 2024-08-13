#pragma once
#ifndef BOMBERMAN_GAME_H
#define BOMBERMAN_GAME_H

#include <vector>
#include <memory>
#include <algorithm>
#include <sstream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "GameObject.h"
#include "Game.h"
// #include "Player.h"
// class UiLabel;

class Player;

/**
 * @brief
 * Forward declaration of the Bomb class to avoid circular dependencies issues
 * */
class Bomb;

/**
 * @brief
 * Manages whole process of the game. Updates, renders, clears all objects in the game
 * */
class Game
{
public:
	Game() = default;
	~Game() noexcept = default;
	/**
	 * @brief
	 * Initializes a new game
	 * @param p_name name of our program
	 * @param p_Xpos x-axis position of window initialization
	 * @param p_Ypos y-axis position of window initialization
	 * @param fullscreen true if we want our game to be fullscreen, false otherwise
	 * */
	void initGame(const char *p_name, int p_xPos, int p_Ypos, int p_w, int p_h, bool fullscreen);
	/**
	 * @brief
	 * Handles SDL_QUIT event
	 * */
	void handleEvents();
	/**
	 * @brief
	 * Updates all objects in the game
	 * */
	void update();
	/**
	 * @brief
	 * Renders all objects in the game
	 * */
	void render();
	/**
	 * @brief
	 * Destroys the renderer and game-window
	 * */
	void clean();
	/**
	 * @brief
	 * Check if game is still running
	 * @param isRunning variable which tells if our game loop should be continued or not
	 * */
	bool running() const { return isRunning; }
	//	bool firstMapDrawing;

	/**
	 * @brief
	 * Reads an input from the user. Main menu
	 * */
	void getUserInput();
	/**
	 * @brief
	 * Congratulates a winner of a game
	 * */
	void congratulateWinner();
	/**
	 * @brief
	 * Check if we should close our program
	 * */
	bool isGameFinished();
	/**
	 * @brief
	 * Declares a tie
	 * */
	void declareATie();
	/**
	 * @brief
	 *  Compare current score to the highest score. If current score is bigger, then rewrite highScore.txt file
	 * */
	void checkForHighScore(size_t score);
	void getTextForLabel1(std::stringstream &ss, std::string tag);
	bool singlePlayer = false;
	bool multiPlayer = false;
	bool continueGame = true;
	bool isRunning = true;
	static SDL_Renderer *renderer;
	static SDL_Event event;
#define USE_FANCYPANTS
#ifdef USE_FANCYPANTS
	static std::vector<std::unique_ptr<GameObject>> enemies;
	static std::vector<std::unique_ptr<GameObject>> bonuses;
	static std::vector<std::unique_ptr<GameObject>> players;
	// static std::vector<std::unique_ptr<GameObject>> labels;

#endif
private:
	SDL_Window *window{};
};

#endif // BOMBERMAN_GAME_H
