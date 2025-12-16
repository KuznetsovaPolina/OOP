#pragma once
#include <memory>
#include <string>
#include <istream>
#include "NPC.h"

class NPCFactory {
public:
    std::shared_ptr<NPC> create(const std::string& type,
                                const std::string& name,
                                double x, double y) const;

    std::shared_ptr<NPC> createFromStream(std::istream& is) const;
};
