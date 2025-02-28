//
// Created by user on 19-Jun-24.
//

#ifndef TASK_PROGRAMMER_H
#define TASK_PROGRAMMER_H

#include <string>
using namespace std;

class Programmer {
private:
    string name;
    int id;

public:
    Programmer(const string &name, const int &id) : name{name}, id{id} {};

    string getName() const {
        return name;
    }

    int getId() const {
        return id;
    }

    string toString() const {
        return name + " | " + to_string(id);
    }
};

#endif //TASK_PROGRAMMER_H
