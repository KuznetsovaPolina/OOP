#pragma once
#include "NPC.h"

class Knight : public NPC {
public:
    Knight(const std::string& name, double x, double y);
    std::string type() const override { return "Knight"; }
    void accept(INPCVisitor& v) override;
};
