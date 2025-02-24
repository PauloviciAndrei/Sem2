//
// Created by Robert on 18.06.2024.
//

#ifndef PROGRAMMERS_OBSERVER_H
#define PROGRAMMERS_OBSERVER_H

class Observer {
public:
    Observer() = default;
    virtual ~Observer() = default;
    virtual void update() const = 0;
};

#endif //PROGRAMMERS_OBSERVER_H
