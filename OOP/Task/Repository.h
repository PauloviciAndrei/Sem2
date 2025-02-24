//
// Created by user on 19-Jun-24.
//

#ifndef TASK_REPOSITORY_H
#define TASK_REPOSITORY_H


#include "Task.h"
#include "Programmer.h"
#include "Subject.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

class Repository : public Subject {
private:
    vector<Programmer> programmers;
    vector<Task> tasks;
    string usersFile, issuesFile;

public:
    Repository() {
        usersFile = "D:\\Info\\OOP\\Task\\Programmers.txt";
        issuesFile = "D:\\Info\\OOP\\Task\\Tasks.txt";
        load_repo();
    }

    void load_repo();
    vector<Task> getTasks() const {
        return tasks;
    }
    vector<Programmer> getUsers() const {
        return programmers;
    }
    void removeTask(int row);
    bool checkIfIssueExists(const string &description);
    void addTask(const string &description, int status, int id
                  );
    void startTask(int pos, int id);
    void finishTask(int pos);
};


#endif //TASK_REPOSITORY_H
