#include <gtest/gtest.h>
#include "Game.h"
#include "NPC.h"

TEST(KillRules, FrogKillsAll) {
    NPC frog{NPCType::Frog, "Frog", 0.0, 0.0, true};
    NPC dragon{NPCType::Dragon, "Dragon", 0.0, 0.0, true};
    NPC knight{NPCType::Knight, "Knight", 0.0, 0.0, true};

    EXPECT_TRUE(frog.alive);
    EXPECT_EQ(frog.type, NPCType::Frog);
}
