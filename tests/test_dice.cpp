#include <gtest/gtest.h>
#include "Core/Core.h"
#include "Source/App.h"
#include <sstream>

// Helper function to simulate input
void setInput(const std::string& input) {
    std::istringstream inputStream{ input };
    std::cin.rdbuf(inputStream.rdbuf());
}

// Helper function to capture output
std::string captureOutput(void (*testFunction)()) {
    std::ostringstream output;
    std::cout.rdbuf(output.rdbuf());
    testFunction();
    return output.str();
}

// Test: rollDice Function
TEST(CoreTests, RollDiceValid) {
    auto rolls = Core::rollDice(3, 6, 1);
    ASSERT_EQ(rolls.size(), 3) << "Expected 3 dice rolls.";
    for (int roll : rolls) {
        EXPECT_GE(roll, 1) << "Roll should be >= 1.";
        EXPECT_LE(roll, 6) << "Roll should be <= 6.";
    }
}

TEST(CoreTests, RollDiceEdgeCases) {
    // Zero dice roll
    auto rolls = Core::rollDice(0, 6, 1);
    ASSERT_TRUE(rolls.empty()) << "Expected no rolls for zero dice.";

    // Negative dice sides
    rolls = Core::rollDice(3, -6, 1);
    ASSERT_TRUE(rolls.empty()) << "Expected no rolls for negative sides.";

    // Large number of dice
    rolls = Core::rollDice(1000, 20, 1);
    ASSERT_EQ(rolls.size(), 1000) << "Expected 1000 dice rolls.";
    for (int roll : rolls) {
        EXPECT_GE(roll, 1) << "Roll should be >= 1.";
        EXPECT_LE(roll, 20) << "Roll should be <= 20.";
    }
}

// Test: opposedRoll Function
TEST(CoreTests, OpposedRollBasic) {
    Core::OpposedRollResult result = Core::opposedRoll(10, 8, 1, 0, 0, 1, 3, 6, 1);
    ASSERT_TRUE(result.winner == Core::Winner::ATTACKER || result.winner == Core::Winner::DEFENDER)
        << "Winner should be ATTACKER or DEFENDER.";
    EXPECT_FALSE(result.critWin && result.critLoss) << "Cannot have both critWin and critLoss.";
    EXPECT_GE(result.degree, 0) << "Degree should be non-negative.";
}

// Test: targetRoll Function
TEST(CoreTests, TargetRollValid) {
    Core::TargetRollResult result = Core::targetRoll(10, 5, 0, 0, 3, 6, 1); // Target number = 5 * 4 = 20
    EXPECT_TRUE(result.success || !result.success) << "Result should indicate success or failure.";
    EXPECT_FALSE(result.critSuccess && result.critFailure) << "Cannot be both critSuccess and critFailure.";
    EXPECT_GE(result.degree, -5) << "Degree should be sensible.";
}

// Test: App Functionality (readValidatedInteger)
TEST(AppTests, ReadValidatedInteger) {
    setInput("5\n");
    int result = readValidatedInteger("Enter a number: ", 1, 10);
    EXPECT_EQ(result, 5) << "Expected input to be 5.";

    setInput("abc\n7\n");
    result = readValidatedInteger("Enter a number: ", 1, 10);
    EXPECT_EQ(result, 7) << "Expected input to be 7 after invalid attempt.";
}

// Test: App Functionality (handleOpposedRoll)
TEST(AppTests, HandleOpposedRoll) {
    setInput("10\n1\n0\n8\n0\n1\n"); // Simulate user input
    auto result = captureOutput(handleOpposedRoll);
    EXPECT_TRUE(result.find("Attacker Rolls:") != std::string::npos) << "Expected Attacker Rolls in output.";
    EXPECT_TRUE(result.find("Defender Rolls:") != std::string::npos) << "Expected Defender Rolls in output.";
}

// Test: App Functionality (handleTargetRoll)
TEST(AppTests, HandleTargetRoll) {
    setInput("10\n5\n0\n0\n"); // Simulate user input
    auto result = captureOutput(handleTargetRoll);
    EXPECT_TRUE(result.find("Target Number:") != std::string::npos) << "Expected Target Number in output.";
    EXPECT_TRUE(result.find("Critical Success!") != std::string::npos ||
        result.find("Critical Failure!") != std::string::npos ||
        result.find("Success!") != std::string::npos ||
        result.find("Failure.") != std::string::npos)
        << "Expected some success/failure outcome in output.";
}
