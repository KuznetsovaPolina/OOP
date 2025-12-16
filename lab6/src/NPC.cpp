#include "NPC.h"
#include "Visitor.h"

NPC::NPC(std::string name, double x, double y)
    : name_(std::move(name)), x_(x), y_(y) {}

void NPC::print(std::ostream& os) const {
    os << type() << " '" << name_ << "' at (" << x_ << ", " << y_ << ")";
}

std::ostream& operator<<(std::ostream& os, const NPC& npc) {
    npc.print(os);
    return os;
}
