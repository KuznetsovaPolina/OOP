#include <gtest/gtest.h>
#include "Dragon.h"
#include "Frog.h"
#include "Knight.h"
#include "Battle.h"
#include "Observer.h"

TEST(BattleRules, FrogVsKnightFrogWins) {
    Frog frog("F", 0, 0);
    Knight knight("K", 0, 0);
    EventManager events;
    BattleResult res = fightPair(frog, knight, 10.0, events);
    EXPECT_FALSE(res.aDead); // frog survives
    EXPECT_TRUE(res.bDead);  // knight dies
}

TEST(BattleRules, KnightVsDragonBothDie) {
    Knight knight("K", 0, 0);
    Dragon dragon("D", 0, 0);
    EventManager events;
    BattleResult res = fightPair(knight, dragon, 10.0, events);
    EXPECT_TRUE(res.aDead);
    EXPECT_TRUE(res.bDead);
}

TEST(BattleRules, FrogVsFrogBothDie) {
    Frog f1("F1", 0, 0);
    Frog f2("F2", 0, 0);
    EventManager events;
    BattleResult res = fightPair(f1, f2, 10.0, events);
    EXPECT_TRUE(res.aDead);
    EXPECT_TRUE(res.bDead);
}
