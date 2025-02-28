#include "Repository.h"
#include <iostream>
#include <algorithm>
#include <unordered_map>

void Repository::load_repo() {
    cout << usersFile;
    ifstream file(usersFile);
    string name, type, row;
    char sep = '|';

    while (getline(file, row)) {
        istringstream iss(row);
        getline(iss, name, sep);
        getline(iss, type, sep);
        int idInt = stoi(type);
        programmers.emplace_back(name, idInt);
        programmerNames[idInt] = name;  // Store mapping
    }
    file.close();

    file = ifstream(tasksFile);
    string description, status, reporter, solver;
    while (getline(file, row)) {
        istringstream iss(row);
        getline(iss, description, sep);
        getline(iss, status, sep);
        getline(iss, reporter, sep);

        int statusInt = stoi(status);
        int idInt = stoi(reporter);

        tasks.emplace_back(description, statusInt, idInt);
    }

    sort(tasks.begin(), tasks.end());
    file.close();
}

void Repository::removeTask(int row) {
    tasks.erase(tasks.begin() + row);
    this->notify();
}

bool Repository::checkIfTaskExists(const std::string &description) {
    for (const auto &task : tasks)
        if (task.getDescription() == description)
            return true;
    return false;
}

void Repository::addTask(const std::string &description, int status, int id) {
    if (checkIfTaskExists(description))
        throw std::runtime_error("Task already exists!");
    if (description.empty())
        throw std::runtime_error("Name cannot be empty!");
    if (programmerNames.find(id) == programmerNames.end())
        throw std::runtime_error("Invalid programmer ID!");

    tasks.emplace_back(description, status, id);
    this->notify();
}

void Repository::startTask(int pos, int id) {
    if (programmerNames.find(id) == programmerNames.end())
        throw std::runtime_error("Invalid programmer ID!");

    tasks[pos].setStatus(1);
    tasks[pos].setId(id);
    this->notify();
}

void Repository::finishTask(int pos) {
    tasks[pos].setStatus(2);
    this->notify();
}

std::string Repository::getProgrammerNameById(int id) {
    if (programmerNames.find(id) != programmerNames.end())
        return programmerNames[id];
    return "None";
}
