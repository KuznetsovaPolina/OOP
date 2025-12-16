#pragma once
#include <vector>
#include <memory>
#include <string>
#include "NPC.h"
#include "NPCFactory.h"
#include "Observer.h"
#include "Battle.h"

class DungeonEditor {
public:
    DungeonEditor();

    bool addNPC(const std::string& type,
                const std::string& name,
                double x, double y);

    void listNPCs() const;

    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);

    void runBattleMode(double distanceLimit);

private:
    std::vector<std::shared_ptr<NPC>> npcs_;
    NPCFactory factory_;
    EventManager events_;

    bool isNameUnique(const std::string& name) const;
};
