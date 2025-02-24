//
// Created by Robert on 18.06.2024.
//

#include "Repository.h"

void Repository::load_repo() {
    ifstream file(usersFile);
    string name, type, row;
    char sep = '|';
    while (getline(file, row)) {
        istringstream iss(row);
        getline(iss, name, sep);
        getline(iss, type, sep);

        users.emplace_back(name, type);
    }
    file.close();
    file = ifstream(issuesFile);
    string description, status, reporter, solver;
    while (getline(file, row)) {
        istringstream iss(row);
        getline(iss, description, sep);
        getline(iss, status, sep);
        getline(iss, reporter, sep);
        getline(iss, solver, sep);
        bool statusBool = status == "open" ? true : false;

        issues.emplace_back(description, statusBool, reporter, solver);
    }
    sort(issues.begin(), issues.end());
    file.close();
}

void Repository::removeIssue(int row) {
    issues.erase(issues.begin() + row);
    this->notify();
}

bool Repository::checkIfIssueExists(const std::string &description) {
    for (const auto &issue : issues)
        if (issue.getDescription() == description)
            return true;
    return false;
}

void Repository::addIssue(const std::string &description, bool status, const std::string &nameReporter,
                          const std::string &nameSolver) {
    if (checkIfIssueExists(description))
        throw std::runtime_error("Issue already exists!");
    if (description.empty())
        throw std::runtime_error("Description cannot be empty!");
    issues.emplace_back(description, status, nameReporter, nameSolver);
    this->notify();
}

void Repository::resolveIssue(int pos, string solver) {
    issues[pos].setStatus(false);
    issues[pos].setSolver(solver);
    this->notify();
}