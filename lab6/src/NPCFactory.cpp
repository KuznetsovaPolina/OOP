#include "NPCFactory.h"
#include "Dragon.h"
#include "Frog.h"
#include "Knight.h"
#include <stdexcept>

static void check_coords(double x, double y) {
    if (x < 0.0 || x > 500.0 || y < 0.0 || y > 500.0) {
        throw std::runtime_error("Coordinates must be in [0,500]");
    }
}

std::shared_ptr<NPC> NPCFactory::create(const std::string& type,
                                        const std::string& name,
                                        double x, double y) const {
    if (name.empty()) {
        throw std::runtime_error("Name must be non-empty");
    }
    check_coords(x, y);

    if (type == "Dragon") {
        return std::make_shared<Dragon>(name, x, y);
    } else if (type == "Frog") {
        return std::make_shared<Frog>(name, x, y);
    } else if (type == "Knight") {
        return std::make_shared<Knight>(name, x, y);
    }

    throw std::runtime_error("Unknown NPC type: " + type);
}

std::shared_ptr<NPC> NPCFactory::createFromStream(std::istream& is) const {
    std::string type;
    double x, y;
    std::string name;
    if (!(is >> type >> x >> y >> name)) {
        return nullptr;
    }
    return create(type, name, x, y);
}
