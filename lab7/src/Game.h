#pragma once
#include <vector>
#include <string>
#include <queue>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <thread>
#include <atomic>

constexpr int MAP_WIDTH = 100;
constexpr int MAP_HEIGHT = 100;
constexpr double MOVE_DISTANCE = 30.0;
constexpr double KILL_DISTANCE = 10.0;

enum class NPCType { Dragon, Frog, Knight };

struct NPC {
    std::string name;
    NPCType type;
    double x{}, y{};
    bool alive{true};
};

struct BattleTask {
    size_t a, b;
};

class Game {
public:
    void run();

private:
    std::vector<NPC> npcs;
    std::queue<BattleTask> battleQueue;

    std::shared_mutex worldMutex;
    std::mutex queueMutex;
    std::mutex coutMutex;
    std::condition_variable queueCv;

    std::atomic<bool> running{false};

    void initNPCs();
    void movementThreadFunc();
    void battleThreadFunc();

    void resolveFight(NPC& a, NPC& b);
    bool canKill(const NPC& a, const NPC& b) const;
    double distance(const NPC& a, const NPC& b) const;

    void printMap();
    void printSurvivors();
};
