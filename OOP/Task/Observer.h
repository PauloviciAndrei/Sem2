//
// Created by user on 19-Jun-24.
//

#ifndef TASK_OBSERVER_H
#define TASK_OBSERVER_H

class Observer {
public:
    Observer() = default;
    virtual ~Observer() = default;
    virtual void update() const = 0;
};

#endif //TASK_OBSERVER_H
