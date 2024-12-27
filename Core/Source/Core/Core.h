#pragma once

#include <vector>
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <random>
#include <numeric>

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
	constexpr int DEFAULT_SKILL_LEVEL = 0;        // Default skill level modifier
	constexpr int DIFFICULTY_SCALING_FACTOR = 4;  // Multiplier for degree calculation and target number scaling

	// Structure: SkillRollResult
	// Encapsulates the result of a skill roll.
	struct SkillRollResult
	{
		int total;                   // Total roll value including skill level
		std::vector<int> rolls;      // Individual dice rolls used in the calculation
		bool critSuccess;            // True if all selected dice rolled the maximum value
		bool critFailure;            // True if all selected dice rolled the minimum value
	};

	// Enum: Winner
// Represents the result of an opposed roll.
	enum class Winner
	{
		TIE,         // Represents a tie in an opposed roll
		ATTACKER, // Represents a win for Contestant 1
		DEFENDER  // Represents a win for Contestant 2
	};

	// Structure: OpposedRollResult
	// Encapsulates the result of an opposed roll between attacker and defender.
	struct OpposedRollResult
	{
		Winner winner;              // Winner of the opposed roll (ATTACKER, DEFENDER, or TIE)
		int degree;                 // Difference between the two totals divided by DIFFICULTY_SCALING_FACTOR
		SkillRollResult attackerRoll; // Details of the attacker's roll
		SkillRollResult defenderRoll; // Details of the defender's roll
		bool critWin;               // True if the winner was decided by a critical success
		bool critLoss;              // True if the loser was decided by a critical failure
	};

	// Structure: TargetRollResult
	// Encapsulates the result of a roll against a target number.
	//
	// Fields:
	// - success: True if the roll meets or exceeds the target number.
	// - degree: Degree of success (positive) or failure (negative).
	// - roll: Details of the roll, including dice rolls, total, and crit flags.
	// - critSuccess: True if the roll is a critical success.
	// - critFailure: True if the roll is a critical failure.
	struct TargetRollResult
	{
		bool success;       // True if the roll meets or exceeds the target number
		int degree;         // Degree of success (positive) or failure (negative)
		SkillRollResult roll; // Details of the roll (dice rolls, total, crit flags)
		bool critSuccess;   // True if the roll is a critical success
		bool critFailure;   // True if the roll is a critical failure
	};

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

	// Function: skillRoll
	// Performs a skill roll, including adjustments for boons and banes.
	//
	// Parameters:
	// - skillLevel: Base skill level to add to the roll total.
	// - boons: Extra dice rolled, keeping the highest rolls (default: DEFAULT_BOONS).
	// - banes: Extra dice rolled, keeping the lowest rolls (default: DEFAULT_BANES).
	// - baseDiceCount: Number of main dice rolled (default: DEFAULT_BASE_DICE_COUNT).
	// - diceSides: Number of sides on each die (default: DEFAULT_DICE_SIDES).
	// - minValue: Minimum value each die can roll (default: DEFAULT_MIN_VALUE).
	//
	// Returns:
	// - A SkillRollResult struct with the total, critSuccess, and critFailure.
	SkillRollResult skillRoll(int skillLevel = DEFAULT_SKILL_LEVEL, int boons = DEFAULT_BOONS, int banes = DEFAULT_BANES, int baseDiceCount = DEFAULT_BASE_DICE_COUNT, int diceSides = DEFAULT_DICE_SIDES, int minValue = DEFAULT_MIN_VALUE);

	// Function: opposedRoll
	// Performs an opposed roll between two contestants.
	//
	// Parameters:
	// - attackerSkillLevel: Skill level of the attacker (default: DEFAULT_SKILL_LEVEL).
	// - defenderSkillLevel: Skill level of the defender (default: DEFAULT_SKILL_LEVEL).
	// - attackerBoons: Extra dice rolled by the attacker, keeping the highest rolls (default: DEFAULT_BOONS).
	// - attackerBanes: Extra dice rolled by the attacker, keeping the lowest rolls (default: DEFAULT_BANES).
	// - defenderBoons: Extra dice rolled by the defender, keeping the highest rolls (default: DEFAULT_BOONS).
	// - defenderBanes: Extra dice rolled by the defender, keeping the lowest rolls (default: DEFAULT_BANES).
	// - baseDiceCount: Number of main dice rolled by each contestant (default: DEFAULT_BASE_DICE_COUNT).
	// - diceSides: Number of sides on each die (default: DEFAULT_DICE_SIDES).
	// - minValue: Minimum value each die can roll (default: DEFAULT_MIN_VALUE).
	//
	// Returns:
	// - An OpposedRollResult struct containing:
	//   - winner: The winner of the opposed roll (ATTACKER, DEFENDER, or TIE).
	//   - degree: Degree of success (positive) or failure (negative).
	//   - attackerRoll: Details of the attacker's roll, including dice rolls and crit flags.
	//   - defenderRoll: Details of the defender's roll, including dice rolls and crit flags.
	//   - critWin: True if the winner was decided by a critical success.
	//   - critLoss: True if the loser was decided by a critical failure.
	OpposedRollResult opposedRoll(
		int attackerSkillLevel = DEFAULT_SKILL_LEVEL, int defenderSkillLevel = DEFAULT_SKILL_LEVEL,
		int attackerBoons = DEFAULT_BOONS, int attackerBanes = DEFAULT_BANES,
		int defenderBoons = DEFAULT_BOONS, int defenderBanes = DEFAULT_BANES,
		int baseDiceCount = DEFAULT_BASE_DICE_COUNT,
		int diceSides = DEFAULT_DICE_SIDES,
		int minValue = DEFAULT_MIN_VALUE);

	// Function: targetRoll
	// Performs a roll against a specified difficulty level.
	// Determines success or failure based on the target number derived from the difficulty level.
	//
	// Parameters:
	// - skillLevel: Base skill level to add to the roll total.
	// - difficultyLevel: The level of difficulty, ranging from 1 (very easy) to 10 (extremely difficult).
	// - boons: Extra dice rolled, keeping the highest rolls (default: DEFAULT_BOONS).
	// - banes: Extra dice rolled, keeping the lowest rolls (default: DEFAULT_BANES).
	// - baseDiceCount: Number of main dice rolled (default: DEFAULT_BASE_DICE_COUNT).
	// - diceSides: Number of sides on each die (default: DEFAULT_DICE_SIDES).
	// - minValue: Minimum value each die can roll (default: DEFAULT_MIN_VALUE).
	//
	// Returns:
	// - A TargetRollResult struct containing:
	//   - success: True if the roll meets or exceeds the target number.
	//   - degree: Degree of success (positive) or failure (negative).
	//   - roll: Details of the roll, including dice rolls and crit flags.
	//   - critSuccess: True if the roll is a critical success.
	//   - critFailure: True if the roll is a critical failure.
	TargetRollResult targetRoll(int skillLevel, int difficultyLevel,
		int boons = DEFAULT_BOONS, int banes = DEFAULT_BANES,
		int baseDiceCount = DEFAULT_BASE_DICE_COUNT,
		int diceSides = DEFAULT_DICE_SIDES, int minValue = DEFAULT_MIN_VALUE);
}//End of Namespace Core
