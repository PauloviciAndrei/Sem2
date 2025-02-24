//
// Created by user on 19-Jun-24.
//

#ifndef TASK_SUBJECT_H
#define TASK_SUBJECT_H

#include "Observer.h"
#include <vector>
using namespace std;

class Subject {
private:
    vector<Observer*> observers;
public:
    Subject() = default;
    ~Subject() = default;
    void registerObserver(Observer *observer) {
        observers.push_back(observer);
    }
    void notify() {
        for (auto observer : observers)
            observer->update();
    }
};

#endif //TASK_SUBJECT_H
