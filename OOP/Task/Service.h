#pragma once

#include "Repository.h"
#include "Observer.h"

class Service {
private:
    Repository& repo;

public:
    explicit Service(Repository& repo);

    void registerObserver(Observer* obs) { repo.registerObserver(obs); }

    void addTask(const std::string& description, int status, int id);
    void removeTask(int row);
    void startTask(int pos, int id);
    void finishTask(int pos);

    bool checkIfTaskExists(const std::string& description) const;
    std::string getProgrammerNameById(int id) const;


    const std::vector<Task>& getTasks() const { return repo.getTasks(); }
    const std::vector<Programmer>& getProgrammers() const { return repo.getProgrammers(); }

};
