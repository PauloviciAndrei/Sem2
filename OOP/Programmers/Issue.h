//
// Created by Robert on 18.06.2024.
//

#ifndef PROGRAMMERS_ISSUE_H
#define PROGRAMMERS_ISSUE_H

#include "User.h"

class Issue {
private:
    string description;
    bool status;
    string reporter, solver;

public:
    Issue(string description = "", bool status = false, string reporter = "",
          string solver = "") : description{description}, status{status},
                                reporter{reporter}, solver{solver} {};
    string getDescription() const {
        return description;
    }
    bool getStatus() const {
        return status;
    }
    string getReporter() const {
        return reporter;
    }
    string getSolver() const {
        return solver;
    }
    string toString() const {
        return description + "|" + (status ? "open" : "closed") + "|" +
               reporter + "|" + solver;
    }
    void setStatus(bool newStatus) {
        status = newStatus;
    }
    void setSolver(string newSolver) {
        solver = newSolver;
    }
    inline bool operator < (const Issue &other) const
    {
        if (status == other.status)
            return description < other.description;
        return status < other.status;
    }
};

#endif //PROGRAMMERS_ISSUE_H
