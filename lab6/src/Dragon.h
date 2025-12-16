#pragma once
#include "NPC.h"

class Dragon : public NPC {
public:
    Dragon(const std::string& name, double x, double y);
    std::string type() const override { return "Dragon"; }
    void accept(INPCVisitor& v) override;
};
