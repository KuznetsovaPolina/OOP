#include "Knight.h"
#include "Visitor.h"

Knight::Knight(const std::string& name, double x, double y)
    : NPC(name, x, y) {}

void Knight::accept(INPCVisitor& v) {
    v.visit(*this);
}
