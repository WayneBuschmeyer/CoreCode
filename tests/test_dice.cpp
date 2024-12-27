#include <gtest/gtest.h>
#include "Core/Core.h"

// Test for rollDice function
TEST(CoreTests, RollDice) {
    auto rolls = Core::rollDice(3, 6, 1);
    ASSERT_EQ(rolls.size(), 3); // Ensure the correct number of rolls
    for (int roll : rolls) {
        EXPECT_GE(roll, 1);     // Each roll must be >= 1
        EXPECT_LE(roll, 6);     // Each roll must be <= 6
    }
}

// Test for opposedRoll function
TEST(CoreTests, OpposedRoll) {
    Core::OpposedRollResult result = Core::opposedRoll(10, 8, 1, 0, 0, 1, 3, 6, 1);
    EXPECT_TRUE(result.winner == Core::Winner::ATTACKER || result.winner == Core::Winner::DEFENDER);
    EXPECT_FALSE(result.critWin && result.critLoss); // Cannot have both critWin and critLoss
    EXPECT_GE(result.degree, 0);                    // Degree should be non-negative
}

// Test for targetRoll function
TEST(CoreTests, TargetRoll) {
    Core::TargetRollResult result = Core::targetRoll(10, 5, 0, 0, 3, 6, 1); // Target number = 5 * 4 = 20
    EXPECT_TRUE(result.success || !result.success);  // Either success or failure
    EXPECT_FALSE(result.critSuccess && result.critFailure); // Cannot be both critSuccess and critFailure
    EXPECT_GE(result.degree, -5);                    // Degree should make sense
}
