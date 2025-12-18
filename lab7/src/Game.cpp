#include "Game.h"
#include <iostream>
#include <cmath>
#include <chrono>
#include <random>

static int rollDice() {
    static thread_local std::mt19937 gen{std::random_device{}()};
    std::uniform_int_distribution<int> d(1,6);
    return d(gen);
}

void Game::initNPCs() {
    std::mt19937 gen{std::random_device{}()};
    std::uniform_real_distribution<double> dx(0, MAP_WIDTH);
    std::uniform_real_distribution<double> dy(0, MAP_HEIGHT);
    std::uniform_int_distribution<int> type(0,2);

    for (int i = 0; i < 50; ++i) {
        NPC n;
        n.type = static_cast<NPCType>(type(gen));
        n.name = "NPC_" + std::to_string(i);
        n.x = dx(gen);
        n.y = dy(gen);
        npcs.push_back(n);
    }
}

bool Game::canKill(const NPC& a, const NPC& b) const {
    if (!a.alive || !b.alive) return false;
    if (a.type == NPCType::Frog) return true;
    if (a.type == NPCType::Knight && b.type == NPCType::Dragon) return true;
    if (a.type == NPCType::Dragon && b.type == NPCType::Knight) return true;
    return false;
}

double Game::distance(const NPC& a, const NPC& b) const {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return std::sqrt(dx*dx + dy*dy);
}

void Game::resolveFight(NPC& a, NPC& b) {
    if (canKill(a,b)) {
        int atk = rollDice();
        int def = rollDice();
        if (atk > def) {
            b.alive = false;
            std::lock_guard<std::mutex> lg(coutMutex);
            std::cout << a.name << " killed " << b.name << "\n";
        }
    }
    if (canKill(b,a)) {
        int atk = rollDice();
        int def = rollDice();
        if (atk > def) {
            a.alive = false;
            std::lock_guard<std::mutex> lg(coutMutex);
            std::cout << b.name << " killed " << a.name << "\n";
        }
    }
}

void Game::movementThreadFunc() {
    using namespace std::chrono_literals;
    while (running) {
        {
            std::unique_lock<std::shared_mutex> lock(worldMutex);
            for (auto& a : npcs) {
                if (!a.alive || a.type != NPCType::Knight) continue;
                for (size_t j = 0; j < npcs.size(); ++j) {
                    if (&a == &npcs[j] || !npcs[j].alive) continue;
                    if (distance(a, npcs[j]) <= KILL_DISTANCE) {
                        std::lock_guard<std::mutex> ql(queueMutex);
                        battleQueue.push({&a - &npcs[0], j});
                        queueCv.notify_one();
                    }
                }
            }
        }
        std::this_thread::sleep_for(100ms);
    }
}

void Game::battleThreadFunc() {
    while (true) {
        BattleTask task;
        {
            std::unique_lock<std::mutex> ul(queueMutex);
            queueCv.wait(ul, [&]{ return !battleQueue.empty() || !running; });
            if (!running && battleQueue.empty()) break;
            task = battleQueue.front();
            battleQueue.pop();
        }
        std::unique_lock<std::shared_mutex> lock(worldMutex);
        if (task.a < npcs.size() && task.b < npcs.size()) {
            if (npcs[task.a].alive && npcs[task.b].alive)
                resolveFight(npcs[task.a], npcs[task.b]);
        }
    }
}

void Game::printMap() {
    std::shared_lock<std::shared_mutex> lock(worldMutex);
    std::lock_guard<std::mutex> lg(coutMutex);
    std::cout << "--- MAP ---\n";
    for (const auto& n : npcs) {
        if (n.alive)
            std::cout << n.name << " (" << n.x << "," << n.y << ")\n";
    }
}

void Game::printSurvivors() {
    std::shared_lock<std::shared_mutex> lock(worldMutex);
    std::lock_guard<std::mutex> lg(coutMutex);
    std::cout << "--- SURVIVORS ---\n";
    for (const auto& n : npcs)
        if (n.alive)
            std::cout << n.name << "\n";
}

void Game::run() {
    initNPCs();
    running = true;

    std::thread mover(&Game::movementThreadFunc, this);
    std::thread fighter(&Game::battleThreadFunc, this);

    auto start = std::chrono::steady_clock::now();
    while (std::chrono::steady_clock::now() - start < std::chrono::seconds(30)) {
        printMap();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    running = false;
    queueCv.notify_all();
    mover.join();
    fighter.join();
    printSurvivors();
}
