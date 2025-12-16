#pragma once
#include <vector>
#include <memory>
#include "NPC.h"
#include "Visitor.h"
#include "Observer.h"

struct BattleResult {
    bool aDead{false};
    bool bDead{false};
};

BattleResult fightPair(NPC& a, NPC& b, double distanceLimit, EventManager& events);

void runBattle(std::vector<std::shared_ptr<NPC>>& npcs,
               double distanceLimit,
               EventManager& events);
