#include "Dragon.h"
#include "Visitor.h"

Dragon::Dragon(const std::string& name, double x, double y)
    : NPC(name, x, y) {}

void Dragon::accept(INPCVisitor& v) {
    v.visit(*this);
}
