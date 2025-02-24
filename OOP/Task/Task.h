//
// Created by user on 19-Jun-24.
//

#ifndef TASK_TASK_H
#define TASK_TASK_H
#include <string>
using namespace std;

class Task {
private:
    string description;
    int status;
    int id;

public:
    Task(string description = "", int status = -1, int id = -1) :
    description{description}, status{status}, id{id} {};
    string getDescription() const {
        return description;
    }
    int getStatus() const {
        return status;
    }
    int getId() const {
        return id;
    }
    string toString() const {
        string s;
        string sid = to_string(id);
        if(status == 0)
        {
            s = "open";
            sid = "None";
        }
        else
            if(status == 1)
                s = "in progress";
            else
                if(status == 2)
                    s = "closed";
        return description + "|" + s + "|" +
                sid;
    }
    void setStatus(int newStatus) {
        status = newStatus;
    }
    void setId(int newId) {
        id = newId;
    }
    inline bool operator < (const Task &other) const
    {
        if (status == other.status)
            return description < other.description;
        return status < other.status;
    }
};

#endif //TASK_TASK_H
