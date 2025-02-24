//
// Created by Robert on 18.06.2024.
//

#include "Repository.h"
#include <iostream>
#include <algorithm>

void Repository::load_repo() {
    ifstream file(usersFile);
    string name, type, row;
    char sep = '|';
    while (getline(file, row)) {
        istringstream iss(row);
        getline(iss, name, sep);
        getline(iss, type, sep);
        int idInt = stoi(type);
        programmers.emplace_back(name, idInt);
    }
    file.close();
    file = ifstream(issuesFile);
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

bool Repository::checkIfIssueExists(const std::string &description) {
    for (const auto &issue : tasks)
        if (issue.getDescription() == description)
            return true;
    return false;
}

void Repository::addTask(const std::string &description, int status, int id
                          ) {
    if (checkIfIssueExists(description))
        throw std::runtime_error("Issue already exists!");
    if (description.empty())
        throw std::runtime_error("Description cannot be empty!");
    tasks.emplace_back(description, status, id);
    this->notify();
}

void Repository::startTask(int pos, int id) {
    tasks[pos].setStatus(1);
    tasks[pos].setId(id);
    this->notify();
}

void Repository::finishTask(int pos)
{
    tasks[pos].setStatus(2);
    this->notify();
}
