#pragma once
#include <string>
#include <vector>
#include <memory>

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onEvent(const std::string& msg) = 0;
};

class ConsoleObserver : public IObserver {
public:
    void onEvent(const std::string& msg) override;
};

class FileObserver : public IObserver {
public:
    explicit FileObserver(const std::string& filename);
    void onEvent(const std::string& msg) override;
private:
    std::string filename_;
};

class EventManager {
public:
    void addObserver(const std::shared_ptr<IObserver>& obs);
    void notify(const std::string& msg);
private:
    std::vector<std::shared_ptr<IObserver>> observers_;
};
