#pragma once

#ifndef BOMBERMAN_RANDOMNUMBERGENERATOR_H
#define BOMBERMAN_RANDOMNUMBERGENERATOR_H

#include <random>
#include <iostream>

static bool randomGenerate(int begin_range, int end_range, int percentage)
{
	std::random_device rd;										   // obtain a random number from hardware
	std::mt19937 gen(rd());										   // seed the generator
	std::uniform_int_distribution<> distr(begin_range, end_range); // define the range

	if (distr(gen) <= percentage)
		return true;
	else
		return false;
}
#endif // BOMBERMAN_RANDOMNUMBERGENERATOR_H
