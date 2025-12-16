#pragma once
#include <string>
#include <memory>
#include <iostream>

class INPCVisitor;

class NPC {
protected:
    std::string name_;
    double x_{};
    double y_{};

public:
    NPC(std::string name, double x, double y);
    virtual ~NPC() = default;

    const std::string& name() const { return name_; }
    double x() const { return x_; }
    double y() const { return y_; }

    virtual std::string type() const = 0;
    virtual void accept(INPCVisitor& v) = 0;

    virtual void print(std::ostream& os) const;
};

std::ostream& operator<<(std::ostream& os, const NPC& npc);
