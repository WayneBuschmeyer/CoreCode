#pragma once

#include <vector>
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <random>

//Core.h
namespace Core
{
	// Constants for default values
	constexpr int DEFAULT_ROLL_COUNT = 1;      // Default number of dice to roll
	constexpr int DEFAULT_DICE_SIDES = 6;     // Default number of sides on each die
	constexpr int DEFAULT_MIN_VALUE = 1;      // Default minimum value a die can roll
	constexpr int DEFAULT_BOONS = 0;          // Default number of boons
	constexpr int DEFAULT_BANES = 0;          // Default number of banes
	constexpr int DEFAULT_BASE_DICE_COUNT = 3; // Default base number of dice to roll

	// Function: rollDice
	// Rolls a specified number of dice and returns the results.
	//
	// Parameters:
	// - rollCount: Number of dice to roll (default: DEFAULT_ROLL_COUNT).
	// - diceSides: Number of sides on each die (default: DEFAULT_DICE_SIDES).
	// - minValue: Minimum value each die can roll (default: DEFAULT_MIN_VALUE).
	//
	// Returns:
	// - A vector containing the results of the rolls, or an empty vector if the parameters are invalid.
	std::vector<int> rollDice(int rollCount = DEFAULT_ROLL_COUNT, int diceSides = DEFAULT_DICE_SIDES, int minValue = DEFAULT_MIN_VALUE);

	// Function: boonBaneRoll
	// Simulates rolling dice with adjustments for boons (advantages) and banes (disadvantages).
	//
	// Parameters:
	// - boons: Extra dice rolled, keeping the highest rolls (default: DEFAULT_BOONS).
	// - banes: Extra dice rolled, keeping the lowest rolls (default: DEFAULT_BANES).
	// - baseDiceCount: Number of main dice rolled (default: DEFAULT_BASE_DICE_COUNT).
	// - diceSides: Number of sides on each die (default: DEFAULT_DICE_SIDES).
	// - minValue: Minimum value each die can roll (default: DEFAULT_MIN_VALUE).
	//
	// Returns:
	// - A vector containing the final selected rolls, or an empty vector if inputs are invalid.
	std::vector<int> boonBaneRoll(int boons = DEFAULT_BOONS, int banes = DEFAULT_BANES, int baseDiceCount = DEFAULT_BASE_DICE_COUNT, int diceSides = DEFAULT_DICE_SIDES, int minValue = DEFAULT_MIN_VALUE);
}//End of Namespace Core
