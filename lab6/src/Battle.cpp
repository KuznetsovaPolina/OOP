#include "Battle.h"
#include "Dragon.h"
#include "Frog.h"
#include "Knight.h"
#include <cmath>
#include <sstream>

class PairFightVisitor : public INPCVisitor {
public:
    NPC& other_;
    double distLimit_;
    EventManager& events_;
    BattleResult& result_;

    PairFightVisitor(NPC& other, double distLimit,
                     EventManager& events, BattleResult& res)
        : other_(other), distLimit_(distLimit), events_(events), result_(res) {}

    void visit(Dragon& d) override {
        handleDragon(d, other_);
    }

    void visit(Frog& f) override {
        handleFrog(f, other_);
    }

    void visit(Knight& k) override {
        handleKnight(k, other_);
    }

private:
    void handleDragon(Dragon& d, NPC& other);
    void handleFrog(Frog& f, NPC& other);
    void handleKnight(Knight& k, NPC& other);

    void logKill(const NPC& killer, const NPC& victim) {
        std::ostringstream ss;
        ss << killer.type() << " '" << killer.name() << "' killed "
           << victim.type() << " '" << victim.name() << "'";
        events_.notify(ss.str());
    }
};

static double distance(const NPC& a, const NPC& b) {
    double dx = a.x() - b.x();
    double dy = a.y() - b.y();
    return std::sqrt(dx*dx + dy*dy);
}

BattleResult fightPair(NPC& a, NPC& b, double distanceLimit, EventManager& events) {
    BattleResult res;
    if (&a == &b) return res;
    if (distance(a, b) > distanceLimit) return res;

    PairFightVisitor visitor(b, distanceLimit, events, res);
    a.accept(visitor);
    return res;
}

void PairFightVisitor::handleDragon(Dragon& d, NPC& other) {
    if (auto* frog = dynamic_cast<Frog*>(&other)) {
        result_.aDead = true;
        logKill(*frog, d);
    } else if (auto* knight = dynamic_cast<Knight*>(&other)) {
        result_.aDead = true;
        result_.bDead = true;
        logKill(*knight, d);
        logKill(d, *knight);
    } else if (auto* dr = dynamic_cast<Dragon*>(&other)) {
        (void)dr;
    }
}

void PairFightVisitor::handleFrog(Frog& f, NPC& other) {
    if (auto* frog2 = dynamic_cast<Frog*>(&other)) {
        result_.aDead = true;
        result_.bDead = true;
        logKill(f, *frog2);
        logKill(*frog2, f);
    } else if (auto* knight = dynamic_cast<Knight*>(&other)) {
        result_.bDead = true;
        logKill(f, *knight);
    } else if (auto* dragon = dynamic_cast<Dragon*>(&other)) {
        result_.bDead = true;
        logKill(f, *dragon);
    }
}

void PairFightVisitor::handleKnight(Knight& k, NPC& other) {
    if (auto* frog = dynamic_cast<Frog*>(&other)) {
        result_.aDead = true;
        logKill(*frog, k);
    } else if (auto* dragon = dynamic_cast<Dragon*>(&other)) {
        result_.aDead = true;
        result_.bDead = true;
        logKill(k, *dragon);
        logKill(*dragon, k);
    } else if (auto* knight2 = dynamic_cast<Knight*>(&other)) {
        (void)knight2;
    }
}

void runBattle(std::vector<std::shared_ptr<NPC>>& npcs,
               double distanceLimit,
               EventManager& events) {
    const std::size_t n = npcs.size();
    if (n < 2) return;

    std::vector<bool> alive(n, true);

    for (std::size_t i = 0; i < n; ++i) {
        if (!alive[i]) continue;
        for (std::size_t j = i + 1; j < n; ++j) {
            if (!alive[j]) continue;
            BattleResult res = fightPair(*npcs[i], *npcs[j], distanceLimit, events);
            if (res.aDead) alive[i] = false;
            if (res.bDead) alive[j] = false;
            if (!alive[i]) break;
        }
    }

    std::vector<std::shared_ptr<NPC>> survivors;
    survivors.reserve(n);
    for (std::size_t i = 0; i < n; ++i) {
        if (alive[i]) survivors.push_back(npcs[i]);
    }
    npcs.swap(survivors);
}
