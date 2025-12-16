#include "Observer.h"
#include <iostream>
#include <fstream>

void ConsoleObserver::onEvent(const std::string& msg) {
    std::cout << msg << std::endl;
}

FileObserver::FileObserver(const std::string& filename)
    : filename_(filename) {}

void FileObserver::onEvent(const std::string& msg) {
    std::ofstream out(filename_, std::ios::app);
    if (out) {
        out << msg << '\n';
    }
}

void EventManager::addObserver(const std::shared_ptr<IObserver>& obs) {
    observers_.push_back(obs);
}

void EventManager::notify(const std::string& msg) {
    for (auto& o : observers_) {
        o->onEvent(msg);
    }
}
