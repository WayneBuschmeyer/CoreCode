#pragma once


#include "Core/Core.h"

#include <string>
#include <iostream>
#include <vector>
#include <numeric>
#include <limits>

// Function: writeOutput
// Outputs a string to the user.
void writeOutput(const std::string& output);

// Function: readInput
// Reads a string input from the user.
// Parameters:
// - prompt: The prompt message to display.
// Returns:
// - A string containing the user's input.
std::string readInput(const std::string& prompt);

// Function: readValidatedInteger
// Reads an integer input from the user with validation.
// Parameters:
// - prompt: The prompt message to display.
// - min: The minimum acceptable value (default: std::numeric_limits<int>::min()).
// - max: The maximum acceptable value (default: std::numeric_limits<int>::max()).
// Returns:
// - A validated integer within the specified range.
int readValidatedInteger(const std::string& prompt, int min = std::numeric_limits<int>::min(), int max = std::numeric_limits<int>::max());

// Function: handleOpposedRoll
// Handles the process for performing an opposed roll.
void handleOpposedRoll();

// Function: handleTargetRoll
// Handles the process for performing a roll against a target number.
void handleTargetRoll();

// Function: showManual
// Displays the user manual explaining the app functionality.
void showManual();

// Function: runCoreRoller
// Main loop for the app, displaying a menu for user interactions.
void runCoreRoller();
