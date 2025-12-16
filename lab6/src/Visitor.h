#pragma once

class Dragon;
class Frog;
class Knight;

class INPCVisitor {
public:
    virtual ~INPCVisitor() = default;
    virtual void visit(Dragon& d) = 0;
    virtual void visit(Frog& f) = 0;
    virtual void visit(Knight& k) = 0;
};
