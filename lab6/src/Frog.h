#pragma once
#include "NPC.h"

class Frog : public NPC {
public:
    Frog(const std::string& name, double x, double y);
    std::string type() const override { return "Frog"; }
    void accept(INPCVisitor& v) override;
};
