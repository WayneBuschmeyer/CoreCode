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

		// Random number
		std::uniform_int_distribution<> dis(minValue, diceSides);

		// Preallocate the vector and fill it with rolls
		std::vector<int> Dicerolls(rollCount);
		for (int i = 0; i < rollCount; ++i)
		{
			Dicerolls[i] = dis(gen);
		}

		return Dicerolls;
	}//End of rollDice

	 // Function: skillRoll
	// Performs a skill roll, including adjustments for boons and banes.
	SkillRollResult skillRoll(int skillLevel, int boons, int banes, int baseDiceCount, int diceSides, int minValue)
	{
		// Validate input parameters
		if (baseDiceCount <= 0 or diceSides <= 0 or minValue > diceSides)
		{
			return { skillLevel, {}, false, false }; // Invalid roll
		}

		// Calculate the total number of extra rolls caused by the imbalance between boons and banes.
		int extraRolls = std::abs(boons - banes);

		// The total number of dice to roll is the sum of base dice and any extra rolls.
		int totalRolls = baseDiceCount + extraRolls;

		// Generate all the required dice rolls.
		std::vector<int> Dicerolls = rollDice(totalRolls, diceSides, minValue);

		// If rollDice returns an empty vector, propagate the error.
		if (Dicerolls.empty())
		{
			return { skillLevel, {}, false, false }; // Invalid roll
		}

		// Prepare a vector to store the final selected rolls.
		std::vector<int> selectedRolls(baseDiceCount);

		if (boons > banes)
		{
			// When boons exceed banes, select the highest baseDiceCount rolls.
			std::nth_element(Dicerolls.begin(), Dicerolls.begin() + baseDiceCount, Dicerolls.end(),
				[](int a, int b) { return a > b; });

			std::copy(Dicerolls.begin(), Dicerolls.begin() + baseDiceCount, selectedRolls.begin());
		}
		else if (banes > boons)
		{
			// When banes exceed boons, select the lowest baseDiceCount rolls.
			std::nth_element(Dicerolls.begin(), Dicerolls.begin() + baseDiceCount, Dicerolls.end());

			std::copy(Dicerolls.begin(), Dicerolls.begin() + baseDiceCount, selectedRolls.begin());
		}
		else
		{
			// When boons and banes cancel out, no adjustments are made to the rolls.
			std::copy(Dicerolls.begin(), Dicerolls.begin() + baseDiceCount, selectedRolls.begin());
		}

		// Check for critical success or failure
		bool critSuccess = std::all_of(selectedRolls.begin(), selectedRolls.end(), [diceSides](int roll) { return roll == diceSides; });
		bool critFailure = std::all_of(selectedRolls.begin(), selectedRolls.end(), [minValue](int roll) { return roll == minValue; });

		// Calculate the total roll including the skill level.
		int total = std::accumulate(selectedRolls.begin(), selectedRolls.end(), skillLevel);

		// Return the result structure.
		return { total, selectedRolls, critSuccess, critFailure };
	}//End of skillRoll

	// Function: opposedRoll
	// Performs an opposed roll between two contestants.
	OpposedRollResult Core::opposedRoll(int attackerSkillLevel, int defenderSkillLevel,
		int attackerBoons, int attackerBanes,
		int defenderBoons, int defenderBanes,
		int baseDiceCount, int diceSides, int minValue)
	{
		// Perform skill rolls for both contestants
		SkillRollResult attackerResult = skillRoll(attackerSkillLevel, attackerBoons, attackerBanes, baseDiceCount, diceSides, minValue);
		SkillRollResult defenderResult = skillRoll(defenderSkillLevel, defenderBoons, defenderBanes, baseDiceCount, diceSides, minValue);

		// Initialize result variables
		Winner winner = Winner::TIE;
		int degree = 0;
		bool critWin = false;
		bool critLoss = false;

		// Determine winner based on totals
		if (attackerResult.total > defenderResult.total)
		{
			winner = Winner::ATTACKER;
		}
		else if (defenderResult.total > attackerResult.total)
		{
			winner = Winner::DEFENDER;
		}
		else
		{
			// If totals are the same, compare skill levels
			if (attackerSkillLevel > defenderSkillLevel)
			{
				winner = Winner::ATTACKER;
			}
			else if (defenderSkillLevel > attackerSkillLevel)
			{
				winner = Winner::DEFENDER;
			}
		}

		// Adjust the winner based on critical successes and failures
		if (attackerResult.critSuccess and defenderResult.critSuccess)
		{
			// Both crit: Winner stays as determined by total or skill comparison
		}
		else if (attackerResult.critSuccess)
		{
			winner = Winner::ATTACKER;
			critWin = true;
		}
		else if (defenderResult.critSuccess)
		{
			winner = Winner::DEFENDER;
			critWin = true;
		}
		else if (attackerResult.critFailure && defenderResult.critFailure)
		{
			// Both fumble: Winner stays as determined by total or skill comparison
		}
		else if (attackerResult.critFailure)
		{
			winner = Winner::DEFENDER;
			critLoss = true;
		}
		else if (defenderResult.critFailure)
		{
			winner = Winner::ATTACKER;
			critLoss = true;
		}

		// Calculate the degree of difference
		degree = std::abs(attackerResult.total - defenderResult.total) / DIFFICULTY_SCALING_FACTOR;

		// Return the result
		return { winner, degree, attackerResult, defenderResult, critWin, critLoss };
	}//End of opposedRoll

	// Function: targetRoll
	// Rolls against a target number to determine success or failure.
	TargetRollResult Core::targetRoll(int skillLevel, int difficultyLevel,
		int boons, int banes,
		int baseDiceCount, int diceSides, int minValue)
	{
		// Calculate the target number as difficultyLevel * DIFFICULTY_SCALING_FACTOR
		int targetNumber = difficultyLevel * DIFFICULTY_SCALING_FACTOR;

		// Perform the skill roll
		SkillRollResult roll = skillRoll(skillLevel, boons, banes, baseDiceCount, diceSides, minValue);

		// Determine success or failure
		bool success = roll.total >= targetNumber;
		int degree = (roll.total - targetNumber) / DIFFICULTY_SCALING_FACTOR;

		// Check for critical success or failure
		bool critSuccess = roll.critSuccess;
		bool critFailure = roll.critFailure;

		// Return the result in a TargetRollResult struct
		return { success, degree, roll, critSuccess, critFailure };
	}	//End of targetRoll
}//End of Namespace Core