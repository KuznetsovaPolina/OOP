#include "Dungeon.h"
#include <fstream>
#include <iostream>

DungeonEditor::DungeonEditor() {
    events_.addObserver(std::make_shared<ConsoleObserver>());
    events_.addObserver(std::make_shared<FileObserver>("log.txt"));
}

bool DungeonEditor::isNameUnique(const std::string& name) const {
    for (const auto& npc : npcs_) {
        if (npc->name() == name) return false;
    }
    return true;
}

bool DungeonEditor::addNPC(const std::string& type,
                           const std::string& name,
                           double x, double y) {
    if (!isNameUnique(name)) {
        std::cerr << "NPC with name '" << name << "' already exists\n";
        return false;
    }
    try {
        auto npc = factory_.create(type, name, x, y);
        npcs_.push_back(npc);
        return true;
    } catch (const std::exception& ex) {
        std::cerr << "Error adding NPC: " << ex.what() << "\n";
        return false;
    }
}

void DungeonEditor::listNPCs() const {
    if (npcs_.empty()) {
        std::cout << "No NPCs in dungeon.\n";
        return;
    }
    std::cout << "NPCs in dungeon:\n";
    for (const auto& npc : npcs_) {
        std::cout << "  " << *npc << "\n";
    }
}

bool DungeonEditor::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) return false;
    for (const auto& npc : npcs_) {
        out << npc->type() << " "
            << npc->x() << " " << npc->y() << " "
            << npc->name() << "\n";
    }
    return true;
}

bool DungeonEditor::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) return false;
    std::vector<std::shared_ptr<NPC>> loaded;
    while (true) {
        auto npc = factory_.createFromStream(in);
        if (!npc) break;
        if (!isNameUnique(npc->name())) {
            std::cerr << "Duplicate name in file: '" << npc->name() << "', skipping\n";
            continue;
        }
        loaded.push_back(npc);
    }
    npcs_.swap(loaded);
    return true;
}

void DungeonEditor::runBattleMode(double distanceLimit) {
    if (npcs_.size() < 2) {
        std::cout << "Not enough NPCs to battle.\n";
        return;
    }
    std::cout << "Starting battle with distance limit = " << distanceLimit << "\n";
    runBattle(npcs_, distanceLimit, events_);
    std::cout << "Battle finished. Survivors: " << npcs_.size() << "\n";
    listNPCs();
}
