#pragma once

#include <vector>
#include <algorithm>
#include <cmath>
#include <stdexcept>

//Core.h
namespace Core
{
	// Function: rollDice
	// Rolls a specified number of dice and returns the results.
	//
	// Parameters:
	// - rollCount: Number of dice to roll (e.g., 3 for 3dx). default is 1.
	// - diceSides: Number of sides on each die (e.g., 6 for a d6). default is 6.
	// - minValue: Minimum value each die can roll (default is 1). default is 1.
	//
	// Returns:
	// - A vector containing the results of the rolls, or an empty vector if the parameters are invalid.
	std::vector<int> rollDice(int rollCount = 1, int diceSides = 6, int minValue = 1);

	// Function: boonBaneRoll
	// Simulates rolling dice with adjustments for boons (advantages) and banes (disadvantages).
	//
	// Parameters:
	// - boons: Extra dice rolled, keeping the highest rolls. default is 0.
	// - banes: Extra dice rolled, keeping the lowest rolls. default is 0.
	// - baseDiceCount: Number of main dice rolled (e.g., 3d6 means 3 dice are rolled). default is 3.
	// - diceSides: Number of sides on each die (e.g., d6 has 6 sides). default is 6.
	// - minValue: Minimum value each die can roll (default is 1). default is 1.
	//
	// Returns:
	// - A vector containing the final selected rolls, or an empty vector if inputs are invalid.
	std::vector<int> boonBaneRoll(int boons = 0, int banes = 0, int baseDiceCount = 3, int diceSides = 6, int minValue = 1);
}//End of Namespace Core
