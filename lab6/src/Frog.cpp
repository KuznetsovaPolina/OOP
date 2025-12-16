#include "Frog.h"
#include "Visitor.h"

Frog::Frog(const std::string& name, double x, double y)
    : NPC(name, x, y) {}

void Frog::accept(INPCVisitor& v) {
    v.visit(*this);
}
