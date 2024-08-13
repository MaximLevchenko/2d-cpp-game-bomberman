#pragma once

#ifndef BOMBERMAN_ERRORHANDLER_H
#define BOMBERMAN_ERRORHANDLER_H
#include <SDL2/SDL.h>
#include <iostream>
/**
 * @brief
 * Function which prints exceptions in the SDL2 library to the console
 * @param msg message we want to print
 * */
void logSDLError(std::ostream &os, const std::string &msg);

#endif // BOMBERMAN_ERRORHANDLER_H
