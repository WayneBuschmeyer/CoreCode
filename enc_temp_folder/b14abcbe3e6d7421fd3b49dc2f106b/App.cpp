#include "Core/Core.h"
#include <iostream>
#include <limits>

static int getValidatedInput(const std::string& prompt, int min = std::numeric_limits<int>::min(), int max = std::numeric_limits<int>::max())
{
	int value;
	bool keepGoing{ true };
	do
	{
		std::cout << prompt;
		std::cin >> value;

		// Check for input validity and range
		if (std::cin.fail())
		{
			std::cin.clear(); // Clear the error flag
			std::cout << "Invalid input. Please enter a number.\n";
		}
		else if (value < min or value > max)
		{
			std::cout << "Invalid input. Please enter a value between " << min << " and " << max << ".\n";
		}
		else
		{
			keepGoing = false; // Input is valid
		}

		// Ignore invalid input or any extra characters
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} while (keepGoing);

	return value; // Valid input; return the value
}

// Function to get user input and execute the opposed roll
static void handleOpposedRoll()
{
	std::cout << "Welcome to the Opposed Roll App!\n";

	// Get input for the attacker
	int attackerSkillLevel = getValidatedInput("Enter attacker skill level: ");
	int attackerBoons = getValidatedInput("Enter number of attacker boons: ", 0);
	int attackerBanes = getValidatedInput("Enter number of attacker banes: ", 0);

	// Get input for the defender
	int defenderSkillLevel = getValidatedInput("Enter defender skill level: ");
	int defenderBoons = getValidatedInput("Enter number of defender boons: ", 0);
	int defenderBanes = getValidatedInput("Enter number of defender banes: ", 0);

	// Execute the opposed roll
	Core::OpposedRollResult result = Core::opposedRoll(attackerSkillLevel, defenderSkillLevel,
		attackerBoons, attackerBanes,
		defenderBoons, defenderBanes);

	// Display the dice rolls and totals for the attacker
	std::cout << "Attacker Rolls: ";
	for (int roll : result.attackerRoll.rolls)
	{
		std::cout << roll << " ";
	}
	int attackerDiceTotal = std::accumulate(result.attackerRoll.rolls.begin(), result.attackerRoll.rolls.end(), 0);
	std::cout << "(Dice Total: " << attackerDiceTotal
		<< ", Skill Bonus: " << attackerSkillLevel
		<< ", Final Total: " << result.attackerRoll.total << ")\n";

	// Display the dice rolls and totals for the defender
	std::cout << "Defender Rolls: ";
	for (int roll : result.defenderRoll.rolls)
	{
		std::cout << roll << " ";
	}
	int defenderDiceTotal = std::accumulate(result.defenderRoll.rolls.begin(), result.defenderRoll.rolls.end(), 0);
	std::cout << "(Dice Total: " << defenderDiceTotal
		<< ", Skill Bonus: " << defenderSkillLevel
		<< ", Final Total: " << result.defenderRoll.total << ")\n";

	// Determine the reason for the win
	if (result.critWin)
	{
		if (result.winner == Core::Winner::ATTACKER)
		{
			std::cout << "Attacker wins with a critical success!\n";
		}
		else if (result.winner == Core::Winner::DEFENDER)
		{
			std::cout << "Defender wins with a critical success!\n";
		}
	}
	else if (result.critLoss)
	{
		if (result.winner == Core::Winner::DEFENDER)
		{
			std::cout << "Defender wins because the attacker fumbled!\n";
		}
		else if (result.winner == Core::Winner::ATTACKER)
		{
			std::cout << "Attacker wins because the defender fumbled!\n";
		}
	}
	else
	{
		if (result.winner == Core::Winner::ATTACKER)
		{
			std::cout << "Attacker wins with a degree of " << result.degree << "!\n";
		}
		else if (result.winner == Core::Winner::DEFENDER)
		{
			std::cout << "Defender wins with a degree of " << result.degree << "!\n";
		}
		else
		{
			std::cout << "It's a tie!\n";
		}
	}

	std::cout << "------------------------\n";
}

// Function: handleTargetRoll
// Handles the logic for rolling against a target number.
// Prompts the user for skill level, difficulty level, boons, and banes, then displays the result.
static void handleTargetRoll()
{
	// Get user input
	int skillLevel = getValidatedInput("Enter your skill level: ");
	int difficultyLevel = getValidatedInput("Enter difficulty level (1-10): ", 1, 10);
	int boons = getValidatedInput("Enter number of boons: ", 0);
	int banes = getValidatedInput("Enter number of banes: ", 0);

	// Execute the target roll
	Core::TargetRollResult result = Core::targetRoll(skillLevel, difficultyLevel, boons, banes);

	// Display roll details
	std::cout << "Rolls: ";
	for (int roll : result.roll.rolls)
	{
		std::cout << roll << " ";
	}
	int targetNumber = difficultyLevel * Core::DIFFICULTY_SCALING_FACTOR;
	std::cout << "\nTotal: " << result.roll.total
		<< " (Skill Bonus: " << skillLevel
		<< ", Target Number: " << targetNumber << ")\n";

	// Display outcome
	if (result.critSuccess)
	{
		std::cout << "Critical Success!\n";
	}
	else if (result.critFailure)
	{
		std::cout << "Critical Failure!\n";
	}
	else if (result.success)
	{
		std::cout << "Success! Degree of success: " << result.degree << "\n";
	}
	else
	{
		std::cout << "Failure. Degree of failure: " << result.degree << "\n";
	}

	std::cout << "------------------------\n";
}

// Function: showManual
// Displays a manual explaining how the app works and the purpose of each menu option.
static void showManual()
{
	std::cout << "\nCoreRoller Manual\n";
	std::cout << "------------------------\n";
	std::cout << "1. Perform an Opposed Roll:\n";
	std::cout << "   - Simulates a contest between two characters (attacker and defender).\n";
	std::cout << "   - You will be prompted to enter skill levels, boons, and banes for both characters.\n";
	std::cout << "   - The app calculates who wins based on dice rolls and skill levels.\n";
	std::cout << "   - Critical successes or failures can override the outcome.\n";
	std::cout << "\n";
	std::cout << "2. Roll Against a Target Number:\n";
	std::cout << "   - Simulates a character attempting to overcome a challenge with a specified difficulty.\n";
	std::cout << "   - You will be prompted to enter your skill level, a difficulty level (1-10), and any boons or banes.\n";
	std::cout << "   - The app determines success or failure, and the degree of success or failure.\n";
	std::cout << "\n";
	std::cout << "3. Exit:\n";
	std::cout << "   - Exits the CoreRoller app.\n";
	std::cout << "\n";
	std::cout << "Boons and Banes:\n";
	std::cout << "   - Boons add extra dice to the roll, keeping the highest results.\n";
	std::cout << "   - Banes add extra dice but keep the lowest results.\n";
	std::cout << "------------------------\n";
}



// Function: runCoreRoller
// Main loop for the app. Displays a menu for opposed rolls, target rolls, manual, or exiting the program.
static void runCoreRoller()
{
	while (true)
	{
		// Display menu
		std::cout << "\nWelcome to CoreRoller!\n";
		std::cout << "1. Perform an Opposed Roll\n";
		std::cout << "2. Roll Against a Target Number\n";
		std::cout << "3. Show Manual (How It Works)\n";
		std::cout << "4. Exit\n";

		int choice = getValidatedInput("Choose an option (1-4): ", 1, 4);

		// Handle user choice
		switch (choice)
		{
		case 1:
			handleOpposedRoll();
			break;
		case 2:
			handleTargetRoll();
			break;
		case 3:
			showManual();
			break;
		case 4:
			std::cout << "Exiting CoreRoller. Goodbye!\n";
			return;
		default:
			std::cout << "Invalid choice. Please try again.\n";
		}
	}
}


int main()
{
	// Start CoreRoller
	runCoreRoller();
	return 0;
}
