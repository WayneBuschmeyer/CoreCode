#include "Core.h"

namespace
{
	// Static RNG setup (translation unit scope)
	static std::random_device rd;      // Seed source
	static std::mt19937 gen(rd());     // Mersenne Twister RNG
}

//Core.cpp
namespace Core
{
	// Function: rollDice
	// Rolls a specified number of dice and returns the results.
	std::vector<int> rollDice(int rollCount, int diceSides, int minValue)
	{
		// Validate input parameters
		if (diceSides < minValue or rollCount <= 0)
		{
			return {}; // Return an empty vector for invalid parameters
		}

		// Random number generator setup
		static std::random_device rd;            // Seed source
		static std::mt19937 gen(rd());           // Mersenne Twister RNG
		std::uniform_int_distribution<> dis(minValue, diceSides);

		// Preallocate the vector and fill it with rolls
		std::vector<int> Dicerolls(rollCount);
		for (int i = 0; i < rollCount; ++i)
		{
			Dicerolls[i] = dis(gen);
		}

		return Dicerolls;
	}//End of rollDice

	// Function: boonBaneRoll
	// Simulates rolling dice with adjustments for boons (advantages) and banes (disadvantages).
	std::vector<int> boonBaneRoll(int boons, int banes, int baseDiceCount, int diceSides, int minValue)
	{
		// Validate input parameters
		if (baseDiceCount <= 0 or diceSides <= 0 or minValue > diceSides)
		{
			return {}; // Return an empty vector for invalid parameters
		}

		// Calculate the total number of extra rolls caused by the imbalance between boons and banes.
		int extraRolls = std::abs(boons - banes);

		// The total number of dice to roll is the sum of base dice and any extra rolls.
		int totalRolls = baseDiceCount + extraRolls;

		// Generate all the required dice rolls.
		// The rollDice function is expected to return random numbers between minValue and diceSides.
		std::vector<int> Dicerolls = rollDice(totalRolls, diceSides, minValue);

		// If rollDice returns an empty vector, propagate the error.
		if (Dicerolls.empty())
		{
			return {}; // Invalid rolls due to invalid parameters in rollDice
		}

		// Prepare a vector to store the final selected rolls.
		// This will contain only the baseDiceCount rolls after processing boons/banes.
		std::vector<int> selectedRolls(baseDiceCount);

		if (boons > banes)
		{
			// When boons exceed banes, select the highest baseDiceCount rolls.
			// Use std::nth_element to partition the rolls so that the top rolls are at the front.
			std::nth_element(Dicerolls.begin(), Dicerolls.begin() + baseDiceCount, Dicerolls.end(),
				[](int a, int b) { return a > b; }); // Comparator ensures descending order.

			// Copy the highest rolls into the selectedRolls vector.
			std::copy(Dicerolls.begin(), Dicerolls.begin() + baseDiceCount, selectedRolls.begin());
		}
		else if (banes > boons)
		{
			// When banes exceed boons, select the lowest baseDiceCount rolls.
			// By default, std::nth_element arranges elements in ascending order.
			std::nth_element(Dicerolls.begin(), Dicerolls.begin() + baseDiceCount, Dicerolls.end());

			// Copy the lowest rolls into the selectedRolls vector.
			std::copy(Dicerolls.begin(), Dicerolls.begin() + baseDiceCount, selectedRolls.begin());
		}
		else
		{
			// When boons and banes cancel out, no adjustments are made to the rolls.
			// Simply take the first baseDiceCount rolls.
			std::copy(Dicerolls.begin(), Dicerolls.begin() + baseDiceCount, selectedRolls.begin());
		}

		// Return the processed rolls based on the boons and banes logic.
		return selectedRolls;
	}//End of boonBaneRoll
}//End of Namespace Core