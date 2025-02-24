//
// Created by Robert on 18.06.2024.
//

#ifndef PROGRAMMERS_SUBJECT_H
#define PROGRAMMERS_SUBJECT_H

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

#endif //PROGRAMMERS_SUBJECT_H
