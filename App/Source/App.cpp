#include "Core/Core.h"
#include "App.h"

// Function: writeOutput
// A generalized function to output data, adaptable for different interfaces.
// Parameters:
// - output: The string to display to the user.
void writeOutput(const std::string& output)
{
    std::cout << output;
}

// Function: readInput
// A generalized function to input data, adaptable for different interfaces.
// Parameters:
// - prompt: The string prompt to display to the user.
// Returns:
// - A string containing the user's input.
std::string readInput(const std::string& prompt)
{
    writeOutput(prompt);
    std::string input;
    std::getline(std::cin, input);
    return input;
}

// Function: readValidatedInteger
// Collects a validated integer input from the user.
// Parameters:
// - prompt: The string prompt to display to the user.
// - min: The minimum acceptable value (default: lowest int).
// - max: The maximum acceptable value (default: highest int).
// Returns:
// - An integer value that is valid and within the specified range.
int readValidatedInteger(const std::string& prompt, int min , int max )
{
    int value{};
    bool keepGoing{ true };
    do
    {
        std::string input{ readInput(prompt) };
        bool isValid{ true };

        // Check if the input contains only digits (with an optional leading '-' for negatives)
        for (size_t i = 0; i < input.size(); ++i)
        {
            if (!std::isdigit(input[i]) && !(i == 0 && input[i] == '-'))
            {
                isValid = false;
                break;
            }
        }

        if (isValid)
        {
            value = std::stoi(input); // Safe to convert since the input was validated

            if (value < min || value > max)
            {
                writeOutput("Invalid input. Please enter a value between " + std::to_string(min) + " and " + std::to_string(max) + ".\n");
            }
            else
            {
                keepGoing = false; // Input is valid
            }
        }
        else
        {
            writeOutput("Invalid input. Please enter a value between " + std::to_string(min) + " and " + std::to_string(max) + ".\n");
        }
    } while (keepGoing);

    return value; // Valid input; return the value
}

// Function: formatRollResults
// Formats roll results into a string for display.
// Parameters:
// - rolls: The dice rolls.
// - skillLevel: The skill level of the character.
// - total: The final total including skill bonus.
// - role: A label for the character's role (e.g., "Attacker" or "Defender").
// Returns:
// - A formatted string with the roll results.
std::string formatRollResults(const std::vector<int>& rolls, int skillLevel, int total, const std::string& role)
{
    std::string output{ role + " Rolls: [" };
    for (size_t i{}; i < rolls.size(); ++i)
    {
        output += std::to_string(rolls[i]);
        if (i < rolls.size() - 1)
        {
            output += ", ";
        }
    }
    int diceTotal{ std::accumulate(rolls.begin(), rolls.end(), 0) };
    output += "] (Dice Total: " + std::to_string(diceTotal)
        + ", Skill Bonus: " + std::to_string(skillLevel)
        + ", Final Total: " + std::to_string(total) + ")\n";
    return output;
}

// Function: handleTargetRoll
// Handles the logic for rolling against a target number.
// Prompts the user for skill level, difficulty level, boons, and banes, then displays the result.
void handleTargetRoll()
{
    // Get user input
    int skillLevel{ readValidatedInteger("Enter your skill level: ") };
    int difficultyLevel{ readValidatedInteger("Enter difficulty level") };
    int boons{ readValidatedInteger("Enter number of boons: ", 0) };
    int banes{ readValidatedInteger("Enter number of banes: ", 0) };

    // Execute the target roll
    Core::TargetRollResult result{ Core::targetRoll(skillLevel, difficultyLevel, boons, banes) };

    // Display roll details using formatRollResults
    writeOutput(formatRollResults(result.roll.rolls, skillLevel, result.roll.total, "Your"));

    int targetNumber{ difficultyLevel * Core::DIFFICULTY_SCALING_FACTOR };
    writeOutput("Target Number: " + std::to_string(targetNumber) + "\n");

    // Display outcome
    if (result.critSuccess)
    {
        writeOutput("Critical Success!\n");
    }
    else if (result.critFailure)
    {
        writeOutput("Critical Failure!\n");
    }
    else if (result.success)
    {
        writeOutput("Success! Degree of success: " + std::to_string(result.degree) + "\n");
    }
    else
    {
        writeOutput("Failure. Degree of failure: " + std::to_string(result.degree) + "\n");
    }

    writeOutput("------------------------\n");
}

// Function: handleOpposedRoll
// Manages the opposed roll process by collecting input, executing the roll, and displaying results.
void handleOpposedRoll()
{
    writeOutput("Welcome to the Opposed Roll App!\n\n");

    // Get input for the attacker
    int attackerSkillLevel{ readValidatedInteger("Enter attacker skill level: ") };
    int attackerBoons{ readValidatedInteger("Enter number of attacker boons: ", 0) };
    int attackerBanes{ readValidatedInteger("Enter number of attacker banes: ", 0) };

    // Get input for the defender
    int defenderSkillLevel{ readValidatedInteger("Enter defender skill level: ") };
    int defenderBoons{ readValidatedInteger("Enter number of defender boons: ", 0) };
    int defenderBanes{ readValidatedInteger("Enter number of defender banes: ", 0) };

    // Execute the opposed roll
    Core::OpposedRollResult result{ Core::opposedRoll(attackerSkillLevel, defenderSkillLevel,
        attackerBoons, attackerBanes,
        defenderBoons, defenderBanes) };

    // Display results for the attacker
    writeOutput(formatRollResults(result.attackerRoll.rolls, attackerSkillLevel, result.attackerRoll.total, "Attacker"));

    // Display results for the defender
    writeOutput(formatRollResults(result.defenderRoll.rolls, defenderSkillLevel, result.defenderRoll.total, "Defender"));

    // Display the outcome
    std::string outcomeOutput{};
    if (result.critWin)
    {
        outcomeOutput = (result.winner == Core::Winner::ATTACKER ? "Attacker" : "Defender") + std::string(" wins with a critical success!\n");
    }
    else if (result.critLoss)
    {
        outcomeOutput = (result.winner == Core::Winner::DEFENDER ? "Defender" : "Attacker") + std::string(" wins because the other fumbled!\n");
    }
    else if (result.winner == Core::Winner::ATTACKER)
    {
        outcomeOutput = "Attacker wins with a degree of " + std::to_string(result.degree) + "!\n";
    }
    else if (result.winner == Core::Winner::DEFENDER)
    {
        outcomeOutput = "Defender wins with a degree of " + std::to_string(result.degree) + "!\n";
    }
    else
    {
        outcomeOutput = "It's a tie!\n";
    }

    writeOutput(outcomeOutput);
    writeOutput("------------------------\n");
}

// Function: showManual
// Displays a manual explaining how the app works and the purpose of each menu option.
void showManual()
{
    const std::string manual =
        "\nCoreRoller Manual\n"
        "------------------------\n"
        "1. Perform an Opposed Roll:\n"
        "   - Simulates a contest between two characters (attacker and defender).\n"
        "   - You will be prompted to enter skill levels, boons, and banes for both characters.\n"
        "   - The app calculates who wins based on dice rolls and skill levels.\n"
        "   - Critical successes or failures can override the outcome.\n\n"
        "2. Roll Against a Target Number:\n"
        "   - Simulates a character attempting to overcome a challenge with a specified difficulty.\n"
        "   - You will be prompted to enter your skill level, a difficulty level (1-10), and any boons or banes.\n"
        "   - The app determines success or failure, and the degree of success or failure.\n\n"
        "3. Exit:\n"
        "   - Exits the CoreRoller app.\n\n"
        "Boons and Banes:\n"
        "   - Boons add extra dice to the roll, keeping the highest results.\n"
        "   - Banes add extra dice but keep the lowest results.\n"
        "------------------------\n";

    writeOutput(manual);
}

// Function: runCoreRoller
// Main loop for the app. Displays a menu for opposed rolls, target rolls, manual, or exiting the program.
void runCoreRoller()
{
    while (true)
    {
        // Display menu
        writeOutput("\nWelcome to CoreRoller!\n");
        writeOutput("1. Perform an Opposed Roll\n");
        writeOutput("2. Roll Against a Target Number\n");
        writeOutput("3. Exit\n");
        writeOutput("4. Show Manual (How It Works)\n");

        int choice{ std::stoi(readInput("Choose an option (1-4): ")) };

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
            writeOutput("Exiting CoreRoller. Goodbye!\n");
            return;

        case 4:
            showManual();
            break;

        default:
            writeOutput("Invalid choice. Please try again.\n");
        }
    }
}


int main()
{
	// Start CoreRoller
	runCoreRoller();
	return 0;
}