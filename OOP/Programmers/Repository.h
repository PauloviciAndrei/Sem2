//
// Created by Robert on 18.06.2024.
//

#ifndef PROGRAMMERS_REPOSITORY_H
#define PROGRAMMERS_REPOSITORY_H

#include "Issue.h"
#include "User.h"
#include "Subject.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

class Repository : public Subject {
private:
    vector<User> users;
    vector<Issue> issues;
    string usersFile, issuesFile;

public:
    Repository() {
        usersFile = "D:\\Info\\OOP\\Programmers\\persons.txt";
        issuesFile = "D:\\Info\\OOP\\Programmers\\issues.txt";
        load_repo();
    }

    void load_repo();
    vector<Issue> getIssues() const {
        return issues;
    }
    vector<User> getUsers() const {
        return users;
    }
    void removeIssue(int row);
    bool checkIfIssueExists(const string &description);
    void addIssue(const string &description, bool status, const string &nameReporter,
                  const string &nameSolver);
    void resolveIssue(int pos, string solver);
};


#endif //PROGRAMMERS_REPOSITORY_H
