//
// Created by user on 19-Jun-24.
//

#pragma once
#include <string>

class Task {
private:
    std::string description;
    int status;
    int id;

public:
    Task(std::string description = "", int status = -1, int id = -1);

    std::string getDescription() const;
    int getStatus() const;
    int getId() const;

    std::string toString() const;

    void setStatus(int newStatus);
    void setId(int newId);

    bool operator<(const Task &other) const;
};
